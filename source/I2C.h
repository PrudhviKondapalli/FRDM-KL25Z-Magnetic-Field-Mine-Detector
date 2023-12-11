#ifndef _I2C_H
#define _I2C_H

void i2c_write_byte(uint8_t address, uint8_t regaddress, uint8_t data);
uint8_t i2c_read_byte(uint8_t address, uint8_t regaddress);
int i2c_read_bytes(uint8_t device_address, uint8_t reg_address, uint8_t *data, int8_t data_count);
void status_config(void);
int status_register_ready_check(void);
void i2c_init(void);

#endif
