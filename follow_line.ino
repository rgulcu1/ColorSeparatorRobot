void follow_line(int choice) {
  int error;

  if (choice == 1) {

    if (ControlT()) {
      stopMotors();
      delay(500);
      goMotors(RCONST, LCONST, 1);
      delay(300);
      while (digitalRead(qtrTurn)) {
        follow_line(1);
      }
      stopMotors();
      delay(100);
      turnRight();
      goMotors(RCONST, LCONST, 1);
      delay(50);
    }
    else {
      error = calculateErrors();
      rightSpeed = RCONST + error;
      leftSpeed = LCONST - error;

      if (rightSpeed > 255 || rightSpeed < 0 || leftSpeed > 255 || leftSpeed < 0) {
        if (rightSpeed > 255) rightSpeed = 255;
        if (leftSpeed > 255) leftSpeed = 255;
        if (rightSpeed < 0) {
          rightSpeed = -rightSpeed;
          motorRight.setSpeed(rightSpeed);
          motorRight.run(BACKWARD);
        }
        if (leftSpeed < 0) {
          leftSpeed = -leftSpeed;
          motorLeft.setSpeed(leftSpeed);
          motorLeft.run(BACKWARD);
        }
      }
      else {
        goMotors(rightSpeed, leftSpeed, 1); //1 ileri yön
      }
    }
  }
  else {
    if (ControlT()) {
      motorRight.setSpeed(RCONST);
      motorLeft.setSpeed(LCONST);
      motorRight.run(FORWARD);
      motorLeft.run(FORWARD);
      delay(20);
      motorRight.setSpeed(0);
      motorLeft.setSpeed(0);
      delay(500);
      goMotors(RCONST, LCONST, 1);
      delay(400);
      while (digitalRead(qtrTurn)) {
        follow_line(1);
      }
      stopMotors();
      delay(100);
      turnLeft();
      goMotors(RCONST, LCONST, 1);
      delay(50);
      controlBack = false;
    }
    else {
      goMotors(BRCONST, BLCONST, 0);
    }
  }
}
int calculateErrors() {


  if (!digitalRead(qtr[0]))  errvalue = 12 * CONSTANT;
  else if (!digitalRead(qtr[1]))  errvalue = 8 * CONSTANT;
  else if (!digitalRead(qtr[2]))  errvalue = 5 * CONSTANT;
  else if (!digitalRead(qtr[3]))  errvalue = 0;
  else if (!digitalRead(qtr[4]))  errvalue = 0;
  else if (!digitalRead(qtr[5]))  errvalue = -5 * CONSTANT;
  else if (!digitalRead(qtr[6]))  errvalue = -12 * CONSTANT;
  else if (!digitalRead(qtr[7]))  errvalue = -15 * CONSTANT;
  else errvalue = 0;

  return errvalue;


}

