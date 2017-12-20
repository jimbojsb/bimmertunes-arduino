#include <arduino.h>
#include "activityled.h"

extern unsigned long currentMillis;

void ActivityLed::update() {
  if (this->state != LOW) {
    if ((currentMillis - this->previousMillis) > ACTIVITY_LED_DURATION) {
      digitalWrite(LED_BUILTIN, LOW);
      this->state = LOW;
    }  
  }
}

void ActivityLed::blink() {
  if (this->state == LOW) {
    this->previousMillis = currentMillis;
    digitalWrite(LED_BUILTIN, HIGH);  
    this->state = HIGH;
  }
}