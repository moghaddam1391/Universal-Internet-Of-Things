#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <CapacitiveSensor.h>
CapacitiveSensor   cs1 = CapacitiveSensor(15,4);   
CapacitiveSensor   cs2 = CapacitiveSensor(15,5);  
char auth[] = "Enter your Auth Token Here";

char ssid[] = "Enter your SSID here";
char pass[] = "Enter your password here";

Servo servo;
Servo servo2;
int previous=0;
int previous2=0;
bool state = false;
bool state2 = false;
bool servo_state = false;
bool servo2_state = false;
BLYNK_WRITE(V3) {
  if(param.asInt() == 1){
    servoup();
  }
  else if(param.asInt() == 0){
    servodown();
  }

}
BLYNK_WRITE(V4) {
  if(param.asInt() == 1){
    servo2up();
  }
  else if(param.asInt() == 0){
    servo2down();
  }

}

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting...");
  Blynk.begin(auth, ssid, pass);
  
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.println("Connected");
}

void loop()
{
    long start = millis();
    long total1 =  cs1.capacitiveSensor(30);  
    long total2 =  cs2.capacitiveSensor(30);
    Serial.println(total2);
    if(total1 > 500 & state == true){
      state = !state;
      servo2up();   
    }
    else if(total1 > 500 & state == false){
      state = !state;
      servodown();     
    }
    if(total2 > 500 & state2 == true){
      state2 = !state2;
      servoup();     
    }
    else if(total2 > 500 & state2 == false){
      state2 = !state2;
      servodown();    
    } 
  Blynk.run(); // You can inject your own code or combine it with other sketches.
  delay(100);
}
void servo2up(){
  servo2.attach(16);
  servo2.write(150);
  delay(1000);
  servo2.detach();
}
void servo2down(){
  servo2.attach(16);
  servo2.write(30);
  delay(1000);
  servo2.detach();
}
void servoup(){
  servo.attach(14);
  servo.write(150);
  delay(1000);
  servo.detach();
}
void servodown(){
  servo.attach(14);
  servo.write(30);
  delay(1000);
  servo.detach();
}


