#define ACTIVITY_LED_DURATION 500

class ActivityLed {
  private:
    unsigned long previousMillis = 0;
    int state = LOW;
  public:
    void update();
    void blink();
};