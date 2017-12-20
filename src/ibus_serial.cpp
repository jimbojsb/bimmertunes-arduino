#include "ibus_serial.h"
#include "ibus_packet.h"
#include "serial_aliases.h"
#include "ibus_dispatcher.h"
#include "debug_interface.h"
#include "activityled.h"

extern IbusDispatcher ibusDispatcher;
extern DebugInterface debug;
extern ActivityLed activityLed;
extern HardwareSerial ibSerial;
extern usb_serial_class dbSerial;
extern unsigned long currentMillis;

void IbusSerial::update() {
  if (this->busQuietMillis >= BUS_GAP_THRESHOLD) {
    if (this->readBufferIndex > 0) {
      debug.write("BUS QUIET READ BUFFER: ", this->readBuffer, this->readBufferIndex);
      if (IbusPacket::isPacket(this->readBuffer, this->readBufferIndex)) {
        IbusPacket pkt(this->readBuffer, this->readBufferIndex);
        debug.write("RX PACKET: ", pkt);
        ibusDispatcher.dispatch(pkt);
      }
    }
    this->readBufferIndex = 0;
  }
  int numBytesToRead = ibSerial.available();
  if (numBytesToRead) {
    for (int i = 0; i < numBytesToRead; i++) {
      this->readBuffer[this->readBufferIndex] = ibSerial.read();
      this->readBufferIndex++;
    }
    this->previousReadMillis = currentMillis;
    this->busQuietMillis = 0;
  } else {
    this->busQuietMillis = currentMillis - this->previousReadMillis;
  }
}

void IbusSerial::write(IbusPacket &pkt) {
  activityLed.blink();
  debug.write("TXP:", pkt);
  ibSerial.write(pkt.asBytes(), pkt.byteLen());
}

void IbusSerial::resetReadBuffer() {

}
