/*
@File Name	: tmp102.h
@Description: tmp102 sensor function  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/13/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/

#ifndef TMP102_H_
#define TMP102_H_

#include "driver_i2c.h"
 

/*Slave Address*/
#define TMP102_SLAVE_ADDR 		(0x48)

/*Resolution of Temperature in degree Celcuis*/
#define RESOLUTION_C			(0.0625)
/*Configuration modes TMP102*/
#define	TMP_CONFIG_SD 	 		(1<<8)
#define	TMP_CONFIG_TM 	  		(1<<9)
#define	TMP_CONFIG_POL	  		(1<<10)
#define	TMP_CONFIG_EM 	  		(1<<4)
#define	TMP_CONFIG_AL 	  		(1<<5)
#define	TMP_CONFIG_CR(x)  		(x<<6)
#define TMP_CONFIG_FAULT(x)		(x<<11)

/* Register Address */

#define	TMP_REG_TEMPERATURE 		(0x00)
#define	TMP_REG_CONFIGURATION 		(0x01)
#define	TMP_REG_TLOW 			(0x02)
#define	TMP_REG_THIGH 			(0x03)

/*Unit Conversion Celcius to Kelvin and Farenheit*/
#define TMP_C_TO_K(x)				(float)((x)+273)
#define TMP_C_TO_F(x)				(float)(((x) * 1.8) + 32)

/*Byte swap to interchange MSB and LSB*/
#define SWAP_BYTES(num16)			(num16 = ((num16 << 8) & 0xFF00) | ((num16 >> 8 ) & 0x00FF))


/*enum for temperature units*/
typedef enum unit
{
	CELCIUS,			
	FARENHEIT, 				
	KELVIN,
}unit_temp;


/*
@description: opens a file descriptor to I2C bus
@return 	: returns a file desriptor
*/
int tmp102_open();

/*
@description: close a file descriptor to I2C bus
@praram		: file descriptor 
@return 	: in type (SUCCESS or FAILURE)
*/
int tmp102_close(int fd);

/*
@description:
@praram		:
@return 	:
*/

return_status tmp102_write_reg(uint8_t addr , uint16_t value);

/* Aligns Data with byte 0 = addr byte 1,2 = value */
uint32_t tmp102_data_align(uint8_t addr,uint16_t value);
/*
@description: read register of TMP102
@praram		: address of register
@return 	: uint16_t Buffer containing reg value
*/
uint16_t tmp102_read_reg(uint8_t addr);

/*
@description: Converts Register value to Digital Value
@praram		: uint16_t reg value
@return 	: 
*/
float regval_to_tempC(uint16_t regval);

/*
@description:Get temperature value from the temp reg
@praram		: unit in which temp is needed
@return 	: float temperature value
*/

float getTemperature(unit_temp unit);











#endif /* TMP102_H_ */
