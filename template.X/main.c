#include "common.h"

// 例1. LED点滅
void setup(void)
{
    // pinMode(ピン名称(または番号),モード)
    //
    // モード
    // OUTPUT  : ディジタル出力 (デフォルト)
    // INPUT   : ディジタル入力 (内部弱プルアップ 無効)
    // INPUT_PULLUP   : ディジタル入力 (内部弱プルアップ 有効)
    // ADC     : アナログ入力 (10 bit)
    // PWM1〜4 : パルス幅変調 (3系統同時出力可)
    // TX      : シリアル通信 送信 (115200ボー)
    // RX      : シリアル通信 受信 (115200ボー)
    
    pinMode(PIN16_RC0,OUTPUT);
    // (補足) ピン番号を使って pinMode(16,OUTPUT); とすることも可能
    // (補足) OUTPUT はデフォルト動作なので省略可能
}

void run(void) 
{
    while(1){
        RC0 = 1;
        __delay_ms(500);
        RC0 = 0;
        __delay_ms(500);
    }

    return;
}


/*
// 例2. ディジタル入力(プルアップ)
void setup(void)
{
    // pinMode(ピン名称(または番号),モード)
    //
    // モード
    // OUTPUT  : ディジタル出力 (デフォルト)
    // INPUT   : ディジタル入力 (内部弱プルアップ 無効)
    // INPUT_PULLUP   : ディジタル入力 (内部弱プルアップ 有効)
    // ADC     : アナログ入力 (10 bit)
    // PWM1〜4 : パルス幅変調 (3系統同時出力可)
    // TX      : シリアル通信 送信 (115200ボー)
    // RX      : シリアル通信 受信 (115200ボー)
    
    pinMode(PIN16_RC0,OUTPUT);
    // (補足) ピン番号を使って pinMode(16,OUTPUT); とすることも可能
    // (補足) OUTPUT はデフォルト動作なので省略可能
    
    pinMode(PIN17_RA2,INPUT_PULLUP);
    // (補足) ピン番号を使って pinMode(17,INPUT_PULLUP); とすることも可能
}

void run(void) 
{
    while(1){
        if(RA2 == 0) RC0 = 1;
        else RC0 = 0;
    }
    
    return;
}
*/


/*
// 例3. アナログ入力
// 分解能は10bit(0〜1023)
void setup(void)
{
    // pinMode(ピン名称(または番号),モード)
    //
    // モード
    // OUTPUT  : ディジタル出力 (デフォルト)
    // INPUT   : ディジタル入力 (内部弱プルアップ 無効)
    // INPUT_PULLUP   : ディジタル入力 (内部弱プルアップ 有効)
    // ADC     : アナログ入力 (10 bit)
    // PWM1〜4 : パルス幅変調 (3系統同時出力可)
    // TX      : シリアル通信 送信 (115200ボー)
    // RX      : シリアル通信 受信 (115200ボー)
    
    pinMode(PIN16_RC0,OUTPUT);
    // (補足) ピン番号を使って pinMode(16,OUTPUT); とすることも可能
    // (補足) OUTPUT はデフォルト動作なので省略可能
    
    pinMode(PIN15_RC1,ADC);
    // (補足) ピン番号を使って pinMode(15,ADC); とすることも可能
}

void run(void) 
{
    while(1){
        // 値は AN+ピン名称 で取得できる (例) RA1 の場合は ANA1
        if(ANC1 > 512) RC0 = 1;
        else RC0 = 0;    
    }
    
    return;
}
*/


/*
// 例4. PWM
// PWM1〜PWM4 を使用できる(その内3系統同時出力可能)
void setup(void)
{
    // pinMode(ピン名称(または番号),モード)
    //
    // モード
    // OUTPUT  : ディジタル出力 (デフォルト)
    // INPUT   : ディジタル入力 (内部弱プルアップ 無効)
    // INPUT_PULLUP   : ディジタル入力 (内部弱プルアップ 有効)
    // ADC     : アナログ入力 (10 bit)
    // PWM1〜4 : パルス幅変調 (3系統同時出力可)
    // TX      : シリアル通信 送信 (115200ボー)
    // RX      : シリアル通信 受信 (115200ボー)
    
    pinMode(PIN10_RB7,PWM1);
    // (補足) ピン番号を使って pinMode(10,PWM1); とすることも可能
}

void run(void) 
{
    while(1){
        // 関数 pwm1〜4(周期,幅) で周期と幅をセットする
        // 周期と幅はマイクロ秒で指定(1000マイクロ秒 = 1ミリ秒、最大 16383 マイクロ秒)
        pwm1(16000,500);
        __delay_ms(3000);
        pwm1(16000,2500);
        __delay_ms(3000);   
    }
    
    return;
}
*/


/*
// 例5. シリアル通信
// 通信速度は115200ボー
void setup(void)
{
    // pinMode(ピン名称(または番号),モード)
    //
    // モード
    // OUTPUT  : ディジタル出力 (デフォルト)
    // INPUT   : ディジタル入力 (内部弱プルアップ 無効)
    // INPUT_PULLUP   : ディジタル入力 (内部弱プルアップ 有効)
    // ADC     : アナログ入力 (10 bit)
    // PWM1〜4 : パルス幅変調 (3系統同時出力可)
    // TX      : シリアル通信 送信 (115200ボー)
    // RX      : シリアル通信 受信 (115200ボー)
    
    pinMode(PIN02_RA5,TX);
    // (補足) ピン番号を使って pinMode(2,TX); とすることも可能

    pinMode(PIN03_RA4,RX);
    // (補足) ピン番号を使って pinMode(3,RX); とすることも可能
}

void run(void) 
{
    while(1){
        int c = getch();
        if( c == 'a'){
            RC0 = 1;
            printf("ON\r\n");
        }
        if( c == 'b'){
            RC0 = 0;
            printf("OFF\r\n");
        }
    }
    
    return;
}
*/