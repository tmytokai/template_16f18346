#include "common.h"
#include "config.h"
#include "utils.h"
#include "uart.h"
#include "input.h"
#include "adc.h"
#include "pwm.h"

unsigned char PIN01_VDD = 0;
unsigned char PIN02_RA5 = 0;
unsigned char PIN03_RA4 = 0;
unsigned char PIN04_RA3 = 0;
unsigned char PIN05_RC5 = 0;
unsigned char PIN06_RC4 = 0;
unsigned char PIN07_RC3 = 0;
unsigned char PIN08_RC6 = 0;
unsigned char PIN09_RC7 = 0;
unsigned char PIN10_RB7 = 0;

unsigned char PIN11_RB6 = 0;
unsigned char PIN12_RB5 = 0;
unsigned char PIN13_RB4 = 0;
unsigned char PIN14_RC2 = 0;
unsigned char PIN15_RC1 = 0;
unsigned char PIN16_RC0 = 0;
unsigned char PIN17_RA2 = 0;
unsigned char PIN18_RA1 = 0;
unsigned char PIN19_RA0 = 0;
unsigned char PIN20_VSS = 0;

unsigned char INPUT_PULLUP = 1;

void pinconfig(void);
void run(void);
void init(void);

//
// !! 注意 !!!
//
// main.c も含めて Modules フォルダ内にあるソースの内容は編集しないこと
// pinconfig.c と run.c だけ編集する
//
void main(void)
{
    init();
    while (1) run();
    return;
}

void __interrupt () isr(void) 
{
    if( PIR1bits.TMR1IF ){
        adc_isr();
        PIR1bits.TMR1IF = 0;
    }
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
    
    PIN01_VDD = VDD;
    PIN02_RA5 = OUTPUT;
    PIN03_RA4 = OUTPUT;
    PIN04_RA3 = MCLR;
    PIN05_RC5 = OUTPUT;
    PIN06_RC4 = OUTPUT;   
    PIN07_RC3 = OUTPUT;
    PIN08_RC6 = OUTPUT;
    PIN09_RC7 = OUTPUT;
    PIN10_RB7 = OUTPUT;

    PIN11_RB6 = OUTPUT;
    PIN12_RB5 = OUTPUT;
    PIN13_RB4 = OUTPUT;
    PIN14_RC2 = OUTPUT;
    PIN15_RC1 = OUTPUT;
    PIN16_RC0 = OUTPUT;
    PIN17_RA2 = OUTPUT;
    PIN18_RA1 = ICSPCLK;
    PIN19_RA0 = ICSPDAT;
    PIN20_VSS = VSS;

    INPUT_PULLUP = 1;

    pinconfig();
    init_uart();
    init_input();
    init_adc();
    init_pwm();
    
    printf("-----\r\nrunning...\r\n");
}
