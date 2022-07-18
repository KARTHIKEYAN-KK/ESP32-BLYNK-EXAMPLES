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

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID" 
#include <WiFi.h>
#include <BlynkSimpleEsp32.h> 

#define LED 23

char auth[] = "YOUR_AUTH_TOKEN";

char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

BLYNK_WRITE(V2) {
    int pinvalue = param.asInt();
    if(pinvalue == 1){
      digitalWrite(LED, HIGH);
    }
    else{
      digitalWrite(LED, LOW);
    }
   }

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
