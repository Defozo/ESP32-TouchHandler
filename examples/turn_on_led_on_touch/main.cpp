// This example demonstrates how to use the TouchHandler library to turn on an LED
// when one of the specified GPIOs are touched.

#include <Arduino.h>
#include <TouchHandler.h>

#define LED_PIN 2

// Define touch pins
const int touchPins[] = {4, 12, 13, 14, 15, 27, 32, 33};
const int numTouchPins = sizeof(touchPins) / sizeof(touchPins[0]);

// Configure touch parameters
TouchConfig config = {
  .samplePeriod = 10,       // in milliseconds
  .initPeriod = 5000,       // Initialization period in milliseconds
  .filterPeriod = 10000,    // Filtering period in milliseconds
  .sensitivity = 0.5f,      // Sensitivity factor for touch detection
  .factor = 12.0f,          // Scaling factor used in threshold calculation
  .offset = 40.0f,          // Offset added to baseline for threshold detection
  .numInitSamples = 50      // Number of samples collected during initialization
};

// Initialize TouchHandler with touch pins, number of pins, and configuration
TouchHandler touchHandler(touchPins, numTouchPins, config);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  touchHandler.begin();
}

void loop() {
  touchHandler.update();

  for (int i = 0; i < numTouchPins; ++i) {
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
