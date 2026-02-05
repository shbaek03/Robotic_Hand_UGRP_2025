#include <robot_hand_library.h>

RobotHand hand;

void setup() {
  Serial.begin(250000);
  hand.begin();
  Serial.println("Send: <finger>,<angle>,<joint> OR open / close");
}

void loop() {
  static String input = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      hand.parseCommand(input);
      input = "";  // clear after use
    } else {
      input += c;
    }
  }
}