#include <arduino.h>
#include "debug_interface.h"

DebugInterface::DebugInterface(bool enable) {
    this->enabled = enable;
}

void DebugInterface::write(const char *msg) {
    if (this->enabled) {
        Serial.write(msg);
    }
}

void DebugInterface::write(byte msg[]) {
    if (this->enabled) {
        Serial.write(msg, sizeof(msg));
    }
}

void DebugInterface::update() {
    if (this->enabled) {
        if (Serial.available()) {
            String input = Serial.readStringUntil('\n');
        }
    }
}