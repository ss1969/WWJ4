#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_

typedef enum _HTTP_STATUS {
    HTTP_STATUS_GET_HEAD = 0,
    HTTP_STATUS_GET_HEAD_DONE,
    HTTP_STATUS_GET_DATA,
    HTTP_STATUS_GET_DATA_DONE,
    HTTP_STATUS_POST_DATA_START,
    HTTP_STATUS_POST_DATA_CONTINUE,
    HTTP_STATUS_FAILED,
} HTTP_STATUS;

typedef void (*http_callback)(const char *data, const int size, HTTP_STATUS status);

void http_get(char *url, http_callback cb);

#endif