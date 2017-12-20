#include "ibus_packet.h"
#include "ibus_devices.h"

#define IBUS_CDPLAYER_PONG_INTERVAL 30000


class IbusCdPlayer {
  private:
    unsigned long previousMillis;
    bool hasBeenPinged;
    void pong();
  public:
    IbusCdPlayer();
    void update(unsigned long millis);
    void handle(IbusPacket *pkt);
};