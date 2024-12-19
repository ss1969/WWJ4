#include "luat_debug.h"
#include "ringbuffer.h"

#define min(a,b) ( (a) < (b) )? (a):(b)

void takeMutex(RINGBUFFER_T *r)
{
	luat_rtos_semaphore_take(r->mutex, 0xFFFFFFFF);
}

void giveMutex(RINGBUFFER_T *r)
{
	luat_rtos_semaphore_release(r->mutex);
}

//---------------------------------------------------------------------------------------------
void RingBufInit(RINGBUFFER_T *r, uint8_t *buffer, uint32_t size, int protect)
{
	r->rp = 0;
	r->wp = 0;
	r->size = size;
	r->buf = buffer;
	r->mutex = NULL;
	if(protect){
		/* though we should protect buffer with an mutex, but as following says in queue.c
		we create an binary semaphore instead. */
		// /* Normally a mutex would not be given from an interrupt, especially if
		// there is a mutex holder, as priority inheritance makes no sense for an
		// interrupts, only tasks. */
		// configASSERT( !( ( pxQueue->uxQueueType == queueQUEUE_IS_MUTEX ) && ( pxQueue->pxMutexHolder != NULL ) ) );
		luat_rtos_semaphore_create(&r->mutex, 0);
	}
}

//---------------------------------------------------------------------------------------------
void RingBufClear(RINGBUFFER_T *r)
{
	takeMutex(r);
	r->rp = 0;
	r->wp = 0;
	giveMutex(r);
}

/* push data into ring buffer, if not enough space available, push as much as we can.
	return pushed data size.
*/
uint32_t RingBufWrite(RINGBUFFER_T *r, uint8_t *buf, uint32_t len)
{
	unsigned int i;
	unsigned int space;

	if(len == 0) return 0;
	takeMutex(r);

	/* calculate space available */
	space = r->size + r->rp - r->wp;

	/* calculate write length */
	len = min(len, space);

	/* calculate if it's able to write whole data to [wp:end] */
	i = min(len, r->size - r->wp % r->size);

	/* copy data */
	memcpy(r->buf + r->wp % r->size, buf, i);
	memcpy(r->buf, buf + i, len - i);

	/* calculate pointer */
	r->wp += len;

	giveMutex(r);
	return len;
}


/* try push data into ring buffer, if not enough space available, return 0 directly.
	after success, return pushed data size.
*/
uint32_t RingBufWriteTry(RINGBUFFER_T *r, uint8_t *buf, uint32_t len)
{
	unsigned int i;

	if(len == 0) return 0;
	takeMutex(r);

	/* calculate space available */
	if(len > r->size + r->rp - r->wp){
		giveMutex(r);
		return 0;
	}

	/* calculate if it's able to write whole data to [wp:end] */
	i = min(len, r->size - r->wp % r->size);

	/* copy data */
	memcpy(r->buf + r->wp % r->size, buf, i);
	memcpy(r->buf, buf + i, len - i);

	/* calculate pointer */
	r->wp += len;

	giveMutex(r);
	return len;
}


/* push data into ring buffer but, old data will be erased.
	read pointer will be move to oldest data position.
*/
uint32_t RingBufWriteForce(RINGBUFFER_T *r, uint8_t *buf, uint32_t len)
{
	unsigned int i;
	unsigned int space;

	if(len == 0) return 0;
	takeMutex(r);

	/* calculate space available */
	space = r->size + r->rp - r->wp;

	/* calculate write length, it cannot exceed the buffer size */
	if(len > r->size){
		buf += len - r->size;	/* write only the latter parts */
		len = r->size;
	}

	/* calculate if it's able to write whole data to [wp:end] */
	i = min(len, r->size - r->wp % r->size);

	/* copy data */
	memcpy(r->buf + r->wp % r->size, buf, i);
	memcpy(r->buf, buf + i, len - i);

	/* calculate pointer */
	r->wp += len;
	if(len > space){/* write more than space */
		r->rp += len - space;
	}

	giveMutex(r);
	return len;
}

/* forcely write 1 char into rb */
uint32_t RingBufWriteForce1Ch(RINGBUFFER_T *r, uint8_t ch)
{
	takeMutex(r);

	/* copy data */
	*(r->buf + r->wp % r->size) = ch;

	/* calculate pointer */
	if(r->size + r->rp == r->wp){
		/* if no space already, increase rp to erase 1 oldest */
		r->rp ++;
	}
	r->wp ++;

	giveMutex(r);
	return 1;
}

//---------------------------------------------------------------------------------------------
/* fall back the written bytes */
void RingBufWriteFallback(RINGBUFFER_T *r, uint32_t size)
{
	takeMutex(r);
	r->wp -= size;
	giveMutex(r);
}


//---------------------------------------------------------------------------------------------
uint32_t RingBufRead(RINGBUFFER_T *r, uint8_t *buf, uint32_t len)
{
	unsigned int i;
	unsigned int dcount;

	if(len == 0) return 0;
	takeMutex(r);

	/* calculate data available */
	dcount = r->wp - r->rp;
	if(dcount == 0){
		giveMutex(r);
		return 0;
	}

	/* calculate how many can we read */
	len = min(len, dcount);

	/* calculate read address */
	i = min(len, r->size - r->rp % r->size );

	/* copy data */
	memcpy(buf, r->buf + r->rp % r->size, i);
	memcpy(buf + i, r->buf, len - i);

	/* calculate pointer */
	r->rp += len;

	giveMutex(r);
	return len;
}

//---------------------------------------------------------------------------------------------
uint32_t RingBufFetch(RINGBUFFER_T *r, uint8_t *buf, uint32_t len)
{
	unsigned int i;
	unsigned int dcount;

	if(len == 0) return 0;
	takeMutex(r);

	/* calculate data available */
	dcount = r->wp - r->rp;
	if(dcount == 0){
		giveMutex(r);
		return 0;
	}

	/* calculate how many can we read */
	len = min(len, dcount);

	/* calculate read address */
	i = min(len, r->size - r->rp % r->size );

	/* copy data */
	memcpy(buf, r->buf + r->rp % r->size, i);
	memcpy(buf + i, r->buf, len - i);

	giveMutex(r);
	return len;
}

//---------------------------------------------------------------------------------------------
uint32_t RingBufPurge(RINGBUFFER_T *r, uint32_t len)
{
	unsigned int dcount;

	if(len == 0) return 0;
	takeMutex(r);

	/* calculate data available */
	dcount = r->wp - r->rp;

	/* calculate how many can we read */
	len = min(len, dcount);

	/* calculate pointer */
	r->rp += len;

	giveMutex(r);
	return len;
}

//---------------------------------------------------------------------------------------------
uint32_t RingBufRead1Ch(RINGBUFFER_T *r, uint8_t *buf)
{
	takeMutex(r);

	/* calculate data available */
	if(r->wp == r->rp) {
		*buf = 0;
		giveMutex(r);
		return 0;
	}

	/* copy data */
	*buf = *(r->buf + r->rp % r->size);

	/* calculate pointer */
	r->rp ++;

	giveMutex(r);
	return 1;
}

//---------------------------------------------------------------------------------------------
uint32_t RingBufDataCount(RINGBUFFER_T *r)
{
	uint32_t l;

	takeMutex(r);
	l = r->wp - r->rp;
	giveMutex(r);
	return l;
}




