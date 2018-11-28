#include <Adafruit_TCS34725.h>
#include <AFMotor.h>
#include <Servo.h>

int RCONST = 150;
int LCONST = 145;
int BRCONST = 140;
int BLCONST = 125;
const int CONSTANT = 7;
const int oneStep = 57;
int rightSpeed, leftSpeed;
const int qtr[8] = {23, 25, 27, 29, 31, 33, 35, 37};
const int qtrTurn = 39;
const int stepPin = 51 ;
const int dirPin = 49;
const int sharp = 50;
const int sharpLeft = 48;
const int sharpRight = 46;
AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(1);
Servo gripper;
Servo arm;
int posGripper = 40, posArm = 90;
int errvalue;
uint16_t start, clearr, red, green, blue;
float avarage, r, g, b;
boolean controlBack = true;
int cnt = 0;
int currentStep = 0;
int counterfinish;
boolean controlColor = false;
boolean objectControl = true;


float r_[10];
float g_[10];
float b_[10];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);



void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; i++) {
    pinMode(qtr[i], INPUT_PULLUP);
  }
  pinMode(qtrTurn, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(sharp, INPUT);
  gripper.attach(52);
  arm.attach(53);

  gripper.write(posGripper);
  arm.write(posArm);
  //goMotors(RCONST, LCONST, 1);
  delay(50);
  Serial.begin(9600);

}

void loop() {
  /*
    goMotors(RCONST,LCONST,1);
    delay(4000);
    goMotors(BRCONST,BLCONST,0);
    delay(4000);*/



  if (lineControl()) {
    follow_line(1);
  }
  else {
    Serial.println("İzlimicem");
    //sharpları oku
    //sevoyu çalıştır
    //sharpı kontrol et
    stopMotors();
    delay(1000);
    if (cnt < 7) {
      r_[cnt] = r;
      g_[cnt] = g;
      b_[cnt] = b;

      while (checkSharp()) {
        goMotors(120, 115, 1);
      }
      stopMotors();

      takeObject();

      TurnStep(1, oneStep);


      goMotors(BRCONST, BLCONST, 0);
      delay(1000);
      controlBack = true;
      while (controlBack) {
        follow_line(0);
      }
      //if(!((r_[cnt]-0.03<r)&&(r <r_[cnt]+0.03) && (g_[cnt]-0.03<g)&&(g < g_[cnt]+0.03) &&(b_[cnt]-0.03<b)))
      cnt++;
      RCONST = RCONST + 3;
      LCONST = LCONST + 3;
      BRCONST = BRCONST + 3;
      BLCONST = BLCONST + 3;

    }
    else {
      controlColor = false;
      objectControl = true;
      int i = findColor();
      if (controlColor) {
        int k = currentStep - i;
        if (k > 0) {
          TurnStep(0, k * oneStep);
        }
        else if (k < 0) {
          TurnStep(1, -(k * oneStep));
        }
        currentStep = i;
        breakObject();
        if (objectControl) {
          goMotors(RCONST, LCONST, 1);
          delay(200);
          stopMotors();
          checkSharp();
          if (objectControl) {
            breakObject();
            counterfinish--;
          }
        }
      }
      if (counterfinish > 6) {
        stopMotors();
        while (true) {
          for (posGripper = 50; posGripper <= 75; posGripper += 1) { // goes from 180 degrees to 0 degrees
            gripper.write(posGripper);              // tell servo to go to posGripperition in variable 'posGripper'
            delay(15);
          }
          for (posGripper = 75; posGripper >= 50; posGripper -= 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            gripper.write(posGripper);              // tell servo to go to posGripperition in variable 'posGripper'
            delay(15);
          }
        }
      }
      goMotors(BRCONST, BLCONST, 0);
      delay(400);
      controlBack = true;
      while (controlBack) {
        follow_line(0);
      }
    }
  }

}
boolean lineControl() {
  int counter = 0;
  readColor();
  while (!(((0.85 < r) && (r < 0.95) && (1.10 < g) && (g < 1.20) && (0.90 < b) && (b < 1)) || ((0.81 < r) && (r < 0.91) && (1.11 < g) && (g < 1.21) && (0.94 < b) && (b < 1.04)))) { //siyah ve beyaz olmama durumunda
    readColor();
    counter++;
    if (counter > 2) {
      return false;
      break;
    }
  }
  return true;

}
boolean ControlT() {
  int turn = calculateQTR();

  if (turn == 0 || turn == 1 || turn == 2 || turn == 3) {
    return true;
  }
  else return false;
}
