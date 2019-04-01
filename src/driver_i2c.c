

/*
@File Name	: myI2C.h
@Description: I2C file Wrapper function  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/17/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/


#include"driver_i2c.h"


int8_t open_i2c_bus()
{
	int8_t adapter_no = ADAPTER_NUM; 
	int fd;
	char i2c_file[20];
	
	snprintf(i2c_file,sizeof(i2c_file),"/dev/i2c-%d", adapter_no);
	if((fd = open(i2c_file,O_RDWR)) < 0)
	{
		
		return ERROR;
	}
	return fd;
}

int8_t close_i2c_bus(int8_t fd)
{
	if(close(fd) < 0)
	{
		perror("Failed to close I2C bus");
		return ERROR;
	}
	printf("Closing I2C bus\n");
	return SUCCESS;
}
