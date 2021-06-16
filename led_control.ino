int basic_led = 2;
int normal_led = 3;
int acidic_led = 4;

void setup() {
  // put your setup code here, to run once:
pinMode(basic_led, OUTPUT);
pinMode(normal_led, OUTPUT);
pinMode(acidic_led, OUTPUT);

digitalWrite(basic_led, LOW);
digitalWrite(normal_led, LOW);
digitalWrite(acidic_led, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(basic_led, HIGH);
digitalWrite(normal_led, LOW);
digitalWrite(acidic_led, LOW);
Serial.println("BASIC // RED");
delay(5000);

digitalWrite(normal_led, HIGH);
digitalWrite(basic_led, LOW);
digitalWrite(acidic_led, LOW);
Serial.println("NORMAL // GREEN");
delay(5000);

digitalWrite(acidic_led, HIGH);
digitalWrite(normal_led, LOW);
digitalWrite(basic_led, LOW);
Serial.println("ACIDIC // YELLOW");
delay(5000);
}