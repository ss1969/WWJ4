#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_network_adapter.h"
#include "networkmgr.h"
#include "luat_http.h"
#include "luat_mem.h"

#include "http.h"
#include "wrapper.h"

static luat_rtos_task_handle task_http_handle;
static http_callback         httpcb = NULL;

static void luatos_http_cb(int status, void *data, uint32_t len, void *param) {
    uint8_t *head_data;
    uint8_t *body_data;

    if (status < 0) {
        luat_rtos_event_send(param, HTTP_STATUS_FAILED, 0, 0, 0, 0);
        return;
    }

    switch (status) {
        case HTTP_STATE_GET_BODY:
            if (data) {
                body_data = luat_heap_malloc(len);
                memset(body_data, 0, len);
                memcpy(body_data, data, len);
                luat_rtos_event_send(param, HTTP_STATUS_GET_DATA, (uint32_t)body_data, len, 0, 0);
            }
            else {
                luat_rtos_event_send(param, HTTP_STATUS_GET_DATA_DONE, 0, 0, 0, 0);
            }
            break;
        case HTTP_STATE_GET_HEAD:
            if (data) {
                head_data = luat_heap_malloc(len);
                memset(head_data, 0, len);
                memcpy(head_data, data, len);
                luat_rtos_event_send(param, HTTP_STATUS_GET_HEAD, (uint32_t)head_data, len, 0, 0);
            }
            else {
                luat_rtos_event_send(param, HTTP_STATUS_GET_HEAD_DONE, 0, 0, 0, 0);
            }
            break;
        case HTTP_STATE_IDLE:
            break;
        case HTTP_STATE_SEND_BODY_START:
            // 如果是POST，在这里发送POST的body数据，如果一次发送不完，可以在HTTP_STATE_SEND_BODY回调里继续发送
            luat_rtos_event_send(param, HTTP_STATUS_POST_DATA_START, 0, 0, 0, 0);
            break;
        case HTTP_STATE_SEND_BODY:
            // 如果是POST，可以在这里发送POST剩余的body数据
            luat_rtos_event_send(param, HTTP_STATUS_POST_DATA_CONTINUE, 0, 0, 0, 0);
            break;
        default:
            break;
    }
}

static void http_get_async_task(const char *url) {
    luat_event_t event = {0};
    int          result;
    uint8_t      is_end = 0;

    luat_http_ctrl_t *http = luat_http_client_create(luatos_http_cb, luat_rtos_get_current_handle(), -1);
    luat_http_client_start(http, url, 0, 0, 1);

    while (!is_end) {
        luat_rtos_event_recv(task_http_handle, 0, &event, NULL, LUAT_WAIT_FOREVER);
        // callback first
        if (httpcb != NULL)
            httpcb(event.param1, event.param2, event.id);
        switch (event.id) {
            case HTTP_STATUS_GET_HEAD:
                luat_heap_free((char *)event.param1);
                break;
            case HTTP_STATUS_GET_HEAD_DONE:
                // 在这里处理http响应头
                LUAT_DEBUG_PRINT("status %d", luat_http_client_get_status_code(http));
                break;
            case HTTP_STATUS_GET_DATA:
                // 在这里处理用户数据, param1是地址，param2是长度
                // 可能是多次
                luat_heap_free((char *)event.param1);
                break;
            case HTTP_STATUS_GET_DATA_DONE:
                // 数据结束
                is_end = 1;
                break;
            case HTTP_STATUS_FAILED:
                is_end = 1;
                break;
            default:
                break;
        }
    }

    // 如果服务器会在下载完成后主动断开，就会多一个HTTP_STATUS_FAILED消息，需要接收处理掉
    do {
        result = luat_rtos_event_recv(task_http_handle, 0, &event, NULL, 100);
    }
    while (result >= 0);

    luat_http_client_close(http);
    luat_http_client_destroy(&http);
    luat_rtos_task_delete(task_http_handle);

    LOG("Http Finished");
}

void http_get(char *url, http_callback cb) {
    LOG("Http Get %s", url);
    httpcb = cb;
    luat_rtos_task_create(&task_http_handle, 4 * 1024, 20, "task http", http_get_async_task, url, 16);
}
