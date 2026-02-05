#include <robot_hand_library.h>

RobotHand hand;

void setup() {
  Serial.begin(9600);
  hand.begin();
  Serial.println("Send: <finger>,<angle>,<joint> OR open / close");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    //input example: "1,90,75" or "open" or "close"
    //엄지 1, 검지 2, 중지 3, 약지 4, 새끼 5
    // angle: 0~180, joint: 75~105
    hand.parseCommand(input);
  }
}