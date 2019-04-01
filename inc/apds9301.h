/**
 * @file apds9301.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief APDS9301 sensor function
 * @version 0.1
 * @date 2019-03-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef APDS9301_H_
#define APDS9301_H_

#include"driver_i2c.h"


#define APDS9301_SLAVE_ADDR 		(0x39)

/*Register Addresss*/
#define APDS9301_REG_CMD			(0x80) // MSB = 1
#define APDS9301_REG_CTRL			(0x00) | APDS9301_REG_CMD
#define APDS9301_REG_TIMING			(0x01) | APDS9301_REG_CMD
#define APDS9301_REG_TH_LOW_LOW		(0x02) | APDS9301_REG_CMD
#define APDS9301_REG_TH_LOW_HIGH	(0X03) | APDS9301_REG_CMD
#define APDS9301_REG_TH_HIGH_LOW	(0x04) | APDS9301_REG_CMD
#define APDS9301_REG_TH_HIGH_HIGH	(0x05) | APDS9301_REG_CMD
#define APDS9301_REG_INT_TH			(0x06) | APDS9301_REG_CMD
#define APDS9301_REG_ID				(0x0A) | APDS9301_REG_CMD
#define APDS9301_REG_DATA0_LOW		(0x0C) | APDS9301_REG_CMD
#define APDS9301_REG_DATA0_HIGH		(0x0D) | APDS9301_REG_CMD
#define APDS9301_REG_DATA1_LOW		(0x0E) | APDS9301_REG_CMD
#define APDS9301_REG_DATA1_HIGH		(0x0F) | APDS9301_REG_CMD

/*Bits in Command Register*/
#define APDS9301_REG_CMD_WORD 		(1<<5)
#define APDS9301_REG_CMD_CLEAR		(1<<6)

/*Bits in CONTROL Register*/
#define APDS9301_REG_CTRL_P_ON		(0x03)
#define APDS9301_REG_CTRL_P_OFF		(0x00)

/*Bits in Timing Register*/
#define APDS9301_REG_TIMING_GAIN	(1<<4)
#define APDS9301_REG_TIMING_INTEG(x)((uint8_t)(x) & 0x03)
#define APDS9301_REG_TIMING_MAN(x)	(uint8_t)(x << 3) 

#define THRESHOLD_D_N 				(20)


/*Bits in IntERRORupt Register*/
#define APDS9301_REG_INT_TH_INTR(x)	((x << 4) & 0x30)

typedef enum light
{
	DAY,
	NIGHT,
}IsDay;
/*
@description: opens a file descriptor to I2C bus
@return 	: returns a file desriptor
*/
int apds9301_open();

/*
@description: close a file descriptor to I2C bus
@praram		: file descriptor 
@return 	: in type (SUCCESS or FAILURE)
*/
int apds9301_close(int fd);

/*
@description: Initialize the sensor
@praram		:
@return 	: SUCCESS or ERROR
*/
return_status apds9301_setup();


/*
@description: power on the sensor
@praram		:
@return 	: SUCCESS or ERROR
*/

return_status apds9301_power_on();


/*
@description: write value to register
@praram		:addr of register and value
@return 	: SUCCESS or ERROR
*/

return_status apds9301_write_reg(uint8_t addr, uint8_t value);


/*
@description: read register of TMP102
@praram		: address of register
@return 	: uint16_t Buffer containing reg value
*/
uint8_t apds9301_read_reg_1byte(uint8_t addr);

/*
@description: read register of TMP102
@praram		: address of register
@return 	: uint16_t Buffer containing reg value
*/
uint16_t apds9301_read_reg_2byte(uint8_t addr);

/**
 * @brief 
 * 
 * @param addr 
 * @param value 
 * @return return_status 
 */

return_status apds9301_write_reg_2byte(uint8_t addr, uint16_t value);

/*
@description: get lux
@praram		: 
@return 	: lux
*/
float getLuminosity();
/*
@description: decide day or night based on lux
@praram		: 
@return 	: day or night
*/
IsDay is_Day_or_Night(float lux);
/*
@description: align data in format 
@praram		: addr and value
@return 	: aligned data
*/

uint16_t apds9301_data_align(uint8_t addr,uint8_t value);
/**
 * @brief Calculate luminosity based on ch1 and ch2
 * 
 */
float calculateLuminosity(uint16_t Ch1 , uint16_t Ch2);

/**
 * @brief write 2 byte
 * 
 */



#endif /* APDS9301_H_ */
