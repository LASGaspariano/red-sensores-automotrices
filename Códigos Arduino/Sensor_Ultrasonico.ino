#include <NewPing.h>

#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  int uS = sonar.ping_median();
  Serial.print("Distancia: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
  
}

