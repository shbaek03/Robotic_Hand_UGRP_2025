#ifndef ROBOT_HAND_LIBRARY_H
#define ROBOT_HAND_LIBRARY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class RobotHand {
  public:
    RobotHand();
    void begin();
    void setFinger(uint8_t fingerNum, uint16_t angle, uint16_t joint);
    void openHand();
    void closeHand();
    void parseCommand(String input);

  private:
    Adafruit_PWMServoDriver pwm;
    uint16_t angleToPulse(uint16_t angle);
    
    // 핀 매핑: [fingerNum - 1][0:angle / 1:joint]
    const uint8_t motorPins[5][2] = {
      {8, 9},  // thumb
      {7, 3},  // index
      {6, 2},  // middle
      {5, 1},  // ring
      {4, 0}   // pinky
    };
};

#endif // ROBOT_HAND_LIBRARY_H