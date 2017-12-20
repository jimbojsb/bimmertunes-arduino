#include <arduino.h>
#include "debug_interface.h"

DebugInterface::DebugInterface(bool enable) {
    this->enabled = enable;
}

void DebugInterface::write(const char *prefix, IbusPacket &pkt) {
    if (this->enabled) {
        Serial.print(prefix);
        char buf[3];
        sprintf(buf, "%02X ", pkt.source);
        Serial.print(buf);
        sprintf(buf, "%02X ", pkt.length);
        Serial.print(buf);
        sprintf(buf, "%02X ", pkt.destination);
        Serial.print(buf);
        for (int i = 0; i < pkt.contentLen; i++) {
            sprintf(buf, "%02X ", pkt.content[i]);
            Serial.print(buf);
        }
        sprintf(buf, "%02X\n", pkt.checksum);
        Serial.print(buf);
    }
}

void DebugInterface::write(const char *msg) {
    if (this->enabled) {
        Serial.println(msg);
    }
}


void DebugInterface::write(const char *prefix, byte *msg, int len) {
    if (this->enabled) {
        char buf[3];
        Serial.print(prefix);
        for (int i = 0; i < len; i++) {
            sprintf(buf, "%02X ", msg[i]);
            Serial.print(buf);
        }
        Serial.write("\n");
    }
}

void DebugInterface::update() {
    if (this->enabled) {
        if (Serial.available()) {
            String input = Serial.readStringUntil('\n');
        }
    }
}
