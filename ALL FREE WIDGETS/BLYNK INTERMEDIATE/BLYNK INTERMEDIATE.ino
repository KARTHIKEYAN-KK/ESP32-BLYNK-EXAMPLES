/*
  ------------------------------------
  |  Edited and reworked by:          |
  |      Karthikeyan Thirumalaisamy,  |
  |      ReDevLabz.                   |
  |                                   |
  |  For contact:                     |
  |      tkarthi.palani@gmail.com     |
  ------------------------------------      
*/

#define BLYNK_TEMPLATE_ID  "YOUR_TEMPLATE_ID" 
#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> 

#define DHTPIN 22 
#define RELAY 23
#define BUTTON 18
#define LDR 34
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
float t, h;
int ld,dr;
char auth[] = "YOUR_AUTH_TOKEN";

char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

BLYNK_WRITE(V2) {
    int pinvalue = param.asInt();
    if(pinvalue == 1){
       digitalWrite(RELAY, LOW);
       Blynk.virtualWrite(V4, "    RELAY ON    ");
      }
    else{
      digitalWrite(RELAY, HIGH);
      Blynk.virtualWrite(V4, "   RELAY  OFF   ");
    }
  }

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LDR, INPUT);

  digitalWrite(RELAY, HIGH);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  button();
  ldr();

  h = dht.readHumidity();
  Blynk.virtualWrite(V0, h);
  t = dht.readTemperature();
  Blynk.virtualWrite(V1, t);
  ld = analogRead(LDR);
  dr = map(ld, 0, 4095, 100, 0);
}

void button(){
  if(digitalRead(BUTTON)==LOW){
    Blynk.virtualWrite(V3, "     PRESSED    ");
  }
  else{
    Blynk.virtualWrite(V3, "  NOT  PRESSED  ");
  }
}

void ldr(){
  Blynk.virtualWrite(V6, dr);
  if(dr > 80){
    Blynk.virtualWrite(V5, "   TOO BRIGHT   ");
  }
  else if(dr < 20){
    Blynk.virtualWrite(V5, "LOW BRIGHTNESS");
  }
  else{
    Blynk.virtualWrite(V5, "BRIGHTNESS OK");
  }
}

