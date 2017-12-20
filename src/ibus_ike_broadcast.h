#define IKE_BROADCAST_INTERVAL 3500

class IbusIkeBroadcast {
  private:
    unsigned long previousMillis = 0;
  public:
    void update();
};