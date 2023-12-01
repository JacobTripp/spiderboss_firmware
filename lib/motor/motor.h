#ifndef motor_h
#define motor_h

namespace motor {
  class Motor {
    public:
      int stepsPerRev;
      int pin;
      int dirPin;
      bool curLevel;
      unsigned long stepDelay;
      unsigned long lastStep;

      Motor::Motor(int, int, int);
      void toggle();
      void step(unsigned long);
      void setRPM(int);
      void setDirection(bool);
  };
}
#endif
