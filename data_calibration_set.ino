//06/01/2021 Data Calibration Set
//    Ph meter    Ph Sensor
//1st solution  6.43    6.37
//2nd solution  9.03    9.40
//3rd solution  4.02    1.37
//4th solution  6.65    5.83



#define SensorPin 0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

void setup()
{
//  pinMode(13,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("Ready");    //Test the serial monitor
}
void loop()
{
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
//  avgValue=0;
//  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
//    avgValue+=buf[i];
//  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
//  phValue=3.5*phValue;                      //convert the millivolt into pH value
//  Serial.print("    pH:");  
//  Serial.print(phValue,2);
//  Serial.println(" ");

float phValue;
Serial.print("PH Values: ");
  for(int w = 0; w <= 9; w++){
    phValue=(float)buf[w]*5.0/1024;
    phValue=3.5*phValue; 
      Serial.print(phValue);
      Serial.print(", ");
    }
    Serial.println(" ");
    delay(1);

  
//  digitalWrite(13, HIGH);       
//  delay(800);
//  digitalWrite(13, LOW); 
}