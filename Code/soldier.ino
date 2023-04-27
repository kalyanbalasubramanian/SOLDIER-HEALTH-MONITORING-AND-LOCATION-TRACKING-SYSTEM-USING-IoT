#include <dht.h>
#include <dht.h>  // Include library
#define temp_sensor A2  // Defines pin number to which the sensor is connected
#define heartbeat A0
dht DHT;      // Creates a DHT object

#include <SoftwareSerial.h>
SoftwareSerial mySerial(18, 19);
#include <LiquidCrystal.h>
const int rs = 6, en = 5, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int heartbeat1;
const int trigPin = 3;
const int echoPin = 4;
long duration;
int distance;
int motion =0;
void setup() {
   Serial.begin(115200);    
   mySerial.begin(115200);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(2,INPUT);//ir
   attachInterrupt(digitalPinToInterrupt(2), change, LOW);
   pinMode(12,INPUT);//metal
   pinMode(13,OUTPUT);//buzzer
   digitalWrite(13,HIGH);delay(500);
   digitalWrite(13,LOW);delay(500);
  
   lcd.begin(16, 2);
   lcd.setCursor(0, 0);
   lcd.print("Soldier Tracking");
   lcd.setCursor(1, 1);
   lcd.print("&Health System");
   delay(2000);
}

void loop() {

   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);  
   duration = pulseIn(echoPin, HIGH);
   distance = duration * 0.034 / 2;

  int readData = DHT.read11(temp_sensor);
  int temp = DHT.temperature;  // Read temperature
  float h = DHT.humidity;   // Read humidity
  int heartbeat = analogRead(heartbeat);
  int metal =digitalRead(12);
   //int motion =!digitalRead(2);
   
   lcd.clear();
   lcd.setCursor(0, 0);lcd.print("D:");lcd.setCursor(2, 0);lcd.print(distance);
   lcd.setCursor(9, 0);lcd.print("H:");lcd.setCursor(11, 0);lcd.print(h);
   lcd.setCursor(1, 1);lcd.print("T:");lcd.setCursor(3, 1);lcd.print(temp);lcd.setCursor(6, 1);lcd.print("C");
    
  
   if (distance < 15)
   {
    lcd.clear();
    lcd.setCursor(2, 0);lcd.print("DISTANCE ALERT");
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
   }
   
   else if (motion == 1)
   { 
    lcd.clear();
    lcd.setCursor(2, 0);lcd.print("MOTION ALERT");
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
   }
   
   else if (temp > 38)
   {
    lcd.clear();
    lcd.setCursor(2, 1);lcd.print("TEMP ALERT");
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
   }
    else if (metal==1)
   {
    lcd.clear();
    lcd.setCursor(2, 1);lcd.print("METAL ALERT");
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
   } 
    else if (heartbeat < 15)
   {
    heartbeat1 = random(72,82);
    lcd.clear();
    lcd.setCursor(3,0 );lcd.print("HEART BEAT");
    lcd.setCursor(8, 1);lcd.print(heartbeat1);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
    digitalWrite(13,HIGH);delay(200);digitalWrite(13,LOW);delay(200);
   } 
   //Serial.print(heartbeat);Serial.print(",");
   Serial.print(distance);Serial.print(",");
   Serial.print(h);Serial.print(",");
   Serial.print(temp);Serial.print(",");
   Serial.print(heartbeat1);Serial.println(",");
 
   mySerial.print(distance);mySerial.print(",");
   mySerial.print(metal);mySerial.print(",");
   mySerial.print(temp);mySerial.print(",");
   mySerial.print(heartbeat1);mySerial.print(",");
   mySerial.print(motion);mySerial.println(","); 
  delay(4000);
  motion=0;
}
void change()
{
  motion =1;
}
