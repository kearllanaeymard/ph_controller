#include <LiquidCrystal.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
float calibration_value = 0;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
void setup() 
{
 Serial.begin(9600);
  lcd.init(); 
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Electronic pH");
  lcd.setCursor(0, 1);
  lcd.print("   Controller");
  lcd.setCursor(0, 2);
  lcd.print("SBEE-4A");
  delay(7000);
  lcd.clear();
}
void loop() {
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(10);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = 3.87 * volt + calibration_value;
 lcd.setCursor(2, 1);
 lcd.print("pH Val: ");
 lcd.setCursor(10, 1);
 lcd.print(ph_act);
 delay(1000);
}
