#ifndef _RINGBUFFER_H__
#define _RINGBUFFER_H__
#include <stdint.h>

#include "luat_rtos.h"

//---------------------------------------------------------------------------------------------
typedef struct
{
	volatile uint32_t rp;
	volatile uint32_t wp;
	uint32_t size;
	uint8_t	*buf;
    luat_rtos_semaphore_t mutex;  // 互斥信号量，用于保护缓冲区操作
} RINGBUFFER_T ;

//---------------------------------------------------------------------------------------------
#define RINGBUFFER_PROTECTED	1
#define RINGBUFFER_UNPROTECTED	0

//---------------------------------------------------------------------------------------------
void RingBufInit(RINGBUFFER_T *r, uint8_t *buffer, uint32_t size, int protect);	/* init */
void RingBufClear(RINGBUFFER_T *r);												/* clean data */
uint32_t RingBufWrite(RINGBUFFER_T *r, uint8_t *buf, uint32_t len);				/* write some data, if space not enough, return written size */
uint32_t RingBufWriteTry(RINGBUFFER_T *r, uint8_t *buf, uint32_t len);			/* try to write some data, return 0 directly if buffer not enough */
uint32_t RingBufWriteForce(RINGBUFFER_T *r, uint8_t *buf, uint32_t len);		/* write all, if space not enough, overwrite oldest */
uint32_t RingBufWriteForce1Ch(RINGBUFFER_T *r, uint8_t ch);						/* write 1 char, if space not enough, overwrite oldest */
void RingBufWriteFallback(RINGBUFFER_T *r, uint32_t size);						/* fallback write pointer, means cancel previously written bytes. */
uint32_t RingBufRead(RINGBUFFER_T *r, uint8_t *buf, uint32_t len);				/* copy data and purge it in queue */
uint32_t RingBufFetch(RINGBUFFER_T *r, uint8_t *buf, uint32_t len);				/* copy data but not purge it in queue */
uint32_t RingBufPurge(RINGBUFFER_T *r, uint32_t len);							/* purge data, does not copy it */
uint32_t RingBufRead1Ch(RINGBUFFER_T *r, uint8_t *buf);							/* read out 1 char */
uint32_t RingBufDataCount(RINGBUFFER_T *r);										/* count how many data are in queue */

#endif

