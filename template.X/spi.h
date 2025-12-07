#pragma once

void init_spi(void);
void config_spi(const char mode, const char smp);
void spi_putch( const char data );
const char spi_getch(void);