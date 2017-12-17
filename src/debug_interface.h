#include <Arduino.h>
#include "ibus_packet.h"

class DebugInterface {
  private:
    bool enabled;
  public:
    DebugInterface(bool enable);
    void update();
    void write(IbusPacket *pkt);
    void write(byte *msg, int len);
    void write(const char *msg);
};