#include "common_api.h"
#include "luat_rtos.h"
#include "luat_mobile.h"
#include "luat_debug.h"
#include "luat_sms.h"
#include "luat_mem.h"

#include "str2x.h"
#include "sysvars.h"
#include "mobile.h"

#define MOBILE_CELL_REFRESH_TIME 120 * 1000

typedef enum {
    MOBILE_NETIF = 0,
    MOBILE_SMS,
} MOBILE_EVENT_E;

static luat_rtos_task_handle   task_mobile_handle = NULL;
static luat_mobile_cell_info_t s_cell_info;
static net_status_callback     net_ready_cb = NULL;
net_sms_callback               net_sms_cb   = NULL;

static void sms_recv_cb(uint32_t event, void *param) {
    LUAT_DEBUG_PRINT("sms_recv_cb:[%d]", event);
    luat_rtos_event_send(task_mobile_handle, MOBILE_SMS, (uint32_t)param, 0, 0, 0);
}

static void sms_send_cb(uint32_t event, void *param) {
    LUAT_DEBUG_PRINT("sms_send_cb:[%d]", event);
}

static void mobile_event_cb(LUAT_MOBILE_EVENT_E event, uint8_t index, uint8_t status) {
    luat_mobile_signal_strength_info_t signal_info;
    uint16_t                           mcc;
    uint8_t                            csq, i, mnc;
    char                               apn[32] = {0};
    ip_addr_t                          ipv4;
    ip_addr_t                          ipv6;
    int                                result;

    static LUAT_MOBILE_REGISTER_STATUS_E rs = 0;

    switch (event) {
        case LUAT_MOBILE_EVENT_CFUN:
            LUAT_DEBUG_PRINT("CFUN消息，status %d", status);
            break;
        case LUAT_MOBILE_EVENT_SIM:
            if (status != LUAT_MOBILE_SIM_NUMBER) {
                LOG("SIM卡消息，卡槽 %d", index);
            }
            switch (status) {
                case LUAT_MOBILE_SIM_READY:
                    LOG("SIM卡正常工作");
                    luat_mobile_get_imsi(0, svIMSI, sizeof(svIMSI));
                    LOG("IMSI: %s", svIMSI);
                    luat_mobile_get_iccid(0, svICCID, sizeof(svICCID));
                    LOG("ICCID: %s", svICCID);
                    luat_mobile_get_plmn_from_imsi(svIMSI, &mcc, &mnc);
                    LOG("MCC: %d, MNC %d", mcc, mnc);
                    result = luat_mobile_get_isp_from_plmn(mcc, mnc);
                    switch (result) {
                        case LUAT_MOBILE_ISP_CMCC:
                            LOG("中国移动卡");
                            break;
                        case LUAT_MOBILE_ISP_CTCC:
                            LOG("中国电信卡");
                            break;
                        case LUAT_MOBILE_ISP_CUCC:
                            LOG("中国联通卡");
                            break;
                        case LUAT_MOBILE_ISP_CRCC:
                            LOG("中国广电卡");
                            break;
                        case LUAT_MOBILE_ISP_UNKNOW:
                            LOG("未知运营商");
                            break;
                        default:
                            LOG("非中国卡 %d", result);
                            break;
                    }
                    break;
                case LUAT_MOBILE_NO_SIM:
                    LOG("SIM卡不存在");
                    break;
                case LUAT_MOBILE_SIM_NEED_PIN:
                    LOG("SIM卡需要输入PIN码");
                    break;
            }
            break;
        case LUAT_MOBILE_EVENT_REGISTER_STATUS:
            if (rs == status) // 不知道为什么会多次 LUAT_MOBILE_STATUS_REGISTERED
                break;
            rs = status;
            if (status == LUAT_MOBILE_STATUS_REGISTERED) {
                LOG("移动网络服务状态变更: REGISTERED");
                luat_mobile_get_sim_number(0, svPhoneNumber, sizeof(svPhoneNumber));
                LUAT_DEBUG_PRINT("Phone: %s", svPhoneNumber);
            }
            else {
                LOG("移动网络服务状态变更: %d", status);
            }
            break;
        case LUAT_MOBILE_EVENT_CELL_INFO:
            switch (status) {
                case LUAT_MOBILE_CELL_INFO_UPDATE:
#if 0 // 小区信息，没用不显示了
			LUAT_DEBUG_PRINT("周期性搜索小区信息完成一次");
			luat_mobile_get_last_notify_cell_info(&s_cell_info);
			if (s_cell_info.lte_service_info.cid)
			{
				LUAT_DEBUG_PRINT("服务小区信息 mcc %x mnc %x cellid %u band %d tac %u pci %u earfcn %u is_tdd %d rsrp %d rsrq %d snr %d rssi %d",
						s_cell_info.lte_service_info.mcc, s_cell_info.lte_service_info.mnc, s_cell_info.lte_service_info.cid,
						s_cell_info.lte_service_info.band, s_cell_info.lte_service_info.tac, s_cell_info.lte_service_info.pci, s_cell_info.lte_service_info.earfcn,
						s_cell_info.lte_service_info.is_tdd, s_cell_info.lte_service_info.rsrp, s_cell_info.lte_service_info.rsrq,
						s_cell_info.lte_service_info.snr, s_cell_info.lte_service_info.rssi);
			}
			for (i = 0; i < s_cell_info.lte_neighbor_info_num; i++)
			{
				if (s_cell_info.lte_info[i].cid)
				{
					LUAT_DEBUG_PRINT("邻小区 %d mcc %x mnc %x cellid %u tac %u pci %u", i + 1, s_cell_info.lte_info[i].mcc,
							s_cell_info.lte_info[i].mnc, s_cell_info.lte_info[i].cid, s_cell_info.lte_info[i].tac, s_cell_info.lte_info[i].pci);
					LUAT_DEBUG_PRINT("邻小区 %d earfcn %u rsrp %d rsrq %d snr %d", i + 1, s_cell_info.lte_info[i].earfcn, s_cell_info.lte_info[i].rsrp,
							s_cell_info.lte_info[i].rsrq, s_cell_info.lte_info[i].snr);
				}
			}
#endif
                    break;
                case LUAT_MOBILE_SIGNAL_UPDATE:
                    luat_mobile_get_last_notify_signal_strength_info(&signal_info);
                    luat_mobile_get_last_notify_signal_strength(&csq);
                    svSignal = csq;
#if 0 // k 信号强度，不显示LOG了
                    if (signal_info.luat_mobile_lte_signal_strength_vaild) {
                        LOG("信号状态变更 rsrp %d, rsrq %d, snr %d, rssi %d, csq %d %d",
                            signal_info.lte_signal_strength.rsrp,
                            signal_info.lte_signal_strength.rsrq,
                            signal_info.lte_signal_strength.snr,
                            signal_info.lte_signal_strength.rssi,
                            csq,
                            luat_mobile_rssi_to_csq(signal_info.lte_signal_strength.rssi));
                    }
#endif
                    break;
            }
            break;
        case LUAT_MOBILE_EVENT_PDP:
#if 0 // Packet Data Protocol 数据激活状态消息，不显示了
            LOG("CID PDP 激活状态变更为 %s", status == LUAT_MOBILE_PDP_ACTIVED ? "ACTIVED" : "DEACTIVED");
#endif
            break;
        case LUAT_MOBILE_EVENT_NETIF:
            switch (status) {
                case LUAT_MOBILE_NETIF_LINK_ON:
                    LOG("Internet 状态变更为 Ready");
                    if (luat_mobile_get_apn(0, 0, apn, sizeof(apn))) {
                        LOG("APN %s", apn);
                    }
                    luat_mobile_get_local_ip(0, 1, &ipv4, &ipv6);
                    if (ipv4.type != 0xff) {
                        LOG("IPV4 %s", ip4addr_ntoa(&ipv4.u_addr.ip4));
                    }
                    if (ipv6.type != 0xff) {
                        LOG("IPV6 %s", ip6addr_ntoa(&ipv4.u_addr.ip6));
                    }
                    luat_rtos_event_send(task_mobile_handle, MOBILE_NETIF, true, 0, 0, 0);
                    break;
                default:
                    LOG("Internet 状态变更为 %s", status == LUAT_MOBILE_NETIF_LINK_OFF ? "OFF" : "OOS");
                    luat_rtos_event_send(task_mobile_handle, MOBILE_NETIF, false, 0, 0, 0);
                    break;
            }
            break;
        case LUAT_MOBILE_EVENT_TIME_SYNC:
            if (!status) {
                LOG("移动网络同步 UTC 时间成功");
            }
            else {
                LOG("移动网络同步 UTC 时间出错");
            }
            break;
#if 0 // Radio Resource Control，无线资源控制 节能状态和正常状态切换，不log
        case LUAT_MOBILE_EVENT_CSCON:
            LOG("RRC状态 %s", status == 1 ? "Active" : "Idle");
            break;
#endif
        case LUAT_MOBILE_EVENT_FATAL_ERROR:
            LOG("Fatal ERROR，15秒内不能恢复的建议重启协议栈");
            break;
        default:
            break;
    }
}

