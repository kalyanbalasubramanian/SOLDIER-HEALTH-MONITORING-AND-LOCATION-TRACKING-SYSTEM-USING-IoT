#include <SoftwareSerial.h>
SoftwareSerial mySerial(14, 12);
#include "Ubidots.h"
const char* UBIDOTS_TOKEN = "BBFF-bIXGfdaQsfEwvMuRYAScI5s7U33AQ6";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "project1";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "project1";      // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

int firstVal, secondVal, thirdVal, fourthVal,fifthVal;
int j=0;
int b=0;
void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  delay(500);
}

void loop() {
  if (mySerial.available() > 0) 
  {
    String a = mySerial.readString();
    Serial.println(a);
    delay(50);
    
    for (int i = 0; i < a.length(); i++) 
      {
        if (a.substring(i, i+1) == ",")
        {
          j++;
          if (j==1)
          {
            firstVal = a.substring(0, i).toInt();
            Serial.print("first : ");
            Serial.println(firstVal);
            ubidots.add("Distance", firstVal); 
            b=i;
          }
          else if (j==2)
          {
            secondVal = a.substring(b+1, i).toInt();
            Serial.print("Second : ");
            Serial.println(secondVal);
            ubidots.add("Metal Detector", secondVal); 
            b=i;
          }
          else if (j==3)
          {
            thirdVal = a.substring(b+1, i).toInt();
            Serial.print("Third : ");
            Serial.println(thirdVal);
            ubidots.add("Temperature", thirdVal);
            b=i;
          }
          else if (j==4)
          {
            fourthVal = a.substring(b+1, i).toInt();
            Serial.print("Fourth : ");
            Serial.println(fourthVal);
            ubidots.add("Heart beat", fourthVal);
            b=i;
          }  
          else if (j==5)
          {
            fifthVal = a.substring(b+1, i).toInt();
            Serial.print("Fifth : ");
            Serial.println(fifthVal);
            ubidots.add("Motion Detected", fifthVal);
            b=0;
            j=0;
          }  
        }
      
      }
              bool bufferSent = false;
          bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id
      
        if (bufferSent) {
          Serial.println("Values sent by the device");
        }
  }
}
