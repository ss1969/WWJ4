#include "common_api.h"
#include "luat_rtos.h"
#include "luat_mobile.h"
#include "luat_debug.h"

#define MOBILE_CELL_REFRESH_TIME    120 * 1000

static luat_rtos_task_handle task_mobile_handle;
static luat_mobile_cell_info_t s_cell_info;
extern int luat_mobile_sms_event_register_handler(luat_mobile_sms_event_callback_t callback_fun);

static void sms_event_cb(uint32_t event, void *param)
{
	LUAT_DEBUG_PRINT("短信 event%d,%x",event, param);
}

static void mobile_event_cb(LUAT_MOBILE_EVENT_E event, uint8_t index, uint8_t status)
{
	luat_mobile_signal_strength_info_t signal_info;
	uint16_t mcc;
	uint8_t csq, i, mnc;
	char imsi[20];
	char iccid[24] = {0};
	char apn[32] = {0};
	ip_addr_t ipv4;
	ip_addr_t ipv6;
	int result;
	switch(event)
	{
	case LUAT_MOBILE_EVENT_CFUN:
		LUAT_DEBUG_PRINT("CFUN消息，status %d", status);
		break;
	case LUAT_MOBILE_EVENT_SIM:
		if (status != LUAT_MOBILE_SIM_NUMBER)
		{
			LUAT_DEBUG_PRINT("SIM卡消息，卡槽%d", index);
		}
		switch(status)
		{
            case LUAT_MOBILE_SIM_READY:
                LUAT_DEBUG_PRINT("SIM卡正常工作");
                luat_mobile_get_iccid(index, iccid, sizeof(iccid));
                LUAT_DEBUG_PRINT("ICCID %s", iccid);
                luat_mobile_get_imsi(index, imsi, sizeof(imsi));
                LUAT_DEBUG_PRINT("IMSI %s", imsi);
                luat_mobile_get_plmn_from_imsi(imsi, &mcc, &mnc);
                result = luat_mobile_get_isp_from_plmn(mcc, mnc);
                switch(result)
                {
                    case LUAT_MOBILE_ISP_CMCC:
                        LUAT_DEBUG_PRINT("中国移动卡");
                        break;
                    case LUAT_MOBILE_ISP_CTCC:
                        LUAT_DEBUG_PRINT("中国电信卡");
                        break;
                    case LUAT_MOBILE_ISP_CUCC:
                        LUAT_DEBUG_PRINT("中国联通卡");
                        break;
                    case LUAT_MOBILE_ISP_CRCC:
                        LUAT_DEBUG_PRINT("中国广电卡");
                        break;
                    case LUAT_MOBILE_ISP_UNKNOW:
                        LUAT_DEBUG_PRINT("未知运营商");
                        break;
                    default:
                        LUAT_DEBUG_PRINT("非中国卡");
                        break;
                }
                break;
            case LUAT_MOBILE_NO_SIM:
                LUAT_DEBUG_PRINT("SIM卡不存在");
                break;
            case LUAT_MOBILE_SIM_NEED_PIN:
                LUAT_DEBUG_PRINT("SIM卡需要输入PIN码");
                break;
		}
		break;
	case LUAT_MOBILE_EVENT_REGISTER_STATUS:
		LUAT_DEBUG_PRINT("移动网络服务状态变更，当前为%d", status);
		break;
	case LUAT_MOBILE_EVENT_CELL_INFO:
		switch(status)
		{
		case LUAT_MOBILE_CELL_INFO_UPDATE:
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
			break;
		case LUAT_MOBILE_SIGNAL_UPDATE:
			LUAT_DEBUG_PRINT("服务小区信号状态变更");
			luat_mobile_get_last_notify_signal_strength_info(&signal_info);
			luat_mobile_get_last_notify_signal_strength(&csq);
			if (signal_info.luat_mobile_lte_signal_strength_vaild)
			{
				LUAT_DEBUG_PRINT("rsrp %d, rsrq %d, snr %d, rssi %d, csq %d %d", signal_info.lte_signal_strength.rsrp,
						signal_info.lte_signal_strength.rsrq, signal_info.lte_signal_strength.snr,
						signal_info.lte_signal_strength.rssi, csq, luat_mobile_rssi_to_csq(signal_info.lte_signal_strength.rssi));
			}

			break;
		}
		break;
	case LUAT_MOBILE_EVENT_PDP:
		LUAT_DEBUG_PRINT("CID %d PDP激活状态变更为 %d", index, status);
		break;
	case LUAT_MOBILE_EVENT_NETIF:
		LUAT_DEBUG_PRINT("internet工作状态变更为 %d,cause %d", status,index);
		switch (status)
		{
            case LUAT_MOBILE_NETIF_LINK_ON:
                LUAT_DEBUG_PRINT("net ready");
                if (luat_mobile_get_apn(0, 0, apn, sizeof(apn)))
                {
                    LUAT_DEBUG_PRINT("默认apn %s", apn);
                }
                luat_mobile_get_local_ip(0, 1, &ipv4, &ipv6);
                if (ipv4.type != 0xff)
                {
                    LUAT_DEBUG_PRINT("IPV4 %s", ip4addr_ntoa(&ipv4.u_addr.ip4));
                }
                if (ipv6.type != 0xff)
                {
                    LUAT_DEBUG_PRINT("IPV6 %s", ip6addr_ntoa(&ipv4.u_addr.ip6));
                }
                break;
            default:
                LUAT_DEBUG_PRINT("不能上网");
                break;
		}
		break;
	case LUAT_MOBILE_EVENT_TIME_SYNC:
		if (!status)
		{
			LUAT_DEBUG_PRINT("通过移动网络同步了UTC时间");
		}
		else
		{
			LUAT_DEBUG_PRINT("移动网络同步UTC时间出错");
		}

		break;
	case LUAT_MOBILE_EVENT_CSCON:
		LUAT_DEBUG_PRINT("RRC状态 %d", status);
		break;
	case LUAT_MOBILE_EVENT_FATAL_ERROR:
		LUAT_DEBUG_PRINT("网络也许遇到问题，15秒内不能恢复的建议重启协议栈");
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
        } else {
            offset += snprintf(result + offset, result_size - offset, "%d", band1[i]);
        }
    }
}


