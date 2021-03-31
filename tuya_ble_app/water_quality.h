#ifndef WATER_QUALITY_H_
#define WATER_QUALITY_H_

#include "tuya_ble_common.h"
#include "tuya_ble_log.h"

#define		GOOD	0
#define		COMMON	1
#define		POOR	2

void water_quality_fun(void);
int water_value_get(void);

#endif