static void mobile_get_band_string(uint8_t band1[], uint8_t total_num1, char *result, size_t result_size) {
    int offset = 0;
    offset += snprintf(result + offset, result_size - offset, "Band: ");
    for (uint8_t i = 0; i < total_num1; ++i) {
        if (i < total_num1 - 1) {
            offset += snprintf(result + offset, result_size - offset, "%d/", band1[i]);
        }
        else {
            offset += snprintf(result + offset, result_size - offset, "%d", band1[i]);
        }
    }
}

void mobile_set_sn(char *newSn) {
    luat_mobile_set_sn(newSn, 32);
    char sn[33] = {0};
    luat_mobile_get_sn(sn, sizeof(sn));
    LUAT_DEBUG_PRINT("SN %s", sn);
}

void mobile_get_muid(void) {
    char muid[64] = {0};
    luat_mobile_get_muid(muid, sizeof(muid));
    LUAT_DEBUG_PRINT("MUID %s", muid);
}

void mobile_get_band(void) {
    uint8_t band[32];
    uint8_t total_num;
    luat_mobile_get_band(band, &total_num);
    char buf[128];
    mobile_get_band_string(band, total_num, buf, sizeof(buf));
    LUAT_DEBUG_PRINT("%s", buf);
}

void mobile_get_cell_info(void) {
    luat_mobile_cell_info_t cell_info;
    luat_mobile_get_cell_info_async(6);
    luat_rtos_task_sleep(15 * 1000);
    luat_mobile_get_cell_info(&cell_info);

    if (cell_info.lte_service_info.cid) {
        LUAT_DEBUG_PRINT("服务小区信息 mcc %x mnc %x cellid %u band %d tac %u pci %u earfcn %u is_tdd %d rsrp %d rsrq %d snr %d "
                         "rssi %d",
                         cell_info.lte_service_info.mcc,
                         cell_info.lte_service_info.mnc,
                         cell_info.lte_service_info.cid,
                         cell_info.lte_service_info.band,
                         cell_info.lte_service_info.tac,
                         cell_info.lte_service_info.pci,
                         cell_info.lte_service_info.earfcn,
                         cell_info.lte_service_info.is_tdd,
                         cell_info.lte_service_info.rsrp,
                         cell_info.lte_service_info.rsrq,
                         cell_info.lte_service_info.snr,
                         cell_info.lte_service_info.rssi);
    }
    for (int i = 0; i < cell_info.lte_neighbor_info_num; i++) {
        if (cell_info.lte_info[i].cid) {
            LUAT_DEBUG_PRINT("邻小区 %d mcc %x mnc %x cellid %u tac %u pci %u",
                             i + 1,
                             cell_info.lte_info[i].mcc,
                             cell_info.lte_info[i].mnc,
                             cell_info.lte_info[i].cid,
                             cell_info.lte_info[i].tac,
                             cell_info.lte_info[i].pci);
            LUAT_DEBUG_PRINT("邻小区 %d earfcn %u rsrp %d rsrq %d snr %d",
                             i + 1,
                             cell_info.lte_info[i].earfcn,
                             cell_info.lte_info[i].rsrp,
                             cell_info.lte_info[i].rsrq,
                             cell_info.lte_info[i].snr);
        }
    }
}

