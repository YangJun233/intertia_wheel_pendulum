#ifndef HARDWARE_PLATFORM_ADAPTER_H
#define HARDWARE_PLATFORM_ADAPTER_H

#include "sdk_include.h"

/** hardware platform adapter*/
#include "stm32f1xx_hal.h"
#include "main.h"
#include "motor.h"

bool get_key_pin_state(uint8_t idx);

void set_led_pin_state(uint8_t idx, bool pin_state);
void toggle_led_pin_state(uint8_t idx);

bool mpu6050_iic_write_byte(uint8_t iic_addr, uint8_t reg, uint8_t data);
uint8_t mpu6050_iic_read_byte(uint8_t iic_addr, uint8_t reg);
bool mpu6050_iic_write_bytes(uint8_t iic_addr, uint8_t reg, uint8_t *p_data, uint16_t size);
bool mpu6050_iic_read_bytes(uint8_t iic_addr, uint8_t reg, uint8_t *p_data, uint16_t size);

void oled_iic_write_byte(uint8_t dat, uint8_t mode);
void oled_iic_write_bytes(uint8_t * p_data, uint8_t size, uint8_t mode);

void motor_en(uint8_t idx, bool en);
void motor_dir(uint8_t idx, bool dir);
int get_encoder_cnt(uint8_t idx);
void motor_pwm_set(uint8_t idx, uint16_t pwm);

#endif // HARDWARE_PLATFORM_ADAPTER_H

