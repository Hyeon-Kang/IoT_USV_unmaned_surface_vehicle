#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <Servo.h>

const char* Wifi_ID = "SG";  
const char* Wifi_Pw =  "20155243";
const char* UiamServer = "soldier.cloudmqtt.com"; 
const int UiamPort =  10591; 
const char* UiamID = "Hyeon"; 

//Motor L (좌측모터)
int PWM_L = D6; //Speed control Motor L
int DIR_L = D3; //Direction Motor L
//Motor R (우측모터)
int PWM_R = D5; //Speed control Motor R
int DIR_R = D2; //Direction Motor R
//Motor C (수거모터)
int DIR_C0 = D8; //standby
int DIR_C1 = D7; //standby


WiFiClient Uiam;
PubSubClient client(Uiam);
Servo servo1;

void setup() {
  delay(1000);
  pinMode(PWM_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_C0, OUTPUT);
  pinMode(DIR_C1, OUTPUT);

//servo
  servo1.attach(15);  //D8

 //WIFI
  Serial.begin(115200);
  WiFi.begin(Wifi_ID, Wifi_Pw);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
  client.setServer(UiamServer, UiamPort);
  client.setCallback(UIamcallback);
   client.publish("hellouiam/online", "w");

   }

 void reconnect(){
  while (!client.connected()) {
    Serial.println("Connecting to Uiam Twitter...");
    client.publish("hellouiam/online", "c");
    if (client.connect("hellouiam", UiamID, UiamID )) {
        client.publish("hellouiam/online", "m");
        Serial.println("connected");  
        client.subscribe("hellouiam/#");
      } else {
      Serial.print("connection failure with state ");
       client.publish("hellouiam/online", "f");
      Serial.println(client.state()); 
      delay(2000);
     }
   }
 }


 void UIamcallback(char* topic, byte* payload, unsigned int length) {
   int v;
   int Speed;
   String msg;
    for (int i = 0; i < length; i++) {
    msg = msg + (char)payload[i]; 
  }
  v = msg.toInt();
  Speed = map(abs(v), 0,100, 250, 1023);

 if (strcmp(topic , "hellouiam/R")==0 && v > 0){
  digitalWrite(DIR_R, LOW); 
  analogWrite(PWM_R, Speed);
  }

else if (strcmp(topic , "hellouiam/R")==0 && v < 0){
  digitalWrite(DIR_R, HIGH);
  analogWrite(PWM_R, 1023-Speed);
  }

else if (strcmp(topic , "hellouiam/R")==0 && v == 0){
  digitalWrite(DIR_R, LOW);
  analogWrite(PWM_R, LOW);
 }
else if (strcmp(topic , "hellouiam/L")==0 && v > 0){
  digitalWrite(DIR_L, LOW);
  analogWrite(PWM_L, Speed);
  }
else if (strcmp(topic , "hellouiam/L")==0 && v < 0){
  digitalWrite(DIR_L, HIGH);
  analogWrite(PWM_L, 1023-Speed);
}
else if (strcmp(topic , "hellouiam/L")==0 && v == 0){
  digitalWrite(DIR_L, LOW);
  analogWrite(PWM_L, LOW);
}
else if (strcmp(topic , "hellouiam/S")==0 && v >= 0 ){
 servo1.write(v);
}


  Serial.println("--------------------");
  Serial.print("Message arrived in topic :");
  Serial.println(topic);
  Serial.print("Message arrived in msg : ");
  Serial.println(msg);
  Serial.println("");  
  Serial.println("///Motor");
  Serial.print("v : ");Serial.println(v);
  Serial.print("Speed : ");Serial.println(Speed);
  Serial.println("");Serial.println("");  
 }

void loop() {
  if (!client.connected()){
    reconnect();
    }
  client.loop();

}
