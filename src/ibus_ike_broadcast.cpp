#include "ibus_ike_broadcast.h"
#include "ibus_packet.h"
#include "ibus_serial.h"
#include "debug_interface.h"

extern unsigned long currentMillis;
extern IbusSerial ibusSerial;
extern DebugInterface debug;

void IbusIkeBroadcast::update() {
    if (currentMillis - this->previousMillis > IKE_BROADCAST_INTERVAL) {
        debug.write("Broadcasting IKE wakeup packet");
        byte msg[2] = {0x11, 0x02};
        IbusPacket pkt(0x80, 0xBF, msg, 2);
        ibusSerial.write(pkt);
        this->previousMillis = currentMillis;
    }
}