void mobile_get_imei(void)
{
	int i;
	char imei[20] = {0};
	luat_mobile_get_imei(0, imei, sizeof(imei));
	LUAT_DEBUG_PRINT("IMEI %s", imei);
}

void mobile_set_sn(char *newSn)
{
	luat_mobile_set_sn(newSn, 32);
	char sn[33] = {0};
	luat_mobile_get_sn(sn, sizeof(sn));
	LUAT_DEBUG_PRINT("SN %s", sn);
}

void mobile_get_muid(void)
{
	char muid[64] = {0};
	luat_mobile_get_muid(muid, sizeof(muid));
	LUAT_DEBUG_PRINT("MUID %s", muid);
}

void mobile_get_band(void)
{
	uint8_t band[32];
	uint8_t total_num;
	luat_mobile_get_band(band, &total_num);
    char buf[128];
    mobile_get_band_string(band, total_num, buf, sizeof(buf));
    LUAT_DEBUG_PRINT("%s", buf);
}

void mobile_get_cell_info(void)
{
	luat_mobile_cell_info_t  cell_info;
    luat_mobile_get_cell_info_async(6);
    luat_rtos_task_sleep(15 * 1000);
    luat_mobile_get_cell_info(&cell_info);

    if (cell_info.lte_service_info.cid)
    {
        LUAT_DEBUG_PRINT("服务小区信息 mcc %x mnc %x cellid %u band %d tac %u pci %u earfcn %u is_tdd %d rsrp %d rsrq %d snr %d rssi %d",
                cell_info.lte_service_info.mcc, cell_info.lte_service_info.mnc, cell_info.lte_service_info.cid,
                cell_info.lte_service_info.band, cell_info.lte_service_info.tac, cell_info.lte_service_info.pci, cell_info.lte_service_info.earfcn,
                cell_info.lte_service_info.is_tdd, cell_info.lte_service_info.rsrp, cell_info.lte_service_info.rsrq,
                cell_info.lte_service_info.snr, cell_info.lte_service_info.rssi);
    }
    for (int i = 0; i < cell_info.lte_neighbor_info_num; i++)
    {
        if (cell_info.lte_info[i].cid)
        {
            LUAT_DEBUG_PRINT("邻小区 %d mcc %x mnc %x cellid %u tac %u pci %u", i + 1, cell_info.lte_info[i].mcc,
                    cell_info.lte_info[i].mnc, cell_info.lte_info[i].cid, cell_info.lte_info[i].tac, cell_info.lte_info[i].pci);
            LUAT_DEBUG_PRINT("邻小区 %d earfcn %u rsrp %d rsrq %d snr %d", i + 1, cell_info.lte_info[i].earfcn, cell_info.lte_info[i].rsrp,
                    cell_info.lte_info[i].rsrq, cell_info.lte_info[i].snr);
        }
    }
}

static void mobile_main_routine(void *param)
{
    // 这几个不放到task里面要死；完了直接退也要死，真他妈恶心
    mobile_get_imei();
    mobile_get_muid();
    mobile_get_band();

	while(1)
	{
        luat_rtos_task_sleep(1000);
		// luat_rtos_task_sleep(MOBILE_CELL_REFRESH_TIME);
        // mobile_get_cell_info();
	}
}

void task_mobile(void)
{
	luat_mobile_event_register_handler(mobile_event_cb);
	luat_mobile_sms_event_register_handler(sms_event_cb);

	luat_mobile_set_period_work(90000, 5000, 4);	//90秒搜索基站间隔，5秒sim卡脱离的尝试恢复间隔，每次基站搜索最大4s
	luat_mobile_set_check_network_period(120000);   // 设置定时检测网络是否正常并且在检测到长时间无网时通过重启协议栈来恢复，但是不能保证一定成功

	luat_mobile_set_sim_detect_sim0_first();        // 优先sim 0
    luat_mobile_set_sync_time(1);                   // 0，表示禁用基站同步时间，传入1，表示启用基站同步时间

	luat_rtos_task_create(&task_mobile_handle, 8*1024, 40, "task_mobile", mobile_main_routine, NULL, 32);
}

void mobile_deinit(void)
{
    luat_rtos_task_suspend(task_mobile_handle);
    luat_rtos_task_delete(task_mobile_handle);

    luat_mobile_event_deregister_handler();
}