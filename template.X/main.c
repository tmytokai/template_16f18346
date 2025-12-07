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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
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


/*
// 例6. INT割り込み

int count = 0;

// INTのISR
void isr_int(void)
{
    // チャタリング対策
    __delay_ms(50);
    if (RA2 == 1) return;
        
    count++;
}

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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
    pinMode(PIN02_RA5,TX);

    // INT割り込みピン ※ 内部弱プルアップ有効
    pinMode(PIN17_RA2,INT);
    
    // INT割り込み設定
    // 引数1: ISRのアドレス
    // 引数2: 割り込みを行うタイミング
    //        0 をセットすると立ち下がり(High→Low)
    //        1 をセットすると立ち上がり(Low→High)
    config_int(isr_int,0);
}

void run(void) 
{
    while(1){
        printf("%d\r\n",count);
        __delay_ms(1000);
    }
    
    return;
}
*/


/*
// 例7. タイマー割り込み

int count1 = 0;
int count3 = 0;

// タイマー1のISR
void isr_timer1(void)
{
    count1++;
}

// タイマー3のISR
void isr_timer3(void)
{
    count3++;
}

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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
    pinMode(PIN02_RA5,TX);

    // タイマー割り込み設定
    // 16bitタイマー1、3、5で割り込み可 
    // (注意) ADCを使用する場合はタイマー5は使用不可
    
    // 割り込み間隔設定 (マイクロ秒、最大 524280)
    timer1(100000);
    timer3(500000);
    
    // 引数: ISRのアドレス設定
    config_timer1(isr_timer1);
    config_timer3(isr_timer3);
}

void run(void) 
{
    while(1){
        printf("-----\r\n");
        printf("count1= %d\r\n",count1);
        printf("count3= %d\r\n",count3);
        __delay_ms(1000);
    }
    
    return;
}
*/


/*
// 例8. SPIマスターモード
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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)
    
    pinMode(PIN02_RA5,TX);
    pinMode(PIN03_RA4,RX);
    
    // SPIピン設定
    pinMode(PIN06_RC4,SDO);
    pinMode(PIN07_RC3,SDI);
    pinMode(PIN08_RC6,SCK);

    // SPI設定
    // 引数1: SPIモード(0〜3)
    // 引数2: サンプリングタイミング(0か1)、とりあえず0で試して、うまく通信できない時は1にする
    config_spi(0,0);
}

void run(void) 
{
    // RC7をCSとする
    RC7 = 1;
    __delay_ms(100); // 子機の初期化待ち(時間は適当)
    RC7 = 0;
    __delay_ms(100); // 子機の初期化待ち(時間は適当)

    while(1){
        
       int c = getch();
       if( c != EOF && c != '\n'){
           
           // 1文字送信
           spi_putch((char)c);
           
           // 1文字受信
           printf("%c\r\n",spi_getch());
       }
    }
    return;
}
*/


/*
// 例9. I2Cマスターモード
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
    // TX      : シリアル通信 送信 (115200 ボー)
    // RX      : シリアル通信 受信 (115200 ボー)
    // INT     : INT割り込み
    // SDO     : SPI SDO
    // SDI     : SPI SDI
    // SCK     : SPI SCK (1MHz)
    // SDA     : I2C SDA
    // SCL     : I2C SCL (100 Hz)

    pinMode(PIN02_RA5,TX);
    pinMode(PIN03_RA4,RX);

    // I2Cピン設定
    pinMode(PIN06_RC4,SDA);
    pinMode(PIN07_RC3,SCL);
}

void run(void) 
{
    int lng = 0;
    char data[64];
    
    __delay_ms(100); // 子機の初期化待ち(時間は適当)

    while(1){
        
       int c = getch();
       if( c != EOF && c != '\n'){
           
           printf("%c",c);
           data[lng++] = (char)c;

           if( c == '\r' ){
                data[lng]='\0';
                printf( "\r\nsend: %s\r\n", data );

                // 送信
                i2c_start();
                i2c_putch( ( 0x01 << 1) + 0 ); // 子機のアドレス(7bit) + write指示(0)
                for(int i=0; i<lng; ++i ) i2c_putch(data[i]);
                i2c_stop();                
                
                __delay_ms(50);

                lng = 5; // 5文字受信
                
                // 受信
                i2c_start();
                i2c_putch( ( 0x01 << 1) + 1 ); // 子機のアドレス(7bit) + read指示(1)
                for(int i=0; i<lng-1; ++i ) data[i] = i2c_getch(0); // ACK を送信して受信続行
                data[lng-1] = i2c_getch(1); // 最後にNACK を送信して受信終了
                i2c_stop();
                
                data[lng]='\0';
                printf( "recv: %s\r\n", data );
                lng = 0;
           }           
       }
    }
}
 */
