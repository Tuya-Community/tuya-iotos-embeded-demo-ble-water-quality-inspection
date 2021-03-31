#include "water_quality.h"

#define 	TIME_MS		1000
#define		BUF_LEN		((sizeof(DP_buf)) / (sizeof(DP_buf[0])))

unsigned long sys_time = 0;
uint8_t DP_buf[4] = {0x65, 0x04, 0x01, 0x00}; //{DP_ID, DP_type, DP_len, DP_data}

int water_value_get(void)
{
	uint16_t water_val;

	water_val = adc_sample_and_get_result();
	TUYA_APP_LOG_INFO("water_val:%d", water_val);

	return water_val;
}

void water_quality_fun(void)
{
	if(!clock_time_exceed(sys_time, 1000 * TIME_MS)){
		return;
	}

	sys_time = clock_time();
	lux_adc_init();

    if (water_value_get() >= 0x00 && water_value_get() <= 0x1E) {
        DP_buf[3] = GOOD;
        TUYA_APP_LOG_INFO("good_quality");
    } else if (water_value_get() > 0x1E && water_value_get() <= 0x64) {
        DP_buf[3] = COMMON;
        TUYA_APP_LOG_INFO("common_quality");
    } else {
        DP_buf[3] = POOR;
        TUYA_APP_LOG_INFO("poor_quality");
    }
    tuya_ble_dp_data_report(DP_buf, BUF_LEN);



}
