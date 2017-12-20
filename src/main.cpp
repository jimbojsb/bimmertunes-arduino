#include <Arduino.h>
#include <SparkFunbc127.h>
#include "config.h"
#include "activityled.h"
#include "debug_interface.h"
#include "ibus_packet.h"
#include "ibus_serial.h"
#include "serial_aliases.h"
#include "pin_aliases.h"
#include "ibus_dispatcher.h"
#include "ibus_ike_broadcast.h"

BC127 bt(&Serial2);
ActivityLed activityLed;
DebugInterface debug(ENABLE_DEBUG);
IbusSerial ibusSerial;
IbusDispatcher ibusDispatcher;
IbusIkeBroadcast ikeBroadcast;
unsigned long currentMillis = 0;


void setup() {
    dbSerial.begin(9600);
    ibSerial.begin(9600, SERIAL_8E1);
    btSerial.begin(9600);

    // wake up 2025 for tx
    pinMode(CSWAKE, OUTPUT);
    digitalWrite(CSWAKE, HIGH);

    // set up onboard led
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    activityLed.blink();

    delay(2000);
    debug.write("BimmerTunes initialized");
}

void loop() {
    currentMillis = millis();
    if (ENABLE_IKE_BROADCAST) {
        ikeBroadcast.update();
    }
    ibusSerial.update();
    ibusDispatcher.update();
    activityLed.update();
}
