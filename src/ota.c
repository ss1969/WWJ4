/**
 * 如果使用全量升级，必须是Air780EP(V,S,T...),Air780EQ等等总FLASH不小于4MB的模块，必须在项目的xmake.lua里设置AP_FLASH_LOAD_SIZE，AP_PKGIMG_LIMIT_SIZE，FULL_OTA_SAVE_ADDR。
 * AP_FLASH_LOAD_SIZE必须减小到能放下代码，同时有剩余空间能放下OTA包，这里的剩余空间包括了原本的DFOTA区域
 * AP_PKGIMG_LIMIT_SIZE必须和AP_FLASH_LOAD_SIZE一致，FULL_OTA_SAVE_ADDR必须在实际AP占用空间之后，OTA保存空间长度=FLASH_FS_REGION_START-FULL_OTA_SAVE_ADDR
 * luatools需要2.2.15及以上版本，进入选项及工具->SOC差分/整包升级包制作工具，新版固件选择要升级的SOC包(SOC包，SOC包，重要的事情说3遍，不是binpkg)
 * 用户标识可以填版本号，也可以不填，看自己的代码对升级版本是否有控制，如果用合宙IOT升级服务，则必须填写版本号！！！
 * 选好输出路径，点生成，在输出目录下生成相应的xxx.sota文件为升级包（使用合宙IOT升级服务的，受网页上文件识别规则限制，后缀改为.bin即可），放在服务器上下载即可升级
 */

#include "common_api.h"

#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_flash.h"
#include "luat_crypto.h"
#include "luat_fota.h"
#include "mem_map.h"
#include "luat_uart.h"
#include "luat_mobile.h"
#include "luat_network_adapter.h"
#include "networkmgr.h"
#include "luat_http.h"
#include "luat_mem.h"

#include "sysvars.h"

luat_rtos_task_handle ota_task_handle;

typedef struct {
    luat_http_ctrl_t     *http;
    uint32_t              http_data_cnt;
    luat_rtos_task_handle task_handle;
} http_download_ctrl_t;

enum {
    OTA_HTTP_GET_HEAD_DONE = 1,
    OTA_HTTP_GET_DATA,
    OTA_HTTP_GET_DATA_DONE,
    OTA_HTTP_FAILED,
};

static void ota_http_cb(int status, void *data, uint32_t len, void *param) {
    uint8_t              *ota_data;
    http_download_ctrl_t *download = (http_download_ctrl_t *)param;
    if (status < 0) {
        LUAT_DEBUG_PRINT("http failed! %d", status);
        luat_rtos_event_send(download->task_handle, OTA_HTTP_FAILED, 0, 0, 0, 0);
        return;
    }
    switch (status) {
        case HTTP_STATE_GET_BODY:
            if (data) {
                ota_data = luat_heap_malloc(len);
                memcpy(ota_data, data, len);
                luat_rtos_event_send(download->task_handle, OTA_HTTP_GET_DATA, (uint32_t)ota_data, len, 0, 0);
                download->http_data_cnt++;
                // 对下载速度进行控制，如果下载速度过快，会导致ram耗尽出错
                if (download->http_data_cnt > 6) {
                    if (!download->http->is_pause) {
                        luat_http_client_pause(download->http, 1);
                    }
                }
            }
            else {
                luat_rtos_event_send(download->task_handle, OTA_HTTP_GET_DATA_DONE, 0, 0, 0, 0);
            }
            break;
        case HTTP_STATE_GET_HEAD:
            if (data) {
                LUAT_DEBUG_PRINT("%s", data);
            }
            else {
                luat_rtos_event_send(download->task_handle, OTA_HTTP_GET_HEAD_DONE, 0, 0, 0, 0);
            }
            break;
        case HTTP_STATE_IDLE:
            break;
        case HTTP_STATE_SEND_BODY_START:
            // 如果是POST，在这里发送POST的body数据，如果一次发送不完，可以在HTTP_STATE_SEND_BODY回调里继续发送
            break;
        case HTTP_STATE_SEND_BODY:
            // 如果是POST，可以在这里发送POST剩余的body数据
            break;
        default:
            break;
    }
}

static void ota_main_rountine(const char *firmware_url) {
    char url[256] = {0};
    strcpy(url, firmware_url);

    luat_debug_set_fault_mode(LUAT_DEBUG_FAULT_HANG_RESET);

    luat_event_t event;
    int          result;
    size_t       all, now_free_block, min_free_block, done_len = 0;

    http_download_ctrl_t download;
    download.http_data_cnt = 0;
    download.task_handle   = luat_rtos_get_current_handle();
    download.http          = luat_http_client_create(ota_http_cb, &download, -1);
    luat_fota_init(0, 0, NULL, NULL, 0);
    luat_http_client_start(download.http, url, 0, 0, 1);
    LUAT_DEBUG_PRINT("ota start url %s", url);

    while (true) {
        luat_rtos_event_recv(download.task_handle, 0, &event, NULL, LUAT_WAIT_FOREVER);
        switch (event.id) {
            case OTA_HTTP_GET_HEAD_DONE:
                done_len = 0;
                LUAT_DEBUG_PRINT("status %d total %u", luat_http_client_get_status_code(download.http),
                                 download.http->context_len);
                break;
            case OTA_HTTP_GET_DATA:
                done_len += event.param2;
                result = luat_fota_write((uint8_t *)event.param1, event.param2);
                luat_heap_free((uint8_t *)event.param1);

                luat_meminfo_sys(&all, &now_free_block, &min_free_block);
                LUAT_DEBUG_PRINT("ota data: %d, mem: all %d, now_free %d, min_free %d", done_len, all, now_free_block,
                                 min_free_block);

                // 对下载速度进行控制，如果下载速度过快，会导致ram耗尽出错
                if (download.http_data_cnt) {
                    download.http_data_cnt--;
                    if ((download.http_data_cnt < 2) && download.http->is_pause) {
                        luat_http_client_pause(download.http, 0);
                    }
                }
                break;
            case OTA_HTTP_GET_DATA_DONE:
                if (!luat_fota_done())
                    luat_os_reboot(0);
                LUAT_DEBUG_PRINT("full ota 测试失败");
                luat_http_client_close(download.http);
                luat_http_client_destroy(&download.http);
                luat_rtos_task_sleep(60000);
                luat_os_reboot(0);
                break;
            case OTA_HTTP_FAILED:
                LUAT_DEBUG_PRINT("full ota 测试失败");
                break;
            default:
                LUAT_DEBUG_PRINT("full ota 未知事件 %d", event.id);
                break;
        }
    }
}

void ota_taskinit(const char *firmware_url) {
    luat_rtos_task_create(&ota_task_handle, 4 * 1024, 50, "ota_task", ota_main_rountine, firmware_url, 0);
}
