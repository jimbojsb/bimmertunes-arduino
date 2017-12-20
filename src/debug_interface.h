#include <Arduino.h>
#include "ibus_packet.h"

class DebugInterface {
  private:
    bool enabled;
  public:
    DebugInterface(bool enable);
    void update();
    void write(const char *prefix, IbusPacket &pkt);
    void write(byte *msg, int len);
    void write(const char *prefix, byte *msg, int len);
    void write(const char *msg);
};
