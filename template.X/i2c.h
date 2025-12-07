#pragma once

void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_putch( const char data );
const char i2c_getch( const unsigned char nack );