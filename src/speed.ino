#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#define USE_SERIAL Serial
WiFiMulti wifiMulti;

// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
int SpeedVariable = 0;
int mySwitch = 0;
int myNetLed = 15;
int myBootLed = 4;

int driveValue = 0;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;


void setup() {
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(myNetLed, OUTPUT);
  pinMode(myBootLed, OUTPUT);
  digitalWrite(myBootLed,HIGH);
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);

  USE_SERIAL.begin(115200);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
  
  for(uint8_t t = 4; t > 0; t--) {
      USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
      USE_SERIAL.flush();
      delay(1000);
  }

    wifiMulti.addAP("moaiwlan", "Ossi1Paavo234");

}

void driveTrain(int mySpeed){
  USE_SERIAL.println(mySpeed);
  if (mySpeed < 0){
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    driveValue = map(abs(mySpeed),10, 100, 210, 240); 
    ledcWrite(pwmChannel, abs(driveValue));
  }
  else if (mySpeed > 0) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    driveValue = map(abs(mySpeed),10, 100, 210, 240); 
    ledcWrite(pwmChannel, abs(driveValue));
  }
  else {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
  }
  return;
}

void loop() {
    // wait for WiFi connection

    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        http.begin("http://www.sabulo.com/speed/speedcontrol.txt"); //HTTP
        int httpCode = http.GET();
        digitalWrite(myNetLed,HIGH);
        digitalWrite(myBootLed,LOW);
        if(httpCode > 0) {
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                mySwitch = payload.toInt();
                
                driveTrain(mySwitch);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            digitalWrite(myNetLed,LOW);
        }

        http.end();

    }

    delay(500);
}
