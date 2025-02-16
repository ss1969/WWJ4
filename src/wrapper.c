#include <stdarg.h>
#include "luat_rtc.h"
#include "luat_uart.h"

#include "usart.h"
#include "wrapper.h"

#define MAX_BUFFER_SIZE 256 // 定义最大日志长度，根据需要调整

void LOG(const char *format, ...) {
    static char buffer[MAX_BUFFER_SIZE];
    va_list     args;
    va_start(args, format);

    // 把时间字符串写入头部
    struct tm tblock = {0};
    luat_rtc_get(&tblock);
    int tm_len = sprintf(buffer, "[%02d/%02d %02d:%02d:%02d]", tblock.tm_mon + 1, tblock.tm_mday, tblock.tm_hour, tblock.tm_min, tblock.tm_sec);

    // 格式化字符串到 buffer，确保不会超出缓冲区大小
    int len = vsnprintf(buffer + tm_len, MAX_BUFFER_SIZE - tm_len, format, args) + tm_len;
    va_end(args);

    // 如果格式化后的字符串长度超过缓冲区大小，vsnprintf 会返回需要的总长度
    // 如果 len >= MAX_BUFFER_SIZE，说明字符串被截断
    if (len >= MAX_BUFFER_SIZE) {
        len         = MAX_BUFFER_SIZE - 1; // 截断长度，保留最后一个字节给 '\0'
        buffer[len] = '\0';                // 确保字符串以 '\0' 结尾
    }

    // 移除末尾的 '\r' 和 '\n'（如果有的话）
    while (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n')) {
        buffer[--len] = '\0';
    }

    // 输出到 LUAT_DEBUG_PRINT，不带时间字符串部分，不带 '\r' 和 '\n'
    LUAT_DEBUG_PRINT("%s", buffer + tm_len);

    // 确保有足够空间添加 '\n'
    if (len < MAX_BUFFER_SIZE - 1) {
        buffer[len++] = '\n'; // 添加 '\n'
        buffer[len]   = '\0'; // 确保字符串以 '\0' 结尾
    }
    else {
        // 如果没有足够空间添加 '\n'，直接截断
        buffer[MAX_BUFFER_SIZE - 2] = '\n'; // 倒数第二个位置放 '\n'
        buffer[MAX_BUFFER_SIZE - 1] = '\0'; // 最后一个字节放 '\0'
    }

    // 输出到 uart_print_async
    uart_print_async("%s", buffer);
}

void LOG_HEX(char *prefix, char *hex, size_t len) {
    char buffer[MAX_BUFFER_SIZE];
    int  offset = 0;

    offset += snprintf(buffer + offset, MAX_BUFFER_SIZE - offset, prefix);

    for (int i = 0; i < len; i++) {
        offset += snprintf(buffer + offset, MAX_BUFFER_SIZE - offset, "%02x", hex[i]);
    }

    offset += snprintf(buffer + offset, MAX_BUFFER_SIZE - offset, "\n");
    LOG("%s", buffer);
}
