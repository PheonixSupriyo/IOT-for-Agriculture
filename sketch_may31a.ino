#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#define led2 D6
WiFiClient wificlient;

//const char* host = "mini-project-c9d9c-default-rtdb.firebaseio.com";
//const int httpPort = 80;
//const char* url= "/controls/light_intensity.json";


void setup() {
  // put your setup code here, to run once:
  Serial.println("hello");
  WiFi.begin("Nokia 5","nirmalya");
  while(WiFi.status() != WL_CONNECTED)
  {
      Serial.print("..");
      delay(200);  Serial.begin(9600);

  }
  Serial.println();
  Serial.println("nodeMcu is connected"); 
  Serial.println(WiFi.localIP());  

}

void loop() {
  // put your main code here, to run repeatedly:
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;
  https.begin(*client,"https://mini-project-c9d9c-default-rtdb.firebaseio.com/controls/light_intensity.json");
  int httpCode = https.GET();
  if (httpCode == 200){
  String brightness = https.getString();
  Serial.println(brightness);   
  int val = brightness.toInt();
  Serial.println(val+1000); 
  int duty = val-1000;
  analogWrite(led2,duty);         
  }
}
