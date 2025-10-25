/*
* File:   lm35_uart.c
* Target: PIC16F877A @ 20 MHz
* Func  : Read LM35 on AN0 and send "Temp: XX.X C" via UART @ 9600 bps
*/
 
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
 
// CONFIG
#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = OFF
#pragma config LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF
 
 
static void UART_TxChar(unsigned char c)
{
    while(!PIR1bits.TXIF); // Wait until TXREG is empty
    TXREG = c;
}
 
static void UART_TxString(const char *s)
{
    while(*s) UART_TxChar(*s++);
}
 
static unsigned int ADC_Read_AN0(void)
{
    __delay_us(10);             // small acquisition delay (hold cap charge)
    ADCON0bits.GO_nDONE = 1;    // Start conversion
    while(ADCON0bits.GO_nDONE); // Wait finish
    return ((unsigned int)ADRESH << 8) | ADRESL; // 10-bit result (0..1023)
}
 
void main(void)
{
    char line[32];
 
    SPBRG = 129;
    TXSTAbits.BRGH = 1;   
    TXSTAbits.SYNC = 0;   
    RCSTAbits.SPEN = 1;   
    TXSTAbits.TXEN = 1;   
 
    TRISC6 = 0;           
    TRISC7 = 1;           
    ADCON1 = 0x8E;
 
    
    ADCON0 = 0x81;
 
    TRISA0 = 1;           
 
    UART_TxString("LM35 UART ready\r\n");
 
    while(1)
    {
        unsigned int adc = ADC_Read_AN0();
 
        float tempC = adc * 0.48828125f;
 
        sprintf(line, "Temp: %.1f C\r\n", tempC);
        UART_TxString(line);
 
        __delay_ms(1000); 
    }
}