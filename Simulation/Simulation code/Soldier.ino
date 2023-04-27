#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup ()
{
Serial.begin(9600);
lcd.begin(16, 2);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(6,OUTPUT);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("SOLDIER HEALTH");
  lcd.setCursor(0, 1);
  lcd.print("MONITORING SYSTEM");
  delay(2000);
}

void loop ()
{
int a=analogRead(A0);
int b=analogRead(A1);
float c=a/4;
float d=b/100;
int e=digitalRead(7);
int f=digitalRead(8);
if(e==1)
{
  digitalWrite(6,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Human Detected");
  Serial.print("human location changed\r\n");
  Serial.print("Lat:56N Lon:86E\r\n");
  delay(500);
}
if(e==0)
{
  digitalWrite(6,LOW);
}
if(f==1)
{
  digitalWrite(6,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temp is high");

  Serial.print("High temp Rate Detected\r\n");

  Serial.print("Lat:56N Lon:86E\r\n");
  delay(500);
}
if(c==0)
{
  digitalWrite(6,LOW);
}
if(a>400)
{
  digitalWrite(6,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("metal detected");
    lcd.setCursor(0, 1);
     // lcd.print(c);
         //   lcd.print("V");
  Serial.print("\r\n");
    Serial.print("metal detected\r\n");
      //Serial.print(c);
         // Serial.print("V\r\n");
  Serial.print("Lat:56N Lon:86E\r\n");
  delay(500);
}
if(b>400)
{
    digitalWrite(6,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("obstacle detected");
    lcd.setCursor(0, 1);
      //lcd.print(d);
       //     lcd.print("A");
  Serial.print("\r\n");
    Serial.print("obstacle detected\r\n");
      //Serial.print(d);
      //    Serial.print("A\r\n");
  Serial.print("Lat:56N Lon:86E\r\n");
  delay(500);
//}
//if(b<401)
//{
 // digitalWrite(6,LOW);
//}
}
}
