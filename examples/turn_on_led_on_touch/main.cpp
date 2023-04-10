// This example demonstrates how to use the TouchHandler library to turn on an LED
// when one of the specified GPIOs are touched.

#include <Arduino.h>
#include <TouchHandler.h>

#define LED_PIN 2

// Define touch pins
const int touchPins[] = {4, 12, 13, 14, 15, 27, 32, 33};
const int numTouchPins = sizeof(touchPins) / sizeof(touchPins[0]);

TouchHandler touchHandler(touchPins, numTouchPins);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  touchHandler.begin();
}

void loop() {
  touchHandler.update();

  for (int i = 0; i < numTouchPins; i++) {
    if (touchHandler.isTouched(i)) {
      digitalWrite(LED_PIN, HIGH);
      Serial.print("Touch pin ");
      Serial.print(touchPins[i]);
      Serial.println(" is touched!");
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }

  delay(10);
}
