#include <16f877a.h>

#fuses NOWDT
#fuses NOBROWNOUT
#fuses NOLVP

#use delay(crystal=4000000)

#define LCD_RS_PIN PIN_B7
#define LCD_RW_PIN PIN_B6
#define LCD_ENABLE_PIN PIN_B5
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B3
#define LCD_DATA6 PIN_B2
#define LCD_DATA7 PIN_B1

#include "lcd.c"

#define sut1 pin_d0
#define sut2 pin_d1
#define sut3 pin_d2
#define sut4 pin_d3

#define sat1 pin_d4
#define sat2 pin_d5
#define sat3 pin_d6
#define sat4 pin_d7

#define ROLE pin_c0

int tus=0;
int basildi;
int sifre[4] = {1, 9, 0, 3}; // �ifreyi burada tan�ml�yoruz

int keypad_oku()
{
  output_d(0x00);
  tus = 0;
  
  output_high(sat1); // SATIR 1
  
  if (input(sut1))
  { while(input(sut1));
  tus=1; 
  basildi=1; }
  
  if (input(sut2))
  { while(input(sut2)); 
  tus=2;
  basildi=1; }
  
  if (input(sut3))
  { while(input(sut3)); 
  tus=3; 
  basildi=1; }
  
  if (input(sut4))
  {  while(input(sut4));  
  tus=0xA; 
  basildi=1; }
   output_low(sat1);
   
   
   
   output_high(sat2); // SATIR 2
   
   if (input(sut1))
  {  while(input(sut1));  
  tus=4; 
  basildi=1; }
  
  if (input(sut2))
  {  while(input(sut2));  
  tus=5; 
  basildi=1; }
  
  if (input(sut3))
  {  while(input(sut3)); 
  tus=6; 
  basildi=1; }
  
  if (input(sut4))
  {  while(input(sut4)); 
  tus=0xB; 
  basildi=1; }
   output_low(sat2);
   
   
   
   output_high(sat3); // SATIR 3
   
   if (input(sut1))
  {  while(input(sut1)); 
  tus=7; 
  basildi=1; }
  
  if (input(sut2))
  {  while(input(sut2));  
  tus=8; 
  basildi=1; }
  
  if (input(sut3))
  {  while(input(sut3));  
  tus=9; 
  basildi=1; }
  
  if (input(sut4))
  {  while(input(sut4)); 
  tus=0x0C; 
  basildi=1; }
   output_low(sat3);
   
   
   
   output_high(sat4); // SATIR 4
   
   if (input(sut1))
  {  while(input(sut1));  
  tus=0xE; 
  basildi=1; }
  
  if (input(sut2))
  {  while(input(sut2));  
  tus=0; 
  basildi=1; }
  
  if (input(sut3))
  {  while(input(sut3)); 
  tus=0xF; 
  basildi=1; }
  
  if (input(sut4))
  {  while(input(sut4)); 
  tus=0xD; 
  basildi=1; }
   output_low(sat4);
   
   return tus;
}


void main()
{
  setup_psp(PSP_DISABLED);
  setup_timer_1(T1_DISABLED);
  setup_timer_2(T2_DISABLED,0,1);
  setup_adc_ports(NO_ANALOGS);
  setup_adc(ADC_OFF);
  
  set_tris_d(0x0F);
  
  lcd_init();
  
  printf(lcd_putc,"\fTaha Kara");
  printf(lcd_putc,"\n202023707018");
  delay_ms(1500);
  printf(lcd_putc,"\fKilitli");
  printf(lcd_putc,"\nBAUN EEM");
  delay_ms(1500);
  printf(lcd_putc,"\fParola Giriniz");
   
   int sec=0;
   int yanlis=0;
   int gelen;
   int deneme_sayisi = 0; 
   
   
   while(true)
   {
  gelen = keypad_oku();
   if(basildi==1) 
   {
     basildi=0;
     
     lcd_gotoxy(7+sec,2);
     printf(lcd_putc,"*");
     
     if (sifre[sec] != gelen)
     {
       yanlis=1;
       sec = 0; 
       deneme_sayisi++; 
       
       if (deneme_sayisi >= 3) // E�er �� kez yanl�� giri� yap�l�rsa
       {
         printf(lcd_putc,"\fKilitlendi!");
         output_low(ROLE);  
         delay_ms(300000);
         deneme_sayisi = 0; 
         printf(lcd_putc,"\fParola Giriniz");
       }
     }
     else 
     {
       sec++;
       if (sec == 4) // �ifre do�ru girildi�inde
       {
         printf(lcd_putc,"\fWELCOME");
         output_high(ROLE);
         delay_ms(2000);
         output_low(ROLE);
         printf(lcd_putc,"\fParola Giriniz");
         sec = 0; 
         deneme_sayisi = 0; 
       }
     }
   
     if (yanlis == 1)
     {
       printf(lcd_putc,"\fParola Hatali");
       lcd_gotoxy(15,2);
       delay_ms(2000);
       yanlis=0;
       printf(lcd_putc,"\fParola Giriniz");
     }  
   }
 }
}
