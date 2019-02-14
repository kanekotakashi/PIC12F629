#define _XTAL_FREQ 4000000
#include <xc.h>
#pragma config FOSC = INTRCIO, WDTE = OFF, PWRTE = ON, MCLRE = OFF, BOREN = OFF, CP = OFF, CPD = OFF

void disp_dice(int num)
{
    // 五つ目サイコロ　指定の数字を出す
    
    // 一旦 出力OFF 
    GPIO0 = 0;
    GPIO1 = 0;
    GPIO2 = 0;
    GPIO4 = 0;
    GPIO5 = 0;
        
    if (num == 1)
    {
        GPIO2 = 1;
    }
    else if (num == 2)
    {
        GPIO1 = 1;
        GPIO5 = 1;
    }
    else if (num == 3)
    {
        GPIO1 = 1;
        GPIO2 = 1;
        GPIO5 = 1;
    }
    else if (num == 4)
    {
        GPIO0 = 1;
        GPIO1 = 1;
        GPIO4 = 1;
        GPIO5 = 1;
    }
    else if (num == 5)
    {
        GPIO0 = 1;
        GPIO1 = 1;
        GPIO2 = 1;
        GPIO4 = 1;
        GPIO5 = 1;
    }
}

unsigned int running = 1; //　サイコロ振っている状態

void __interrupt () isr(void) 
{
    //割り込み発生
    __delay_ms(5);
    if(GPIO3 == 0)
    {
        // ボタンプッシュ
        // サイコロ　振っている状態<->ストップ状態
        if (running == 1) running = 0;
        else running = 1;
    }
    INTCONbits.GPIF = 0;
}

void main(void) 
{
    //開始
    IOC = 0b00001000;
    GPIO = 0x00;
    CMCON = 0b00000111;
    TRISIO = 0b00001000;
    INTCONbits.GPIF = 0;
    INTCONbits.GPIE = 1;
    INTCONbits.GIE = 1;
    
    running = 1; //サイコロ振っている状態
    int i = 1;

    while(1) 
    {
        __delay_ms(20);
        disp_dice(i);
        i++;
        if (i > 5)
        {
            i = 1;
        }
        
        if (running == 0)
        {
            while(1)
            {
                __delay_ms(20);
                if (running == 1)
                {
                    break;
                }
            }
        }
    }
    return;
}
