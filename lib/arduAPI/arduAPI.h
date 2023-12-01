#include <Arduino.h>
#ifndef arduAPI_h
#define arduAPI_h

namespace arduAPI {
  class CfgParser {
    public:
      int motor0_rpm;
      int motor1_rpm;
      int motor2_rpm;
      int motor3_rpm;
      bool isValid;
      unsigned long duration;

      void parse(String);
  };
}
#endif
