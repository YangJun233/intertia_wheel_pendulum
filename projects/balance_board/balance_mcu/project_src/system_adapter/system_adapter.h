#ifndef SYSTEM_ADAPTER_H
#define SYSTEM_ADAPTER_H

/*************************************************************************************************\
 * hardware platform adapter
 */
#include "hardware_platform_adapter.h"

/*************************************************************************************************\
 * profile adapter
 */
#include "delay_profile.h"

/*************************************************************************************************\
 * driver adapter
 */
#include "key.h"
#include "led.h"
#include "mpu6050.h"
#include "oled.h"
#include "motor.h"

/*************************************************************************************************\
 * algorithm adapter
 */


extern delay_adapter_s g_delay_adapter;
extern key_adapter_s g_key_adapter;
extern led_adapter_s g_led_adapter;
extern mpu6050_adapter_s g_mpu6050_adapter;
extern oled_adapter_s g_oled_adapter;

#endif // SYSTEM_ADAPTER_H
