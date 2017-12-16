#include <Arduino.h>

class IbusSerial {
  private:
    unsigned long previousMillis;
    unsigned long currentMillis;
    byte buffer[64];
    
  public:
    IbusSerial();
    void update(unsigned long currentMillis);
    void write(byte msg[]);
    void write(const char *msg);
};