#include <main.h>
#define LCD_RS_PIN PIN_B7
#define LCD_RW_PIN PIN_B6
#define LCD_ENABLE_PIN PIN_B5
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B3
#define LCD_DATA6 PIN_B2
#define LCD_DATA7 PIN_B1
#include "lcd.c"

#define buton pin_a0
#define sut1 pin_d0
#define sut2 pin_d1
#define sut3 pin_d2
#define sut4 pin_d3

#define sat1 pin_d4
#define sat2 pin_d5
#define sat3 pin_d6
#define sat4 pin_d7

#define ROLE pin_c1

int tus[4]={11,11,11,11};
int yanlis=0,sayac=0,flag=0,flag2=0,flag3=0,roleflag=0,taha=0;
int sifre[4] = {1, 9, 0, 3}; // Şifreyi burada tanımlıyoruz

void oku(int *tuss)
{
   int breaker=0;
   while(breaker<=3)
   {
      if(roleflag==1)
      {
         roleflag=0; output_low(ROLE);
      }
      if(input(buton)==1 && taha==0){ output_high(pin_c4);taha=1;}
      else {taha=0;output_low(pin_c4);}
      
      output_high(sat1);
      if(input(sut1)==1){while((input(sut1))); tuss[breaker]=1;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut2)==1){while((input(sut2))); tuss[breaker]=2;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut3)==1){while((input(sut3))); tuss[breaker]=3;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      output_low(sat1);
      output_high(sat2);
      if(input(sut1)==1){while((input(sut1))); tuss[breaker]=4;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut2)==1){while((input(sut2))); tuss[breaker]=5;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut3)==1){while((input(sut3))); tuss[breaker]=6;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      output_low(sat2);
      output_high(sat3);
      if(input(sut1)==1){while((input(sut1))); tuss[breaker]=7;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut2)==1){while((input(sut2))); tuss[breaker]=8;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut3)==1){while((input(sut3))); tuss[breaker]=9;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      output_low(sat3);
      output_high(sat4);
      if(input(sut1)==1){while((input(sut1))); tuss[breaker]=12;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut2)==1){while((input(sut2))); tuss[breaker]=0;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      if(input(sut3)==1){while((input(sut3))); tuss[breaker]=13;lcd_gotoxy(7+breaker,2);printf(lcd_putc,"*");breaker++;}
      output_low(sat4);
   }
   breaker=0;
}
int compare(void)
{
   for(int i=0;i<4;i++)
   {
      if(tus[i]!=sifre[i]) 
      
      return 0;
   }
   return 1;
}
#INT_TIMER1
void  TIMER1_isr(void) 
{
   sayac++;
   if(sayac==10 && flag3==0)
   {
      flag=0;
      sayac=0;
      flag2=1;
      disable_interrupts(INT_TIMER1);
   }
   
   if(flag3==1 && sayac==5)
   {
     sayac=0;
     flag3=0;
     roleflag=1;
     flag=0;
     disable_interrupts(INT_TIMER1);
   }
}

void main()
{
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);      
   output_d(0x00);
   enable_interrupts(GLOBAL);
   
   set_tris_d(0x00);
   set_tris_c(0x00);
   set_tris_a(0x00);
   lcd_init();
 
   output_high(pin_c3);
   
   output_low(ROLE);
   
   while(TRUE)
   {
      if(flag!=1 && flag3!=1)
      {
         
         printf(lcd_putc,"\fParola Giriniz");
         oku(tus);
         if(compare()!=1)
         {yanlis++;
         
         }
         else 
         {
            yanlis=0;
            output_high(ROLE);
            printf(lcd_putc,"\fWELCOME");
            flag3=1;
            enable_interrupts(INT_TIMER1);
         }
      }
      if(yanlis==3)
      {
         printf(lcd_putc,"\fKilitlendi!");
         yanlis=0;
         enable_interrupts(INT_TIMER1);
         flag=1;
      }
   }
}
      
