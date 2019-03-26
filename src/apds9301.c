/*
@File Name	: apds9301.c
@Description: APDS9301 sensor function  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/17/2019
*/


#include"apds9301.h"

/*
@description: opens a file descriptor to I2C bus
@return 	: returns a file desriptor
*/
int apds9301_open()
{

int fd;
	fd = open_i2c_bus();

	if(fd < 0)
	{
		perror("APDS9301 ERROR: open I2C bus");
		return ERROR;
	}
	if(ioctl(fd,I2C_SLAVE,APDS9301_SLAVE_ADDR) < 0)
	{
		perror("APDS9301 ERROR: Open IOCTL");
		return ERROR;
	}

	return fd;
}

/*
@description: close a file descriptor to I2C bus
@param		: file descriptor 
@return 	: in type (SUCCESS or FAILURE)
*/
int apds9301_close(int fd)
{
	if(close(fd) < 0)
	{
		perror("APDS9301 ERROR: Close File Descriptor");
		return ERROR;
	}
	return SUCCESS;
}
/*
@description: Initialize the sensor
@param		:
@return 	: SUCCESS or ERROR
*/
return_status apds9301_setup()
{
	uint8_t data = apds9301_read_reg_1byte(APDS9301_REG_CTRL);
	printf("Poweron setup %x\n",data);

	if(apds9301_read_reg_1byte(APDS9301_REG_ID) != 0x50)
	{
		perror("APDS9301 ERROR: ID Read");
		return ERROR;
	}
	return SUCCESS;

}

/*
@description: power on the sensor
@param		:
@return 	: SUCCESS or ERROR
*/

return_status apds9301_power_on()
{
	if(apds9301_write_reg(APDS9301_REG_CTRL, 0x03) < 0)
	{
		perror("ERROR : Power On");
		return ERROR;
	}
	uint8_t data = apds9301_read_reg_1byte(APDS9301_REG_CTRL);
	printf("Poweron read %x\n",data);
	return SUCCESS;
}

/*
@description: write value to register
@param		:addr of register and value
@return 	: SUCCESS or ERROR
*/

return_status apds9301_write_reg(uint8_t addr, uint8_t value)
{
	int fd;
	uint16_t buff;
	fd = apds9301_open();
	if(fd < 0)
	{
		return ERROR;
	}
	buff = apds9301_data_align(addr,value);
	fd = write(fd,&buff,(sizeof(buff)));
	if(fd == ERROR)
	{
		perror("APDS9301 ERROR: Write fail file descriptor APDS9301");
		return ERROR;
	}
	if(apds9301_close(fd) == ERROR)
		return ERROR;
	return SUCCESS;
}

/*
@description: read register of TMP102
@param		: address of register
@return 	: uint16_t Buffer containing reg value
*/
uint8_t apds9301_read_reg_1byte(uint8_t addr)
{
	int fd;
	uint8_t buff;
	fd = apds9301_open();
	if(fd == ERROR)
	{
		return ERROR;
	}
	if(write(fd, &addr,sizeof(addr)) < 0)
	{
		perror("APDS9301 ERROR: Write fail file descriptor");
		return ERROR;
	}

	if(read(fd, &buff,sizeof(buff)) < 0)
	{
		perror("APDS9301 ERROR: read fail file descriptor");
		return ERROR;
	}
	if(apds9301_close(fd) == ERROR)
		return ERROR;
	return buff;
}

/*
@description: read register of TMP102
@param		: address of register
@return 	: uint16_t Buffer containing reg value
*/
uint16_t apds9301_read_reg_2byte(uint8_t addr)
{
	int fd;
	uint16_t buff;
	fd = apds9301_open();
	if(fd == ERROR)
	{
		return ERROR;
	}
	if(write(fd, &addr,1) < 0)
	{
		perror("APDS9301 ERROR: Write fail file descriptor");
		return ERROR;
	}

	if(read(fd, &buff,2) < 0)
	{
		perror("APDS9301 ERROR: read fail file descriptor");
		return ERROR;
	}
	if(apds9301_close(fd) == ERROR)
		return ERROR;
	return buff;
}

/*
@description: get lux
@param		: 
@return 	: lux
*/
float getLuminosity()
{

	float lux = 0.0;
	uint16_t Ch1= 0, Ch2 =0;
	uint16_t data1, data0;
	float ratio_ch2_ch1;
	apds9301_write_reg(APDS9301_REG_TIMING,(APDS9301_REG_TIMING_GAIN | APDS9301_REG_TIMING_INTEG(0x00)));
	
	Ch1 = apds9301_read_reg_2byte(APDS9301_REG_CMD_WORD | APDS9301_REG_DATA0_LOW);
	//usleep(100000);
	Ch2 = apds9301_read_reg_2byte(APDS9301_REG_CMD_WORD | APDS9301_REG_DATA1_LOW);
	//usleep(100000);
	//printf("CH1 = %d , CH2 %d\n",Ch1,Ch2);
	if(Ch1 != 0)
		ratio_ch2_ch1= (float)Ch2/(float)Ch1;
	else 
		ratio_ch2_ch1 = 0;
	
	if (ratio_ch2_ch1 > 0 && ratio_ch2_ch1 <= 0.50)
	{
		lux = 0.0304*Ch1 - 0.062*Ch1*(pow(ratio_ch2_ch1,1.4));
	}
	else if (ratio_ch2_ch1 > 0.50 && ratio_ch2_ch1 <= 0.61)
	{
		lux = 0.0224*Ch1 - 0.031*Ch2;
	}
	else if (ratio_ch2_ch1 > 0.61 && ratio_ch2_ch1 <= 0.80)
	{
		lux = 0.0128*Ch1 - 0.0153*Ch2;
	}
	else if (ratio_ch2_ch1 > 0.80 && ratio_ch2_ch1 <= 1.30)
	{
		lux = 0.00146*Ch1 - 0.00112*Ch2;
	}
	else if (ratio_ch2_ch1 > 1.30)
	{
		lux = 0;
  }
  //printf("LUX is %f\n",lux);
    return lux;
}

/*
@description: decide day or night based on lux
@param		: 
@return 	: day or night
*/
light is_Day_or_Night()
{
	float lux = getLuminosity();
	if(lux > THRESHOLD_D_N)
		return DAY;
	else
		return NIGHT;
}

/*
@description: align data in format 
@param		: addr and value
@return 	: aligned data
*/

uint16_t apds9301_data_align(uint8_t addr,uint8_t value)
{
	uint16_t data;
	data = ((value <<8) | addr);
	return data;
}
