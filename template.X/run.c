#include "common.h"
#include "uart.h"
#include "adc.h"
#include "pwm.h"

void run(void) 
{
    while(1){
                 
        /*
        // 例1. LED点滅
        // この例ではRA5にLEDと抵抗を接続する
        RA5 = 1;
        __delay_ms(500);
        RA5 = 0;
        __delay_ms(500);
        */

        /*
        // 例2. ディジタル入力
        // pinconfig.c で任意のピン(この例ではRA4)に INPUT を指定してスイッチ等に接続する
        // pinconfig.c で INPUT_PULLUP に 1 を指定すると内部弱プルアップがONになる(デフォルトON)
        if(RA4 == 0) RA5 = 1;
        else RA5 = 0;
        */

        /*
        // 例3. アナログ入力
        // pinconfig.c で任意のピン(この例ではRC5)に ADC を指定して可変抵抗等に接続する
        // 分解能は10bit(0〜1023)
        if(ANC5 > 512) RA5 = 1;
        else RA5 = 0;
        */

        /*       
        // 例4. PWM
        // pinconfig.c で任意のピンに PWM1 を指定してオシロスコープ等に接続する
        // 関数 pwm1(周期,幅) で周期と幅をセットする
        // 周期と幅はマイクロ秒で指定(最大 16383 マイクロ秒)
        // PWM2、PWM3、PWM4 も同様にして使用できる(3系統同時出力可)
        pwm1(1000,500);
        __delay_ms(1000);
        pwm1(2000,1000);
        __delay_ms(1000);
        */

        /* 
        // 例5. シリアル通信
        // pinconfig.c で任意のピンに RX と TX を指定してPC等に接続する
        // 通信速度は115200ボー
        int c = getch();
        if( c == 'a'){
            RA5 = 1;
            printf("ON\r\n");
        }
        if( c == 'b'){
            RA5 = 0;
            printf("OFF\r\n");
        }
        */
    }

    return;
}
