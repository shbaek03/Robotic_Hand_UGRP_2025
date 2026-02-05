#include "robot_hand_library.h"

RobotHand::RobotHand() : pwm(Adafruit_PWMServoDriver()) {}

void RobotHand::begin() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(60);
  delay(10);
}

void RobotHand::setFinger(uint8_t fingerNum, uint16_t angle, uint16_t joint) {
  if (fingerNum < 1 || fingerNum > 5) {
    // Serial.println("Invalid finger number");
    return;
  }
  if (fingerNum != 1 && (angle > 180 || joint > 105 || joint < 75)) {
    Serial.println("Invalid finger number (1~5) or angle values");
    return;
  }

  uint8_t anglePin = motorPins[fingerNum - 1][0];
  uint8_t jointPin = motorPins[fingerNum - 1][1];

  pwm.setPWM(anglePin, 0, angleToPulse(angle));
  pwm.setPWM(jointPin, 0, angleToPulse(joint));

  /*Serial.print("Finger ");
  Serial.print(fingerNum);
  Serial.print(" - Angle: ");
  Serial.print(angle);
  Serial.print("°, Joint: ");
  Serial.print(joint);
  Serial.println("°");*/
}

void RobotHand::openHand() {
  for (uint8_t i = 1; i <= 5; i++) {
    setFinger(i, 0, 90);
  }
}

void RobotHand::closeHand() {
  for (uint8_t i = 1; i <= 5; i++) {
    setFinger(i, 180, 90);
  }
}

void RobotHand::parseCommand(String input) {
  input.trim();

  if (input.equalsIgnoreCase("open")) {
    openHand();
    Serial.println("Hand opened");
    return;
  }

  if (input.equalsIgnoreCase("close")) {
    closeHand();
    Serial.println("Hand closed");
    return;
  }

  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);

  if (firstComma > 0 && secondComma > firstComma) {
    int fingerNum = input.substring(0, firstComma).toInt();
    int angle = input.substring(firstComma + 1, secondComma).toInt();
    int joint = input.substring(secondComma + 1).toInt();

    setFinger(fingerNum, angle, joint);
  } else {
    Serial.println("Invalid format. Use: <finger>,<angle>,<joint> OR open/close");
  }
}

uint16_t RobotHand::angleToPulse(uint16_t angle) {
  return map(angle, 0, 180, 150, 600);
}
