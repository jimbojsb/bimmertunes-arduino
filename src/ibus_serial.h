#include <Arduino.h>
#include "ibus_packet.h"

#define BUS_GAP_THRESHOLD 10

class IbusSerial {
  private:
    unsigned long previousReadMillis = 0;
    unsigned long busQuietMillis = 0;
    int readBufferIndex = 0;
    byte readBuffer[36];
    IbusPacket* writeBuffer[4];
    void resetReadBuffer();
  public:
    void update();
    void write(IbusPacket &pkt);
};
