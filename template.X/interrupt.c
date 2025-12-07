#include "common.h"

volatile pisr int_pisr = NULL;
volatile char int_edg = 0;

volatile pisr timer_pisr[TIMER_NUM+1] = {NULL};
volatile unsigned char timer_ckps[TIMER_NUM+1] = {0};
volatile unsigned short timer_interval[TIMER_NUM+1] = {0};

void isr_dummy()
{}

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
    
    if( int_pisr == NULL ){
        // コンパイル時のwarning表示防止
        config_int(NULL,0);
        int_pisr = isr_dummy;
        return;
    }
    
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
    if( pisr == NULL ) return;
    int_pisr = pisr;
    int_edg = edg;
}


//
// タイマー割り込み
//
// 4Mhz で駆動しているのでタイマーのカウントアップ間隔 = prescale*1/(FOSC/4) = prescale*1/(4/4*10^6) = prescale マイクロ秒
//

void start_timer1()
{
    T1CONbits.TMR1CS = 0b00; // クロック = FOSC/4
    PIE1bits.TMR1IE = 1; // タイマー 割り込み許可
    T1CONbits.TMR1ON = 1; // タイマー 有効化
}

void start_timer3()
{
    T3CONbits.TMR3CS = 0b00; // クロック = FOSC/4
    PIE3bits.TMR3IE = 1; // タイマー 割り込み許可
    T3CONbits.TMR3ON = 1; // タイマー 有効化
}

void start_timer5()
{
    T5CONbits.TMR5CS = 0b00; // クロック = FOSC/4
    PIE4bits.TMR5IE = 1; // タイマー 割り込み許可
    T5CONbits.TMR5ON = 1; // タイマー 有効化
}

void init_timer_impl(const int no)
{
    if( timer_pisr[no] == NULL ) return;

    printf("-----\r\nTIMER:\r\n");
    printf("timer = %d\r\n",no);

    // 全割り込み処理不可
    INTCONbits.GIE = 0;

    if( no == 1) start_timer1();
    if( no == 3) start_timer3();
    if( no == 5) start_timer5();

    // 周辺割り込み許可
    INTCONbits.PEIE = 1;
    
    // 全割り込み処理許可
    INTCONbits.GIE = 1; 
}

void init_timer(void)
{
    if( timer_pisr[1] == NULL ){
        // コンパイル時のwarning表示防止
        config_timer1(NULL);
        timer1(0);
        timer_pisr[1] = isr_dummy;
    }
    else init_timer_impl(1);
        
    if( timer_pisr[3] == NULL ){
        // コンパイル時のwarning表示防止
        config_timer3(NULL);
        timer3(0);
        timer_pisr[3] = isr_dummy;
    }
    else init_timer_impl(3);
    
    if( timer_pisr[5] == NULL ){
        // コンパイル時のwarning表示防止
        config_timer5(NULL);
        timer5(0);
        timer_pisr[5] = isr_dummy;
    }
    else init_timer_impl(5);
}

void config_timer1(const pisr pisr)
{
    if( pisr == NULL ) return;
    timer_pisr[1] = pisr;
}

void config_timer3(const pisr pisr)
{
    if( pisr == NULL ) return;
    timer_pisr[3] = pisr;
}

void config_timer5(const pisr pisr)
{
    if( pisr == NULL ) return;
    timer_pisr[5] = pisr;
}

void set_timer_parameter(const int no, const long interval)
{
    long interval2 = (interval > 65535*8 ? 65535*8 : interval);
    long prescale = 0;

    if( interval2 <= 65535 ) prescale = 1;
    else if( interval2 <= 65535*2 ) prescale = 2;
    else if( interval2 <= 65535*4 ) prescale = 4;
    else prescale = 8;
    
    timer_ckps[no] = 0b00;
    if( prescale == 2 ) timer_ckps[no] = 0b01;
    if( prescale == 4 ) timer_ckps[no] = 0b10;
    if( prescale == 8 ) timer_ckps[no] = 0b11;  
    timer_interval[no] = (unsigned short)(interval2/prescale); 
}

void set_timer1()
{
    T1CONbits.T1CKPS = timer_ckps[1];
    TMR1 = 65535-timer_interval[1];
    PIR1bits.TMR1IF = 0; // タイマー 割り込みフラグリセット
}

void set_timer3()
{
    T3CONbits.T3CKPS = timer_ckps[3]; // prescale = 1 or 2 or 4 or 8
    TMR3 = 65535-timer_interval[3];
    PIR3bits.TMR3IF = 0; // タイマー 割り込みフラグリセット
}

void set_timer5()
{
    T5CONbits.T5CKPS = timer_ckps[5]; // prescale = 1 or 2 or 4 or 8
    TMR5 = 65535-timer_interval[5];
    PIR4bits.TMR5IF = 0; // タイマー 割り込みフラグリセット
}

void timer1(const long interval)
{
    set_timer_parameter(1,interval);
    set_timer1();
}

void timer3(const long interval)
{
    set_timer_parameter(3,interval);
    set_timer3();
}

void timer5(const long interval)
{
    set_timer_parameter(5,interval);
    set_timer5();
}

