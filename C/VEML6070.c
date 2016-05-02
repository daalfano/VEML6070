// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// VEML6070
// This code is designed to work with the VEML6070_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, VEML6070 I2C address is 0x38(56)
	ioctl(file, I2C_SLAVE, 0x38);

	// Select command register(0x02)
	// Integration time = 0.5T, shutdown mode disabled
	char config[1] = {0};
	config[0] = 0x02;
	write(file, config, 1);
	sleep(1);

	// Read 2 bytes of data
	// Read uvlight msb from register(0x73)
	char reg[1] = {0x73};
	write(file, reg, 1);
	char data[1] = {0};
	if(read(file, data, 1) != 1)
	{
		printf("Erorr : Input/output Erorr \n");
		exit(1);
	}
	int data_0 = data[0];

	// Read uvlight lsb from register(0x71)
	reg[0] = 0x71;
	write(file, reg, 1);
	read(file, data, 1);
	int data_1 = data[0];

	// Convert the data 
	int uvlight = (data_0 * 256 + data_1);

	// Output to screen
	printf("UV Light of The Device : %d \n", uvlight);
}