static void mobile_main_task(void *param) {

    int          ret;
    luat_event_t event;
    while (true) {
        ret = luat_rtos_event_recv(task_mobile_handle, 0, &event, NULL, LUAT_WAIT_FOREVER);
        if (ret) {
            LUAT_DEBUG_PRINT("luat_rtos_event_recv ERROR %d", event.id);
            continue;
        }
        switch (event.id) {
            case MOBILE_NETIF:
                if (net_ready_cb != NULL) {
                    net_ready_cb(event.param1);
                }
                break;
            case MOBILE_SMS: {
                LUAT_SMS_RECV_MSG_T *data     = (LUAT_SMS_RECV_MSG_T *)event.param1;
                char                 time[32] = {0};
                sprintf(time,
                        "%02d/%02d/%02d,%02d:%02d:%02d %c%02d",
                        data->time.year,
                        data->time.month,
                        data->time.day,
                        data->time.hour,
                        data->time.minute,
                        data->time.second,
                        data->time.tz_sign,
                        data->time.tz);
                char *uni = convertToUnicode(data->sms_buffer);
                LUAT_DEBUG_PRINT("PDU: [%s]", uni);
                if (net_sms_cb != NULL)
                    net_sms_cb(time, data->phone_address, uni);
                FREE(uni);
                break;
            }
            default:
                break;
        }
    }
}

void mobile_task_init(void) {
    luat_rtos_task_create(&task_mobile_handle, 4 * 1024, 20, "task mobile", mobile_main_task, NULL, 16);

    luat_sms_init();
    luat_sms_recv_msg_register_handler(sms_recv_cb);
    luat_sms_send_msg_register_handler(sms_send_cb);

    luat_mobile_event_register_handler(mobile_event_cb);

    luat_mobile_set_period_work(90000, 5000, 4);  // 90秒搜索基站间隔，5秒sim卡脱离的尝试恢复间隔，每次基站搜索最大4s
    luat_mobile_set_check_network_period(120000); // 设置定时检测网络是否正常并且在检测到长时间无网时通过重启协议栈来恢复，但是不能保证一定成功

    luat_mobile_set_sim_detect_sim0_first();      // 优先sim 0
    luat_mobile_set_sync_time(1);                 // 0，表示禁用基站同步时间，传入1，表示启用基站同步时间
}

void mobile_task_deinit(void) {
    if (task_mobile_handle) {
        luat_rtos_task_suspend(task_mobile_handle);
        luat_rtos_task_delete(task_mobile_handle);
    }

    luat_mobile_event_deregister_handler();
}

void mobile_set_netready_callback(net_status_callback cb) {
    net_ready_cb = cb;
}

void mobile_set_sms_callback(net_sms_callback cb) {
    net_sms_cb = cb;
}