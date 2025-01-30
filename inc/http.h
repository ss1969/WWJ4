#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_

typedef enum _HTTP_STATUS {
    TEST_HTTP_GET_HEAD = 0,
    TEST_HTTP_GET_HEAD_DONE,
    TEST_HTTP_GET_DATA,
    TEST_HTTP_GET_DATA_DONE,
    TEST_HTTP_POST_DATA_START,
    TEST_HTTP_POST_DATA_CONTINUE,
    TEST_HTTP_FAILED,
} HTTP_STATUS;

typedef void (*http_callback)(const char *data, const int size, HTTP_STATUS status);

void http_get(char *url, http_callback cb);

#endif