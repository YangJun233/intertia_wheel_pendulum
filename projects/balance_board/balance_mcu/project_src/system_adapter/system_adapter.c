#include "system_adapter.h"


/*************************************************************************************************\
 * profile adapter
 */

/** delay adapter */
delay_adapter_s g_delay_adapter = 
{
    .p_delay_ms = HAL_Delay,
    .p_delay_us = NULL,
};


/*************************************************************************************************\
 * driver adapter
 */

/** key adapter*/
key_attribute_s key_attribute[2] = 
{
    {false, NULL},
    {false, NULL},
};
key_adapter_s g_key_adapter =
{
    .key_nums               = 2,
    .p_key_attribute        = key_attribute,
    .p_get_key_pin_state    = get_key_pin_state,
};


/** led adapter*/
led_adapter_s g_led_adapter = 
{
    .led_on_state           = true,
    .p_set_led_pin_state    = set_led_pin_state,
    .p_toggle_led_pin_state = toggle_led_pin_state,
};


/** mpu6050 adapter*/
mpu6050_adapter_s g_mpu6050_adapter = 
{
    .iic_addr_7bit = MPU6050_ADDRESS_AD0_LOW,

    .mpu_config = 
    {
		.gyro_fsr 		= FSR_500DPS,
		.gyro_lpf		= GYRO_FILTER_98HZ,
		.gyro_offset 	= {0, 0, 0},

		.accel_fsr 		= FSR_4G,
		.accel_lpf 		= ACCEL_FILTER_40HZ,
		.accel_offset 	= {0, 0, 0},

		.axis_config = 
		{
			.axis_map 		= AXIS_MAP_XYZ,
			.axis_direction = 
			{
				.AXIS_INV_X = 0,
				.AXIS_INV_Y = 0,
				.AXIS_INV_Z = 0,
			},
		},
    },

    .p_write_byte 	= mpu6050_iic_write_byte,
    .p_read_byte 	= mpu6050_iic_read_byte,
    .p_write_bytes 	= mpu6050_iic_write_bytes,
    .p_read_bytes	= mpu6050_iic_read_bytes,
};

/** oled adapter*/
oled_adapter_s g_oled_adapter = 
{
    .p_write_byte   = oled_iic_write_byte,
    .p_write_bytes  = oled_iic_write_bytes,
    .p_rst_contronl = NULL,
};

/** motor adapter*/
motor_adapter_s g_motor_adapter = 
{
    .motor_num = 2,
    .p_motor_en = motor_en,
    .p_motor_dir = motor_dir,
    .p_get_encoder_cnt = get_encoder_cnt,
    .p_pwm_set = motor_pwm_set,
};

/*************************************************************************************************\
 * algorithm adapter
 */
