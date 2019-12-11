#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <Servo.h>

const char* Wifi_ID = "Hallym WiFi";
const char* Wifi_Pw =  "1111133333";

const char* UiamServer = "soldier.cloudmqtt.com";
const int UiamPort =  10591;
const char* UiamID = "Hyeon";


int zeroThrottle = 90; //90 Needs to be between 66 and 101.
int maxThrottle = 110; //120 seems to be where the maximum is. Above this doesn't give any extra speed.
int minThrottle = 70;  //60 This represents the "reverse" speed.


WiFiClient Uiam;
PubSubClient client(Uiam);
Servo servo_L;
Servo servo_R;

void setup() {
  delay(1000);


pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);

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
   client.publish("Hyeon/online", "w");

Serial.println("Set up Left");

servo_L.attach(D3); // attaches the servo on pin 9 to the servo object

Serial.println("Zero Throttle");
servo_L.write(zeroThrottle);  // Set the output to the middle or "zero" position. CONNECT THE ESC DURING THIS DELAY!!

delay(3000);       // This delay allows the ESC to be connected and powered on. The motor will beep once on
                    // power up and once when it recognises the zero position.


Serial.println("Max");
servo_L.write(maxThrottle); // Make sure your test bed is safe for the motor to turn at this point. It will run at maximum speed!

delay(2000);

Serial.println("Zero");
servo_L.write(zeroThrottle); // Simulates the receiver sending a zero throttle signal again

delay(2000);

Serial.println("Min");
servo_L.write(minThrottle); // "engages" reverse.

delay(2000);

Serial.println("Zero");
servo_L.write(zeroThrottle); // back to neutral

delay(2000);

Serial.println("Set up Left END");

delay(2000);





Serial.println("Set up Right");
 servo_R.attach(D2); // attaches the servo on pin 9 to the servo object

Serial.println("Zero Throttle");
servo_R.write(zeroThrottle);  // Set the output to the middle or "zero" position. CONNECT THE ESC DURING THIS DELAY!!

delay(3000);       // This delay allows the ESC to be connected and powered on. The motor will beep once on
                    // power up and once when it recognises the zero position.


Serial.println("Max");
servo_R.write(maxThrottle); // Make sure your test bed is safe for the motor to turn at this point. It will run at maximum speed!

delay(2000);

Serial.println("Zero");
servo_R.write(zeroThrottle); // Simulates the receiver sending a zero throttle signal again

delay(2000);

Serial.println("Min");
servo_R.write(minThrottle); // "engages" reverse.

delay(2000);

Serial.println("Zero");
servo_R.write(zeroThrottle); // back to neutral

delay(2000);

Serial.println("Set up Right END");
delay(1000);
Serial.println("Setup Complete");






   }

 void reconnect(){
  while (!client.connected()) {
    Serial.println("Connecting to Uiam Twitter...");
    client.publish("Hyeon/online", "c");
    if (client.connect("Hyeon", UiamID, UiamID )) {
        client.publish("Hyeon/online", "m");
        Serial.println("connected");
        client.subscribe("Hyeon/#");
      } else {
      Serial.print("connection failure with state ");
       client.publish("Hyeon/online", "f");
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
  Speed = map(abs(v), -100,100,minThrottle,maxThrottle);

 if (strcmp(topic , "Hyeon/R")==0 && v > 0){
servo_R.write(Speed);

}


else if (strcmp(topic , "Hyeon/R")==0 && v == 0){
servo_R.write(Speed);

 }

 else if (strcmp(topic , "Hyeon/R")==0 && v < 0){
servo_R.write(Speed);

 }


else if (strcmp(topic , "Hyeon/L")==0 && v > 0){
servo_L.write(Speed);

  }

else if (strcmp(topic , "Hyeon/L")==0 && v == 0){
servo_L.write(Speed);
}

else if (strcmp(topic , "Hyeon/L")==0 && v < 0){
servo_L.write(Speed);
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

  //5800이면 1m 입니다. 최대 기다리는 시간은 1,000,000 입니다.
  // 5800을 58로 나누게 되면 cm 단위가 됩니다.
  long distance = pulseIn(ECHO, HIGH, 5800) / 58; //5800uS 동안 기다렸으므로 1미터 측정이 된다.
  Serial.print("r");
  Serial.print(rad);
  Serial.print("d");
  Serial.println(distance);

   if (distance < 10) {
  tone(speakerpin, 500,10);  //500: 음의 높낮이(주파수), 10: 음의 지속시간(0.01초)
//  noTone(speakerpin); // 이걸 적용하면 소리가 확 줄어듭니다.
//  delay(1000); //물체를 발견하고 멈추는 시간
  }
 }

void draw(){

background(0); // black background
stroke(0, 255, 36); //bright green color
arc(cx, cy, width, height, PI, TWO_PI, CHORD); //draw semi-circle
arc(cx, cy, width/2, height/2, PI, TWO_PI, CHORD); //draw semi-circle 2
float r = TWO_PI-map(rad, 0, 360, 0, TWO_PI);

line(cx, cy, cx + cos(r)* width/2, cy + sin(r)* height/2); //draw moving line
line(cx, cy, cx + cos(radians(30))* width/2, cy + sin(radians(-30))* height/2);
line(cx, cy, cx + cos(radians(60))* width/2, cy + sin(radians(-60))* height/2);
line(cx, cy, cx + cos(radians(90))* width/2, cy + sin(radians(-90))* height/2);
line(cx, cy, cx + cos(radians(120))* width/2, cy + sin(radians(-120))* height/2);
line(cx, cy, cx + cos(radians(150))* width/2, cy + sin(radians(-150))* height/2);
text("0cm", cx, cy, 100,100);
text("100cm", cx, cy-220, 100,100);


updateBalls();

displayBalls();

//text("Distance: "+Integer.toString(distance), cx-30, cy+10, 100, 100);  //거리 표시

text("Ultrasonic Radar", 0, 0, 100, 100);

}


void updateBalls(){
for(int i = balls.size()-1 ; i > -1 ; i--){
balls.get(i).update();
if(balls.get(i).isDead())
balls.remove(i);
}
}

void displayBalls(){
for(int i = 0 ; i < balls.size() - 1 ; i++){
balls.get(i).display();
}
}

void serialEvent(Serial p){
String inString = p.readStringUntil('\n');
if(inString != null){
if(inString.startsWith("r")){
String[] strings = inString.trim().replace("r","").split("d");
if(strings.length > 1){
rad = Integer.parseInt(strings[0]);
int distance = Integer.parseInt(strings[1]);

if(distance != 0){
balls.add(new Ball(cx, cy, rad, distance));



}
}
}
}
}

class Ball{
int life = 50;
float x, y;
public Ball(float cx, float cy, int rad, int distance){
float d = map(distance, 0, 100, 0, width/2);
float r = TWO_PI-map(rad, 0, 360, 0, TWO_PI);
x = cx + cos(r)*d;
y = cy + sin(r)*d;

}

public void display(){
ellipse(x, y, life, life);
}

public void update(){
--life;
if(life < 0 )
life = 0;
}

public boolean isDead(){
return life == 0;
}
}


void loop() {
  if (!client.connected()){
    reconnect();
    }
  client.loop();

}
