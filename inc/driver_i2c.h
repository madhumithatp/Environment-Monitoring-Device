/*
@File Name	: myI2C.h
@Description: I2C file Wrapper function  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/17/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/


#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include<fcntl.h>
#include<linux/i2c-dev.h>
#include<sys/ioctl.h>
#include<sys/stat.h>
//#include "error_handle.h"

#include<stdint.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include<errno.h>
#include <stddef.h>
#include <math.h>
#include<stdio.h>

#define ADAPTER_NUM (2)


typedef enum{

	ERROR	= -1,
	SUCCESS	= 1
}return_status;

/**************************************************************************************
@Function 	: int8_t open_i2c_bus()
@Description: Opens i2c bus 
@Return Type: int8_t new file descriptor(success), -1(failure)
*************************************************************************************/
int8_t open_i2c_bus(void);

/**************************************************************************************
@Function 	: void close_i2c_bus()
@Description: close i2c bus 
@Return Type: 1 (success), -1(failure)
*************************************************************************************/
int8_t close_i2c_bus(int8_t fd);

#endif
