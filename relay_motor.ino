//JDVCC Jumper ON
//COM & NC Connections
//-Motor to -12v
//+Motor to COM
//+12v to NC


int IN1 = 12;
int IN2 = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(IN1, HIGH);
digitalWrite(IN2, HIGH);
delay(3000);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
delay(3000);
}