#include <Arduino.h>

class DebugInterface {
  private:
    bool enabled;
  public:
    DebugInterface(bool enable);
    void update();
    void write(byte msg[]);
    void write(const char *msg);
};