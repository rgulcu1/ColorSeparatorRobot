void goMotors(int motor1, int motor2, int drc) {
  if (drc == 1) {
    motorRight.setSpeed(motor1);
    motorLeft.setSpeed(motor2);
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
  }
  else if (drc == 0) {
    motorRight.setSpeed(motor1);
    motorLeft.setSpeed(motor2);
    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
  }
}
void stopMotors() {
  motorRight.setSpeed(RCONST);
  motorLeft.setSpeed(LCONST);
  motorRight.run(BACKWARD);
  motorLeft.run(BACKWARD);
  delay(20);
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
}
void turnRight() {
  boolean control = true;
  motorRight.setSpeed(180);
  motorLeft.setSpeed(175);
  motorRight.run(BACKWARD);
  motorLeft.run(FORWARD);
  delay(350);

  while (control) {
    motorRight.setSpeed(150);
    motorLeft.setSpeed(145);
    motorRight.run(BACKWARD);
    motorLeft.run(FORWARD);
    if (!digitalRead(qtr[3]) || !digitalRead(qtr[2])) control = false;
  }
  motorRight.setSpeed(RCONST);
  motorLeft.setSpeed(RCONST);
  motorRight.run(FORWARD);
  motorLeft.run(BACKWARD);
  delay(20);
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);

}
void turnLeft() {
  boolean control = true;
  motorRight.setSpeed(180);
  motorLeft.setSpeed(175);
  motorRight.run(FORWARD);
  motorLeft.run(BACKWARD);
  delay(350);

  while (control) {
    motorRight.setSpeed(150);
    motorLeft.setSpeed(145);
    motorRight.run(FORWARD);
    motorLeft.run(BACKWARD);
    if (!digitalRead(qtr[4]) || !digitalRead(qtr[5])) control = false;
  }
  motorRight.setSpeed(RCONST);
  motorLeft.setSpeed(RCONST);
  motorRight.run(BACKWARD);
  motorLeft.run(FORWARD);
  delay(20);
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
}

void TurnStep(int dir, int stepNum) {

  if (dir == 1) {
    currentStep++;
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x < stepNum; x++) // Loop 200 times
    {
      digitalWrite(stepPin, HIGH); // Output high
      delay(10);
      digitalWrite(stepPin, LOW); // Output low
      delay(10); // Wait
    }
  }
  else {
    digitalWrite(dirPin, LOW); //Changes the rotations direction
    // Makes 400 pulses for making two full cycle rotation
    for (int x = 0; x < stepNum; x++) {
      digitalWrite(stepPin, HIGH);
      delay(10);
      digitalWrite(stepPin, LOW);
      delay(10);
    }

  }
  if (currentStep > 6) currentStep = 0;
}

void takeObject() {

  for (posArm = 90; posArm <= 180; posArm += 1) { // goes from 180 degrees to 0 degrees
    arm.write(posArm);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  for (posGripper = 40; posGripper <= 70; posGripper += 1) { // goes from 180 degrees to 0 degrees
    gripper.write(posGripper);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  for (posArm = 180; posArm >= 20; posArm -= 1) { // goes from 180 degrees to 0 degrees
    arm.write(posArm);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  for (posGripper = 70; posGripper >= 40; posGripper -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    gripper.write(posGripper);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  for (posArm = 20; posArm <= 90; posArm += 1) { // goes from 180 degrees to 0 degrees
    arm.write(posArm);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);

}

void breakObject(){
  for (posGripper = 40; posGripper <= 50; posGripper += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    gripper.write(posGripper);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  for (posArm = 90; posArm >= 15; posArm -= 1) { // goes from 180 degrees to 0 degrees
    arm.write(posArm);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  for (posGripper = 50; posGripper <= 70; posGripper += 1) { // goes from 180 degrees to 0 degrees
    gripper.write(posGripper);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  for (posArm = 15; posArm <= 180; posArm += 1) { // goes from 180 degrees to 0 degrees
    arm.write(posArm);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  checkSharp();
  delay(500);
   for (posGripper = 70; posGripper >= 50; posGripper -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    gripper.write(posGripper);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  checkSharp();
   for (posArm = 180; posArm >= 90; posArm -= 1) { // goes from 180 degrees to 0 degrees
    arm.write(posArm);              // tell servo to go to posGripperition in variable 'posGripper'
    delay(15);
  }
  delay(500);
  
  
  counterfinish++;
}


