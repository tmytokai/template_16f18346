#include "config.h"
#include "common.h"

void setup(void);
void run(void);
void init(void);

void main(void)
{
    init();
    while (1) run();
    return;
}

void init()
{
    // 周波数 = Freq/DIV = 4/1 = 4MHz
    OSCFRQbits.HFFRQ = 0b0011; // Freq=4Mhz
    OSCCON1bits.NDIV = 0b0000; // DIV = 1

    PORTA = 0x0;
    PORTB = 0x0;
    PORTC = 0x0;
    TRISA = 0x0;
    TRISB = 0x0;
    TRISC = 0x0;
    ANSELA = 0x0;
    ANSELB = 0x0;
    ANSELC = 0x0;
    
    init_pinMode();
    setup();
    init_uart();
    init_input();
    init_adc();
    init_pwm();
    init_spi();
    init_i2c();

    // 割り込み関係は最後に初期化
    init_int();
    init_timer();
    
    printf("-----\r\nrunning...\r\n");
}
