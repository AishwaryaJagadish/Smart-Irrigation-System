#define BLYNK_TEMPLATE_ID "TMPL3ncyi8s7X"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_AUTH_TOKEN "uXXdkQLEC8FcZhjWYjVFzNVpbW2P8h72"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define sensor A0
#define relay D4


BlynkTimer timer;

//Enter your WIFI SSID and password
char ssid[] = "Jagadish";
char pass[] = "Dharma_2018";

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

//Get the ultrasonic sensor values
void soilMoisture() {
  int value = analogRead(sensor);
  Serial.println(value);
  value = map(value, 0, 1023, 0, 100);
  value = (value - 100) * -1;
  if(value < 25){
    digitalWrite(relay, LOW);
  } else {
    digitalWrite(relay, HIGH);
  }
  Blynk.virtualWrite(V0, value);
  Serial.println(value);
}

//Get the button value
BLYNK_WRITE(V1) {
  bool waterSwitch = param.asInt();
  if (waterSwitch == 1) {
    digitalWrite(relay, LOW);
  } else {
    digitalWrite(relay, HIGH);
  }
}

void loop() {
  soilMoisture();
  Blynk.run();//Run the Blynk library

  delay(200);

}
