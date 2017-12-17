#include <Arduino.h>
#include <SparkFunbc127.h>
#include "config.h"
#include "activityled.h"
#include "debug_interface.h"
#include "ibus_packet.h"

BC127 bt(&Serial2);
ActivityLed activityLed(LED_PIN);
DebugInterface debug(ENABLE_DEBUG);


void setup() {
    Serial.begin(9600);
    Serial1.begin(9600, SERIAL_8E1);
    Serial2.begin(9600);

    byte content[] = {0x01};

    IbusPacket p(0x68, 0x03, 0x18, content, 1);
    debug.write(&p);
}

void loop() {
    unsigned long currentMillis = millis();
    debug.update();
    activityLed.update(currentMillis);
}