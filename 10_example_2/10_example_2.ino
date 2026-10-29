#include <Servo.h>
#define PIN_SERVO 10

Servo myservo;

void setup() {
  myservo.attach(PIN_SERVO); 
  myservo.write(90);
  delay(1000);
}

void loop() {
  // add code here.

  int angles[] = {0, 90, 180, 90};

  for (int a : angles) {
    myservo.write(a);
    delay(500);
  }
}
