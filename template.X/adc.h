#pragma once

enum
{
    ADC_MAXCH = 20,
};

void init_adc(void);
void adc_isr(void);

extern volatile unsigned short adc_value[ADC_MAXCH+1];;

#define ANA5 adc_value[RA5PIN]
#define ANA4 adc_value[RA4PIN]
#define ANA3 adc_value[RA3PIN]
#define ANA2 adc_value[RA2PIN]
#define ANA1 adc_value[RA1PIN]
#define ANA0 adc_value[RA0PIN]

#define ANB7 adc_value[RB7PIN]
#define ANB6 adc_value[RB6PIN]
#define ANB5 adc_value[RB5PIN]
#define ANB4 adc_value[RB4PIN]

#define ANC7 adc_value[RC7PIN]
#define ANC6 adc_value[RC6PIN]
#define ANC5 adc_value[RC5PIN]
#define ANC4 adc_value[RC4PIN]
#define ANC3 adc_value[RC3PIN]
#define ANC2 adc_value[RC2PIN]
#define ANC1 adc_value[RC1PIN]
#define ANC0 adc_value[RC0PIN]
