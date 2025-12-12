#include "common.h"

volatile char i2c_status = 1;

// I2C 初期設定
void init_i2c(void)
{    
    unsigned char porta = 0;
    unsigned char portb = 0;
    unsigned char portc = 0;
    
    unsigned char num = get_pinMode(SDA,&porta,&portb,&portc);
    if( num != 1 ) i2c_status = 255;
    else{
        num = get_pinMode(SCL,&porta,&portb,&portc);
        if( num != 1 ) i2c_status = 255;
    }

    // コンパイル時のwarning表示防止
    if(i2c_status == 255 ){
        i2c_start();
        i2c_stop();
        i2c_putch(0);
        i2c_getch(0);
        return;
    }

    printf("-----\r\nI2C:\r\n");
    get_pinMode(SDA,&porta,&portb,&portc);
    printf("SDA: portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",porta,portb,portc);
    set_outputpps(SDA,porta,portb,portc);
    set_inputpps(SDA,porta,portb,portc);

    get_pinMode(SCL,&porta,&portb,&portc);
    printf("SCL: portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",porta,portb,portc);
    set_outputpps(SCL,porta,portb,portc);
    set_inputpps(SCL,porta,portb,portc);

    // MSSP2 使用
    SSP2STAT = 0x00;
    SSP2CON1 = 0x00;
    SSP2CON2 = 0x00;
    SSP2CON3 = 0x00;
    SSP2MSK = 0x00;

    SSP2CON1bits.SSPM = 0b1000; // I2Cマスターモード
    SSP2STATbits.SMP = 1; // // 標準速度モード (100 KHz or 1 Mhz)
    SSP2ADD = 9; // クロック = 100 KHz ( FOSC/(4*100000)-1 = 4000000/400000-1 = 9 )
    SSP2CON1bits.SSPEN = 1; // MSSP2 ON
}

// start condition 送信
void i2c_start(void) 
{
    if(i2c_status == 255 ) return;
    
    PIR2bits.SSP2IF = 0; // 割り込みフラグは自動ではリセットされないので手動でリセット
    SSP2CON2bits.SEN = 1; // Start Condition 送信開始 (SEN = Start Condition Enabled bit)
    while(SSP2CON2bits.SEN == 1) continue; // 処理が終わると自動で SEN = 0、SSPxIF = 1 になる
}

// stop condition 送信
void i2c_stop(void)
{
    if(i2c_status == 255 ) return;
    
    PIR2bits.SSP2IF = 0; // 割り込みフラグは自動ではリセットされないので手動でリセット
    SSP2CON2bits.PEN = 1; // Stop Condition 送信開始 (PEN = Stop Condition Enable bit)
    while (SSP2CON2bits.PEN == 1) continue; // 処理が終わると自動で PEN = 0、SSPxIF = 1 になる
}

// ACK/NACK 送信
// nack = 1 : NACK 送信
// nack = 0 : ACK  送信
void i2c_acknowledge( unsigned char nack )
{
    PIR2bits.SSP2IF = 0; // 割り込みフラグは自動ではリセットされないので手動でリセット
    SSP2CON2bits.ACKDT = nack; // 1をセットするとNACKを送信 (ACKTD = Acknowledge Data bit )
    SSP2CON2bits.ACKEN = 1; // 送信開始 (ACKEN = Acknowledge Sequence Enable bit )
    while (SSP2CON2bits.ACKEN == 1) continue; // 処理が終わると自動で ACKEN = 0、SSPxIF = 1 になる
}

// 1 byte 送信
void i2c_putch( const char data )
{ 
    if(i2c_status == 255 ) return;
    
    PIR2bits.SSP2IF = 0; // 割り込みフラグは自動ではリセットされないので手動でリセット
    SSP2BUF = data; // バッファにデータをセットすると送信開始
    while (PIR2bits.SSP2IF == 0) continue; // 処理が終わると自動で SSPxIF = 1 になる
}

// 1 byte 受信
// nack = 1 : NACK 返信
// nack = 0 : ACK  返信
const char i2c_getch( const unsigned char nack )
{
    char data = 0;

    if(i2c_status == 255 ) return 0;
    
    PIR2bits.SSP2IF = 0; // 割り込みフラグは自動ではリセットされないので手動でリセット
    SSP2CON2bits.RCEN = 1; // 受信開始 (RCEN = Receive Enable bit )
    while (PIR2bits.SSP2IF == 0) continue; // 処理が終わると自動で RCEN = 0、SSPxIF = 1 になる
    data = SSP2BUF;

    i2c_acknowledge( nack );

    return data;
}
