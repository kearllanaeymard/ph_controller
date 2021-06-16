#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

#define SensorPin 0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
int buf[10],temp;
float phValue;

int IN1 = 12;
int IN2 = 13;

int basic_led = 2;
int normal_led = 3;
int acidic_led = 4;


void ph_up(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(150);
    digitalWrite(IN1, LOW);
  }

void ph_down(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(150);
    digitalWrite(IN2, LOW);
  }

void get_ph(){
      for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
      { 
        buf[i]=analogRead(SensorPin);
        delay(10);
      }
      for(int i=0;i<9;i++)        //sort the analog from small to large
      {
        for(int j=i+1;j<10;j++)
        {
          if(buf[i]>buf[j])
          {
            temp=buf[i];
            buf[i]=buf[j];
            buf[j]=temp;
          }
        }
      }
      avgValue=0;
      for(int i=2;i<8;i++)                      //take the average value of 6 center sample
        avgValue+=buf[i];
      phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
      phValue=3.5*phValue;                      //convert the millivolt into pH value
  }

void main_prog(){
    get_ph();
    if((phValue >= 6.5) && (phValue <= 7.00)){
       Serial.print("pH Value: ");
       Serial.println(phValue);
       Serial.println("NORMAL");
       Serial.println(" ");

       lcd.setCursor(1,0);
       lcd.print("pH Value:");
       lcd.setCursor(11,0);
       lcd.print(phValue);
       lcd.setCursor(5,2);
       lcd.print("NORMAL");
       
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
       digitalWrite(normal_led, HIGH);
       digitalWrite(basic_led, LOW);
       digitalWrite(acidic_led, LOW);
       Serial.println("NORMAL // GREEN");
       delay(2000);
      }
      
    else if(phValue < 6.5){
       Serial.print("pH Value: ");
       Serial.println(phValue);
       Serial.println("ACIDIC");
       Serial.println(" ");

       lcd.setCursor(1,0);
       lcd.print("pH Value:");
       lcd.setCursor(11,0);
       lcd.print(phValue);
       lcd.setCursor(5,2);
       lcd.print("ACIDIC");

       digitalWrite(acidic_led, HIGH);
       digitalWrite(normal_led, LOW);
       digitalWrite(basic_led, LOW);
       Serial.println("ACIDIC // YELLOW");
       ph_up();
       delay(10000);
      }
      
    else if(phValue > 7.00){
       Serial.print("pH Value: ");
       Serial.println(phValue);
       Serial.println("BASIC");
       Serial.println(" ");

       lcd.setCursor(1,0);
       lcd.print("pH Value:");
       lcd.setCursor(11,0);
       lcd.print(phValue);
       lcd.setCursor(5,2);
       lcd.print("BASIC ");

       digitalWrite(basic_led, HIGH);
       digitalWrite(normal_led, LOW);
       digitalWrite(acidic_led, LOW);
       Serial.println("BASIC // RED");
       ph_down();
       delay(10000);
      }
  }

void setup()
{ 
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN2, LOW);
  digitalWrite(IN2, LOW);
  
  pinMode(basic_led, OUTPUT);
  pinMode(normal_led, OUTPUT);
  pinMode(acidic_led, OUTPUT);
  
  digitalWrite(basic_led, LOW);
  digitalWrite(normal_led, LOW);
  digitalWrite(acidic_led, LOW);
 
  Serial.println("- - - - - READY - - - - - ");
  Serial.println(" ");
  lcd.setCursor(0,0);
  lcd.print("Electronic pH");
  lcd.setCursor(0,1);
  lcd.print("Controller");
  lcd.setCursor(0,3);
  lcd.print("SBEE-4A");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("- - -READY- - -");
  delay(2000);
  lcd.clear();
}
void loop()
{
  main_prog();
}