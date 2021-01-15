#include "hardware_platform_adapter.h"
#include "main.h"

/*************************************************************************************************\
 * hardware platform adapter
 */
/** key adapter*/
bool get_key_pin_state(uint8_t idx)
{
    bool ret;
    
    switch(idx)
    {
        case 0:
            ret = HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
            break;
        case 1:
            ret = HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
            break;
        default:
            break;
    }
    
    return ret;
}

/** led adapter*/
void set_led_pin_state(uint8_t idx, bool pin_state)
{
    switch(idx)
    {
        case 0:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, pin_state);
            break;
        case 1:
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, pin_state);
            break;
        default:
            break;
    }
}

void toggle_led_pin_state(uint8_t idx)
{
    switch(idx)
    {
        case 0:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            break;
        case 1:
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
            break;
        default:
            break;
    }
}


/** mpu6050 adapter*/
extern I2C_HandleTypeDef hi2c1;
bool mpu6050_iic_write_byte(uint8_t iic_addr, uint8_t reg, uint8_t data)
{
    if(HAL_I2C_Mem_Write(&hi2c1, iic_addr<<1, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&data, 1, 0xFFFF) != HAL_OK)
    {
        return false;
    }
    
    return true;
}

uint8_t mpu6050_iic_read_byte(uint8_t iic_addr, uint8_t reg)
{
    uint8_t ret = 0;
    
    HAL_I2C_Mem_Read(&hi2c1, iic_addr<<1, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&ret, 1, 0xFFFF);
    
    return ret;
}

bool mpu6050_iic_write_bytes(uint8_t iic_addr, uint8_t reg, uint8_t *p_data, uint16_t size)
{
    if(HAL_I2C_Mem_Write(&hi2c1, iic_addr<<1, reg, I2C_MEMADD_SIZE_8BIT, p_data, size, 0xFFFF) != HAL_OK)
    {
        return false;
    }
    
    return true;
}

bool mpu6050_iic_read_bytes(uint8_t iic_addr, uint8_t reg, uint8_t *p_data, uint16_t size)
{
    if(HAL_I2C_Mem_Read(&hi2c1, iic_addr<<1, reg, I2C_MEMADD_SIZE_8BIT, p_data, size, 0xFFFF) != HAL_OK)
    {
        return false;
    }
    
    return true;
}


/** oled adapter*/
#define OLED_SCL_Clr() HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, GPIO_PIN_RESET)//SCL
#define OLED_SCL_Set() HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, GPIO_PIN_SET)

#define OLED_SDA_Clr() HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, GPIO_PIN_RESET)//DIN
#define OLED_SDA_Set() HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, GPIO_PIN_SET)

//延时
static void IIC_delay(void)
{
    uint8_t t=1;
    while(t--);
}

//起始信号
static void I2C_Start(void)
{
    OLED_SDA_Set();
    OLED_SCL_Set();
    IIC_delay();
    OLED_SDA_Clr();
    IIC_delay();
    OLED_SCL_Clr();
    IIC_delay();
}

//结束信号
static void I2C_Stop(void)
{
    OLED_SDA_Clr();
    OLED_SCL_Set();
    IIC_delay();
    OLED_SDA_Set();
}

//等待信号响应
static void I2C_WaitAck(void) //测数据信号的电平
{
    OLED_SDA_Set();
    IIC_delay();
    OLED_SCL_Set();
    IIC_delay();
    OLED_SCL_Clr();
    IIC_delay();
}

//写入一个字节
static void Send_Byte(uint8_t dat)
{
    uint8_t i;
    for(i=0; i<8; i++)
    {
        if(dat&0x80)//将dat的8位从最高位依次写入
        {
            OLED_SDA_Set();
        }
        else
        {
            OLED_SDA_Clr();
        }
        IIC_delay();
        OLED_SCL_Set();
        IIC_delay();
        OLED_SCL_Clr();//将时钟信号设置为低电平
        dat<<=1;
    }
}

//发送一个字节
//mode:数据/命令标志 0,表示命令;1,表示数据;
void oled_iic_write_byte(uint8_t dat, uint8_t mode)
{
    I2C_Start();
    Send_Byte(0x78);
    I2C_WaitAck();
    if(mode) {
        Send_Byte(0x40);
    }
    else {
        Send_Byte(0x00);
    }
    I2C_WaitAck();
    Send_Byte(dat);
    I2C_WaitAck();
    I2C_Stop();
}

void oled_iic_write_bytes(uint8_t * p_data, uint8_t size, uint8_t mode)
{
    I2C_Start();
    Send_Byte(0x78);
    I2C_WaitAck();
    if(mode) {
        Send_Byte(0x40);
    }
    else {
        Send_Byte(0x00);
    }
    I2C_WaitAck();
    for(int i=0; i<size; i++)
    {
        Send_Byte(p_data[i]);
        I2C_WaitAck();
    }
    I2C_Stop();
}


/** motor adapter*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void motor_en(uint8_t idx, bool en)
{
    switch(idx)
    {
        case MOTOR_NO_X:
            HAL_GPIO_WritePin(MOTOR_X_EN_GPIO_Port, MOTOR_X_EN_Pin, en);
            break;
        case MOTOR_NO_Y:
            HAL_GPIO_WritePin(MOTOR_Y_EN_GPIO_Port, MOTOR_Y_EN_Pin, en);
            break;
        default:
            break;
    }
}

void motor_dir(uint8_t idx, bool dir)
{
    switch(idx)
    {
        case MOTOR_NO_X:
            HAL_GPIO_WritePin(MOTOR_X_DIR_GPIO_Port, MOTOR_X_DIR_Pin, dir);
            break;
        case MOTOR_NO_Y:
            HAL_GPIO_WritePin(MOTOR_Y_DIR_GPIO_Port, MOTOR_Y_DIR_Pin, dir);
            break;
        case MOTOR_NO_Z:
            
            break;
        default:
            break;
    }
}

int get_encoder_cnt(uint8_t idx)
{
    int encoder_cnt = 0;
    
    switch(idx)
    {
        case MOTOR_NO_X:
            encoder_cnt = (int)__HAL_TIM_GET_COUNTER(&htim1);
            break;
        case MOTOR_NO_Y:
            encoder_cnt = (int)__HAL_TIM_GET_COUNTER(&htim2);
            break;
        case MOTOR_NO_Z:
            encoder_cnt = (int)__HAL_TIM_GET_COUNTER(&htim2);
            break;
        default:
            break;
    }
    
    return encoder_cnt;
}

void motor_pwm_set(uint8_t idx, uint16_t pwm)
{
    switch(idx)
    {
        case MOTOR_NO_X:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm);
            break;
        case MOTOR_NO_Y:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
            break;
        case MOTOR_NO_Z:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pwm);
            break;
        default:
            break;
    }
}











