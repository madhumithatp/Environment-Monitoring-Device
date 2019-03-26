/*
@File Name	: tmp102.c
@Description: tmp102.c  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/13/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/




#include "tmp102.h"


/*
@description: opens a file descriptor to I2C bus
@return 	: returns a file desriptor
*/
int tmp102_open()
{
	int fd;
	fd = open_i2c_bus();

	if(fd < 0)
	{
		perror("TMP 102 ERROR: open I2C bus");
		return ERROR;
	}
	if(ioctl(fd,I2C_SLAVE,TMP102_SLAVE_ADDR) < 0)
	{
		perror("TMP 102 ERROR: Open IOCTL");
		return ERROR;
	}

	return fd;
}

/*
@description: close a file descriptor to I2C bus
@praram		: file descriptor 
@return 	: int type (SUCCESS or FAILURE)
*/
int tmp102_close(int fd)
{
	if(close(fd) < 0)
	{
		perror("TMP 102 ERROR: Close File Descriptor");
		return ERROR;
	}
	return SUCCESS;
}

/*
@description: write value to register
@praram		: addr of register and value
@return 	: SUCCESS or ERROR
*/

return_status tmp102_write_reg(uint8_t addr , uint16_t value)
{

	int fd;
	uint32_t buff;

	/*MSB first*/
	SWAP_BYTES(value);

	fd = tmp102_open();
	if(fd < 0)
	{
		return ERROR;
	}
	/* Aligns Data with byte 0 = addr byte 1,2 = value */
	buff= tmp102_data_align(addr,value);
	// printf("Value written is %x",buff);
	/*writes up to  sizeof(buff)-1 bytes from the buffer to the file descriptor*/
	fd = write(fd,&buff,(sizeof(buff)-1));
	if(fd == ERROR)
	{
		perror("TMP 102 ERROR: Write fail file descriptor TMP102");
		return ERROR;
	}
	if(tmp102_close(fd) < 0)
		return ERROR;
} 


/*
@description: read register of TMP102
@praram		: address of register
@return 	: uint16_t Buffer containing reg value
*/
uint16_t tmp102_read_reg(uint8_t addr)
{
	int fd;
	uint16_t buff;
	fd = tmp102_open();
	if(fd < 0)
	{
		return ERROR;
	}
	if(write(fd, &addr,1)<0)
	{
		perror("TMP 102 ERROR: Write fail file descriptor");
		return ERROR;
	}

	if(read(fd, &buff,2)<0)
	{
		perror("TMP 102 ERROR: read fail file descriptor");
		return ERROR;
	}
	if(tmp102_close(fd) < 0 )
		return ERROR;		 
	SWAP_BYTES(buff);

	return buff;
}


/*
@description: align data in format 
@praram		: addr and value
@return 	: aligned data
*/
uint32_t tmp102_data_align(uint8_t addr,uint16_t value)
{
	uint32_t data;
	data = ( addr | (value <<8));
	return data;
}
/*
@description: Converts Register value to Digital Value
@praram		: uint16_t reg value
@return 	: 
*/
float regval_to_tempC(uint16_t regval)
{
		float tempval;
		/*Convert Value to 12 bits ignoring 4 least significant bits*/
		regval = regval >> 4  & 0x0FFF;
		
		/*Check Negative or Postive Temperature*/
		if(regval > 0x7FF)
		{ 
			tempval = (regval * RESOLUTION_C)- 256;
					
		}		
		else
			tempval = (regval * RESOLUTION_C);
		return tempval;
}

/*
@description:Get temperature value from the temp reg
@praram		: unit in which temp is needed
@return 	: float temperature value
*/

float getTemperature(unit_temp unit)
{
	uint16_t reg_value;
	float temperature = 0.0; 

	reg_value = tmp102_read_reg(TMP_REG_TEMPERATURE);
	temperature = regval_to_tempC(reg_value);
	switch(unit)
	{
		case CELCIUS:
			return temperature;
		case FARENHEIT:
			return TMP_C_TO_F(temperature);
		case KELVIN:
			return TMP_C_TO_K(temperature);
		default:
			return temperature;
	}

}
