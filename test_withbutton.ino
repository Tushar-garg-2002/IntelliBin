#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30  
char ssid[] = "";
char pass[] = "";
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <AceButton.h>
using namespace ace_button; 
//tushar garg
#define trig 25
#define echo 26
#define lm35 35 
#define vref 3300.0
#define res 4096
#define VPIN_BUTTON_1 V0
int duration;
float distance;
float s;
float mv;
float temp; 
float depth = 13;
int percentage;
char auth[] = BLYNK_AUTH_TOKEN; 
ButtonConfig config1;
AceButton button1(&config1);
BlynkTimer timer;
void checkstatus(){
  bool isconnected = Blynk.connected();
  if(isconnected == true){
    Serial.println("connnected");
    
  }
}

BLYNK_CONNECTED(){
  Blynk.syncVirtual(VPIN_BUTTON_1);
}


void mytimer(){
  Blynk.virtualWrite(VPIN_BUTTON_1,distance);
}
void measureDistance(){
  mv = analogRead(lm35) * (vref/res);
  temp = mv/10;
  s = 331 + (0.6 * temp); 
  s = s/10000;
  digitalWrite(trig,LOW);
  delay(2);
  digitalWrite(trig,HIGH);
  delay(20);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  Serial.println(duration);
  distance = (duration*s)/2;
  distance = distance;
  if(distance >13){
    percentage = -1;
  }
  else{
    float med = distance/depth;
    percentage = med * 100;
  }
  
  Blynk.virtualWrite(VPIN_BUTTON_1,percentage);
  delay(100);
}
void setup() {
  Serial.begin(115200);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkstatus); // check if Blynk server is connected every 2 seconds
  Blynk.config(auth);
  delay(1000);
  timer.setInterval(10000L,measureDistance);
  // put your setup code here, to run once:

}

void loop() {
  Blynk.run();
  timer.run();
  // put your main code here, to run repeatedly:

}
