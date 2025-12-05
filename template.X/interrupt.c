#include "common.h"

volatile pisr int_pisr = NULL;
volatile char int_edg = 0;

volatile pisr timer_pisr[TIMER_NUM+1] = {NULL};
volatile char timer_prescale[TIMER_NUM+1] = {0};
volatile unsigned timer_interval[TIMER_NUM+1] = {0};

void __interrupt () isr(void) 
{
    INTCONbits.GIE = 0;
    
    if(PIR0bits.INTF){
        (*int_pisr)();    
        PIR0bits.INTF = 0;
    }
    if( PIR1bits.TMR1IF ){
        (*timer_pisr[1])();
        TMR1 = 65535-timer_interval[1];
        PIR1bits.TMR1IF = 0;
    }
    if( PIR3bits.TMR3IF ){
        (*timer_pisr[3])();
        TMR3 = 65535-timer_interval[3];
        PIR3bits.TMR3IF = 0;
    }
    if( PIR4bits.TMR5IF ){
        (*timer_pisr[5])();
        TMR5 = 65535-timer_interval[5];
        PIR4bits.TMR5IF = 0;
    }
}

//
// INT 割り込み
//

void init_int(void)
{
    unsigned char porta = 0;
    unsigned char portb = 0;
    unsigned char portc = 0;
    
    if( int_pisr == NULL ) return;
    
    unsigned char num = get_pinMode(INT,&porta,&portb,&portc);
    if( num != 1 ) return;
    
    printf("-----\r\nINT:\r\n");
    printf("edg = %d, portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",int_edg,porta,portb,portc);
    
    set_inputpps(INT,porta,portb,portc);
    WPUA  |= porta;
    WPUB  |= portb;
    WPUC  |= portc;

    // 全割り込み処理不可
    INTCONbits.GIE = 0;
    
    INTCONbits.INTEDG = int_edg;
    
    // フラグリセット
    PIR0bits.INTF = 0;
    
    // INT 割り込み許可
    PIE0bits.INTE = 1;    
    
    // 全割り込み処理許可
    INTCONbits.GIE = 1; 
}

void config_int(const pisr pisr, const char edg)
{
    int_pisr = pisr;
    int_edg = edg;
}


//
// TIMER割り込み
//
// 4Mhz で駆動しているのでタイマーのカウントアップ間隔 = prescale*1/(FOSC/4) = prescale*1/(4/4*10^6) = prescale マイクロ秒
//

void init_timer_impl(const int no)
{
    if( timer_pisr[no] == NULL ) return;

    unsigned char ckps = 0b00;
    if( timer_prescale[no] == 2 ) ckps = 0b01;
    if( timer_prescale[no] == 4 ) ckps = 0b10;
    if( timer_prescale[no] == 8 ) ckps = 0b11;

    printf("-----\r\nTIMER%d:\r\n",no);
    printf("interval = %ld, prescale = %d, ckps = %d\r\n",(long)timer_interval[no]*timer_prescale[no],timer_prescale[no],ckps);

    // 全割り込み処理不可
    INTCONbits.GIE = 0;

    if( no == 1){
        T1CONbits.TMR1CS = 0b00; // クロック = FOSC/4
        T1CONbits.T1CKPS = ckps; // prescale = 1 or 2 or 4 or 8
        TMR1 = 65535-timer_interval[1];
        PIR1bits.TMR1IF = 0; // タイマー 割り込みフラグリセット
        PIE1bits.TMR1IE = 1; // タイマー 割り込み許可
        T1CONbits.TMR1ON = 1; // タイマー 有効化
    }
    if( no == 3){
        T3CONbits.TMR3CS = 0b00; // クロック = FOSC/4
        T3CONbits.T3CKPS = ckps; // prescale = 1 or 2 or 4 or 8
        TMR3 = 65535-timer_interval[3];
        PIR3bits.TMR3IF = 0; // タイマー 割り込みフラグリセット
        PIE3bits.TMR3IE = 1; // タイマー 割り込み許可
        T3CONbits.TMR3ON = 1; // タイマー 有効化
    }
    if( no == 5){
        T5CONbits.TMR5CS = 0b00; // クロック = FOSC/4
        T5CONbits.T5CKPS = ckps; // prescale = 1 or 2 or 4 or 8
        TMR5 = 65535-timer_interval[5];
        PIR4bits.TMR5IF = 0; // タイマー 割り込みフラグリセット
        PIE4bits.TMR5IE = 1; // タイマー 割り込み許可
        T5CONbits.TMR5ON = 1; // タイマー 有効化
    }
    
    // 周辺割り込み許可
    INTCONbits.PEIE = 1;
    
    // 全割り込み処理許可
    INTCONbits.GIE = 1; 
}

void init_timer(void)
{
    init_timer_impl(1);
    init_timer_impl(3);
    init_timer_impl(5);
    
    config_timer1(NULL,0); // コンパイル時のwaring表示防止
    config_timer3(NULL,0); // コンパイル時のwaring表示防止
}

void config_timer_impl(const int no, const pisr pisr, const long interval)
{
    if( pisr == NULL ) return;
    timer_pisr[no] = pisr;
    if( interval <= 65535 ) timer_prescale[no] = 1;
    else if( interval <= 65535*2 ) timer_prescale[no] = 2;
    else if( interval <= 65535*4 ) timer_prescale[no] = 4;
    else timer_prescale[no] = 8;
    timer_interval[no] = (unsigned short)(interval/timer_prescale[no]); 
}

void config_timer1(const pisr pisr, const long interval)
{
    config_timer_impl(1,pisr,interval);
}

void config_timer3(const pisr pisr, const long interval)
{
    config_timer_impl(3,pisr,interval);
}

void config_timer5(const pisr pisr, const long interval)
{
    config_timer_impl(5,pisr,interval);
}