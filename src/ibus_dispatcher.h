#include "ibus_packet.h"

class IbusDispatcher {
  private:
    unsigned long previousMillis;
  public:
    void update();
    void dispatch(IbusPacket &pkt);
};
