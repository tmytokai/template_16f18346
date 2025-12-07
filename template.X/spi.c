#include "common.h"

volatile char spi_mode = 255; // SPIモード
volatile char spi_smp = 0;  // サンプリングタイミング: 0:中央、1:最後

// SPI 初期設定
void init_spi(void)
{
    unsigned char porta = 0;
    unsigned char portb = 0;
    unsigned char portc = 0;
    
    // コンパイル時のwarning表示防止
    if( spi_mode == 255 ){
        config_spi(255,0);
        spi_putch(0);
        spi_getch();
    }

    unsigned char num = get_pinMode(SDO,&porta,&portb,&portc);
    if( num != 1 ) return;
    num = get_pinMode(SDI,&porta,&portb,&portc);
    if( num != 1 ) return;
    num = get_pinMode(SCK,&porta,&portb,&portc);
    if( num != 1 ) return;

    printf("-----\r\nSPI:\r\n");
    get_pinMode(SDO,&porta,&portb,&portc);
    printf("SDO: portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",porta,portb,portc);
    set_outputpps(SDO,porta,portb,portc);

    get_pinMode(SDI,&porta,&portb,&portc);
    printf("SDI: portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",porta,portb,portc);
    set_inputpps(SDI,porta,portb,portc);

    get_pinMode(SCK,&porta,&portb,&portc);
    printf("SCK: portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",porta,portb,portc);
    set_outputpps(SCK,porta,portb,portc);

    // MSSP1 使用
    SSP1STAT = 0x00;
    SSP1CON1 = 0x00;
    SSP1CON2 = 0x00; // SPIはCON2不使用
    SSP1CON3 = 0x00;

    // SPIモード0 :
    // アイドル時ロー極性   : CPOL = 0 または CKP = 0
    // 立上がり時サンプリング: CPHA = 0 または CKE = 1
    //
    // SPIモード1 :
    // アイドル時ロー極性   : CPOL = 0 または CKP = 0
    // 立下がり時サンプリング: CPHA = 1 または CKE = 0
    //
    // SPIモード2 :
    // アイドル時ハイ極性   : CPOL = 1 または CKP = 1
    // 立下がり時サンプリング: CPHA = 0 または CKE = 1
    //
    // SPIモード3 :
    // アイドル時ハイ極性   : CPOL = 1 または CKP = 1
    // 立上がり時サンプリング: CPHA = 1 または CKE = 0
    //
    char CKP = 0, CKE = 1; // mode0
    if(spi_mode==1){ CKP = 0; CKE = 0; }
    if(spi_mode==2){ CKP = 1; CKE = 1; }
    if(spi_mode==3){ CKP = 1; CKE = 0; }
    SSP1CON1bits.SSPM = 0b0000; // SPIマスターモード、clock = FOSC/4 = 1 Mhz
    SSP1CON1bits.CKP = CKP;
    SSP1STATbits.CKE = CKE;
    SSP1STATbits.SMP = spi_smp;
    SSP1CON1bits.SSPEN = 1; // MSSP1 ON
}

void config_spi(const char mode,const char smp)
{
    if(mode == 255) return;
    spi_mode = mode;
    spi_smp = smp;
}

// 1 byte 送信
void spi_putch( const char data )
{
    if(spi_mode == 255) return;
    SSP1BUF = data;
}

// 1 byte 受信
const char spi_getch(void)
{
    if(spi_mode == 255) return 0;
    while(!SSP1STATbits.BF) continue; // 受信待ち (BF = Buffer Full Status bit)
    PIR1bits.SSP1IF = 0; // 割り込みフラグは自動ではリセットされないので手動でリセット
    return SSP1BUF; // SSP1BUF からデータを読み込むと SSP1STATbits.BF がリセットされる
}
