/*********************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *********************

  Rotate a servo using a slider!

  App project setup:
    Slider widget (0...180) on V3
 *********************/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define TRIGGER D2 
#define ECHO    D1
int flag=0;
unsigned long startM;
unsigned long currentM;
const unsigned long period=10000;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6787f99764ba41ccb088f765787af61d";

char ssid[] ="sid";
char pass[] ="123456781";
Servo servo;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  servo.attach(D4);
  servo.write(180);
  startM=millis();
}

void loop()
{ 
  currentM=millis();
  Blynk.run();

  if(flag==1)
  {
     if(currentM-startM>=period){
        udm();
        startM=currentM;
       }
  }
  //Serial.print(flag);
}
void udm() {
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delay(50);
  digitalWrite(TRIGGER, HIGH);
  delay(50); 
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
    if(distance>=10)
    { 
      //delay(10000);
      servo.write(180);
      flag=0;
    
    } 
  }
BLYNK_WRITE(V1)
{
  servo.write(180-param.asInt());
  if(param.asInt()>=65) {
    flag=1;
    delay(5000);
  }
  if(param.asInt()==0)
    flag=0;
}//SLIDER CONTROL SERVO 

BLYNK_WRITE(V2)
{
  servo.write(180);
  flag=0;
}//SWITCHOFF GAS STOVE
BLYNK_WRITE(V3)
{
  servo.write(65);
  flag=1;
  delay(5000);
}//SWITCHON GAS STOVE

BLYNK_WRITE(V4)
{
  // You'll get HIGH/1 at startTime and LOW/0 at stopTime.
  // this method will be triggered every day
  // until you remove widget or stop project or
  // clean stop/start fields of widget
  Serial.print("Got a value: ");
  Serial.println(param.asInt());
  if(param.asInt()==1){
    servo.write(65);
    flag=1; 
    delay(5000);
    }
  if(param.asInt()==0) {
    servo.write(180);
    flag=0;
  }
}//TIMER*/
