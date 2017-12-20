#include "ibus_cdplayer.h"
#include "ibus_serial.h"

extern IbusSerial ibusSerial;

IbusCdPlayer::IbusCdPlayer() {
    this->hasBeenPinged = false;
    this->previousMillis = 0;
}

void IbusCdPlayer::update(unsigned long millis) {
    if (this->hasBeenPinged) {
        if (millis - this->previousMillis > IBUS_CDPLAYER_PONG_INTERVAL) {
            this->pong();
        }
    }
}

void IbusCdPlayer::handle(IbusPacket *pkt) {
    switch(pkt->source) {
        case IBUS_DEVICE_RADIO:
            byte pingMessage[1] = {0x01};
            if (pkt->contentEquals(pingMessage, 1)) {
                this->hasBeenPinged = true;
                this->pong();
            }
        break;
    }
}

void IbusCdPlayer::pong() {
    byte msg[2] = {0x02, 0x00};
    IbusPacket pkt(IBUS_DEVICE_CDPLAYER, IBUS_DEVICE_BROADCAST, msg, 2);
    ibusSerial.write(pkt);
}
