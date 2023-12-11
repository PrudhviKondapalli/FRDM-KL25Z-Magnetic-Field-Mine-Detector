/**
 * Default Libraries allowed to be used
 */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "MKL25Z4.h"
#include "I2C.h"
#include "systick.h"
#include "mag_readings.h"

/**
 * User defined Macros
 */
#define I2C_START 		I2C1->C1 |= I2C_C1_MST_MASK
#define I2C_STOP 		I2C1->C1 &= ~I2C_C1_MST_MASK
#define I2C_RESTART		I2C1->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRANSFER	I2C1->C1 |= I2C_C1_TX_MASK
#define I2C_RECEIVE		I2C1->C1 &= ~I2C_C1_TX_MASK

#define I2C_WAIT		while((I2C1->S & I2C_S_IICIF_MASK)==0) {} \
								I2C1->S |= I2C_S_IICIF_MASK;
//#define I2C_WAIT_TIMEOUT_MS  10
//#define I2C_WAIT \
//    { \
//        uint32_t timeout = I2C_WAIT_TIMEOUT_MS * 1000; /* Timeout in microseconds */ \
//        while (((I2C1->S & I2C_S_IICIF_MASK) == 0) && (timeout > 0)) { \
//            timeout--; \
//        } \
//        I2C1->S |= I2C_S_IICIF_MASK; \
//    }

#define NACK			I2C1->C1 |= I2C_C1_TXAK_MASK
#define ACK				I2C1->C1 &= ~I2C_C1_TXAK_MASK

#define device_read_address    	(0x1B)
#define device_write_address	(0x1A)
#define control_reg1			(0x09)
#define control_reg2			(0x0A)
#define set_reset_reg			(0x0B)
#define data_ready_reg			(0x06)


int i2c_recieve_check = 0;
int i2c_ready_check = 0;
uint8_t data_buffer[7] = {0};
uint8_t status_buffer[7] = {0};
extern volatile int ticks_since_startup;


/**
 * @brief      {I2C1 Initialization for 400khz baud rate, configures hold,setup times and sets to master mode}
 * @type       {void}
 * @return     {None}
 * @Credits    {Alexander G. Dean - Chapter 8 - Embedded systems fundamentals}
 */
void i2c_init(void)
{
	//clock i2c1 and PTE0 = I2C1_SDA/D14/J2-18 and PTE1 = I2C1_SCL/D15/J2-20
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	//PCR controls the pin and ALT6 - is I2C1 alternate function on PTE0 and PTE1
	PORTE->PCR[0] |= PORT_PCR_MUX(6);
	PORTE->PCR[1] |= PORT_PCR_MUX(6);

	//set baud to 400k
	//I2C baud rate = bus speed (Hz)/(mul × SCL divider)
	//24Mhz/400Khz = 60; icr = 0x11, sets scl_div to 56 according to table 38-41I2C divider and hold values
	//SDA hold time = bus period (s) × mul × SDA hold value //set as 9us
	//SCL start hold time = bus period (s) × mul × SCL start hold value //set as 18us
	//SCL stop hold time = bus period (s) × mul × SCL stop hold value //set as 25us
	I2C1->F = I2C_F_ICR(0x11) | I2C_F_MULT(0);

	//Enable I2C and set to master mode
	I2C1->C1 |= (I2C_C1_IICEN_MASK);
	//Select high drive mask //Controls the drive capability of the I2C pads
	I2C1->C2 |= (I2C_C2_HDRS_MASK);
}

/**
 * @brief      {Write Byte function}
 * @type       {void}
 * @return     {None}
 * @Credits    {Alexander G. Dean - Chapter 8 - Embedded systems fundamentals}
 */
void i2c_write_byte(uint8_t address, uint8_t regaddress, uint8_t data)
{
	I2C_TRANSFER;
	//Transmit mode select -0 Receive, 1 Transmit
	I2C_START;
	//send start
	I2C1->D = address;
	//send device address on bus
	I2C_WAIT
	I2C1->D = regaddress;
	I2C_WAIT
	I2C1->D = data;
	//send data
	I2C_WAIT
	I2C_STOP;
}

uint8_t i2c_read_byte(uint8_t address, uint8_t regaddress)
{
	uint8_t data;
	I2C_TRANSFER;
	//set to transmit mode
	I2C_START;
	//Send start sequence
	I2C1->D = address;
	//send device address(write)
	I2C_WAIT

	I2C1->D = regaddress;
	//send register address
	I2C_WAIT

	I2C_RESTART;
	I2C1->D = (address|0x1);
	//send device address(read)
	I2C_WAIT

	I2C_RECEIVE;
	NACK;
	//Set to receive mode
	data = I2C1->D;
	//send Nack after read(by master)
	I2C_STOP;
	return data;

}

int i2c_read_bytes(uint8_t device_address, uint8_t reg_address, uint8_t *data, int8_t data_count)
{
	int16_t num_bytes_read = 0;
	I2C_TRANSFER;
	//set to transmit mode
	I2C_START;
	//Send start sequence
	I2C1->D = device_address;
	//send device address(write)
	I2C_WAIT

	I2C1->D = reg_address;
	//send register address
	I2C_WAIT

	//for(int i=0;i<1000;i++);

	I2C_RESTART;
	//I2C_START;
	I2C1->D = (device_address|0x1);
	//send device address(read)
	I2C_WAIT
	I2C_RECEIVE;
	ACK;
	data[0] = I2C1->D;
	I2C_WAIT;
	ACK;
	data[1] = I2C1->D;
	I2C_WAIT;
	ACK;
	data[2] = I2C1->D;
	I2C_WAIT;
	ACK;
	data[3] = I2C1->D;
	I2C_WAIT;
	ACK;
	data[4] = I2C1->D;
	I2C_WAIT;
	ACK;
	data[5] = I2C1->D;
	I2C_WAIT;
	NACK;
	data[6] = I2C1->D;
	I2C_WAIT;

	//data[6] = I2C1->D;
//	for(int i =0; i<data_count;i++)
//	{
//		data[i] = I2C1->D;
//		I2C_WAIT
//		if(i==(data_count-1))
//		{
//			NACK;
//		}
//		else
//		{
//			ACK;
//		}
//	}
	//loop should read until just the last byte of the data, last byte should be read with NACK
	//NACK;
	I2C_STOP;
	//send stop
	return 1;
}


int status_register_ready_check(void)
{
	i2c_ready_check = i2c_read_bytes(device_write_address,data_ready_reg,status_buffer,1);
	if((status_buffer[0] && 0b00000001) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


void status_config(void)
{
	i2c_write_byte(device_write_address,set_reset_reg,0x01);
	for(int i = 0;i<100;i++);
	i2c_write_byte(device_write_address,control_reg1,0x1D);
	for(int i = 0;i<100;i++);
	i2c_write_byte(device_write_address,control_reg2,0x40);
	for(int i = 0;i<100;i++);

	int data_available = status_register_ready_check();
	systick_enable();
	if(data_available == 1)
	{
		while(1)
			{
				if(get_timer_now() > 2)
				{
					i2c_recieve_check = i2c_read_bytes(device_write_address,0x00,data_buffer,6);
					convert_to_signed(data_buffer);
					mag_read();
					ticks_since_startup = 0;
				}
			}
	}
}



