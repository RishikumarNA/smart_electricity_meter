//#define BLYNK_TEMPLATE_ID "TMPLQ8d3eyGC"
//#define BLYNK_DEVICE_NAME "project iot"
//#define BLYNK_AUTH_TOKEN "e59QuXL0OXWEJLUDxogKZbLRLdwN_G5z"

#define BLYNK_TEMPLATE_ID "TMPLXKD_pLHh"
#define BLYNK_TEMPLATE_NAME "NEW"
#define BLYNK_AUTH_TOKEN "IB0UwiLHuInsiiKZgMXtxa8EDZTlJYRn"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Rohan";
char pass[] = "rohan1782";
//char watt;

unsigned long last_time =0; 
unsigned long current_time =0; 
float Wh =0 ;
// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
/*BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2, LOW);
  }
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  Blynk.virtualWrite(V5, current);  
}*/
void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  /*int adc= analogRead(A0);
  float voltage = adc*5/1023.0;
  float current=(voltage-2.5)/0.105;
  if(current<0.16){
    current=0;
  }
  Serial.print("current:");
  Serial.print(current);
  delay(300);*/
  float wh;
  //char watt;
  float V = 230;
  float I = analogRead(A0);
  float i= (2.5 - (I * (5.0 / 1024.0)) )/0.066; 
  //float Cu = i/35;
  Serial.println("CURRENT:"); 
  Serial.println(I); 
  Blynk.virtualWrite(V0,I);
  float po = V * I;
  last_time = current_time; 
  current_time = millis();
  Wh = Wh+ po *(( current_time -last_time) /3600000.0) ; 
  //dtostrf(Wh, 4, 2, watt);
  Serial.println(Wh); 
  Blynk.virtualWrite(V1,Wh); 
  delay(1000);
  Blynk.run();
}
