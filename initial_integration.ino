#define SensorPin 0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
int buf[10],temp;
float phValue;

int IN1 = 12;
int IN2 = 13;


void ph_up(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(150); //droplets
    digitalWrite(IN1, LOW);
    delay(10000);
    
  }

void ph_down(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(150); //droplets
    digitalWrite(IN2, LOW);
    delay(10000);
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
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
      }
    else if(phValue < 6.5){
       Serial.print("pH Value: ");
       Serial.println(phValue);
       Serial.println("ACIDIC");
       Serial.println(" ");
       ph_up();
      }
    else if(phValue > 7.00){
       Serial.print("pH Value: ");
       Serial.println(phValue);
       Serial.println("BASIC");
       Serial.println(" ");
       ph_down();
      }
  }

void setup()
{ 
  Serial.begin(9600);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN2, LOW);
  digitalWrite(IN2, LOW);

  delay(2000);
  Serial.println("- - - - - READY - - - - - ");
  Serial.println(" ");
}
void loop()
{
  main_prog();
}