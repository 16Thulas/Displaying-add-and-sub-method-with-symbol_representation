
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
// #pragma config statements should precede project file includes.
// Use project enum instead of #define for ON and OFF.
#include<xc.h>
#define _XTAL_FREQ 6000000 //6mhz 
unsigned char value;
unsigned char x;
unsigned char j,k[5],Equal,Minus,Plus;
unsigned int num1,num2,sub,delaycount,m,n;
void lcd_init();
void lcdOutput(unsigned int i);
void delay(unsigned int delaycount);
void lcd_command(unsigned char i);
void lcd_data(unsigned char i);
void main(){
    lcd_init();
    num1=100;
    num2=200;
    Equal='=';
    Minus='-';
    Plus='+';
    
    lcd_command(0x80);
    lcdOutput(num1);
    lcd_data(Minus);
    lcdOutput(num2);
     lcd_data(Equal);
    lcd_command(0x88);
    if(num1>num2){
        lcd_data(Plus);
        sub=num1-num2;
    }
    else{
        lcd_data(Minus);
        sub=num2-num1;
    }
    lcd_data(Minus);
    while(1);
    
}
void lcd_init(){
	// lcd init
	//TRISC = 0x00; //all pins are op
    TRISC = 0x00; //RB0(EN) and RB3 as ouptut
	TRISD = 0x00;  
	PORTD = 0x00;
	PORTB = 0xF6; //RB3 and RB0 as low
	lcd_command(0x30);
	__delay_ms(100);
	lcd_command(0x30);
	__delay_ms(100);
	lcd_command(0x30);
	__delay_ms(100);
	lcd_command(0x38);
	__delay_ms(100);
	lcd_command(0x06);
	__delay_ms(100);
	lcd_command(0x0C);
	__delay_ms(100);
	lcd_command(0x01);
	__delay_ms(100);
}
void lcdOutput(unsigned int i){
    unsigned char s,j=1;
    m=i;
    while(m!=0){
        s=m-((m/10)*10);
        k[j]=s;
        j++;
        m=m/10;
    }
    k[j]='\0';
    j=j-i;
    while(j!=0){
        n=0x30+k[j];
    }
}
void lcd_command(unsigned char i){
	PORTB &= 0xF7; //RS=>RB3 //
	PORTD=i;
	PORTB |= 0x01;  //RB0 =1
	PORTB &= 0xFE;  //RC0=0
	__delay_ms(100);
}
void lcd_data(unsigned char i){
	PORTB |= 0x08; //RS->RC3->1
	PORTD=i;
	PORTB |= 0x01;  //RC0 =1
	PORTB &= 0xFE; //~0x01;  //RC0=0
	__delay_ms(100);
}
void delay(unsigned int delaycount){
    while(--delaycount);
}
