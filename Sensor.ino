int calculateQTR() {
  int control = 0;
  for (int i = 0; i < 8; i++) {
    control = control + digitalRead(qtr[i]);
  }
  return control;
}

void printSensors() {
  Serial.print("qtr ön : ");
  for (int i = 0; i < 8; i++) {
    Serial.print(digitalRead(qtr[i]));
    Serial.print("  ");
  }
  Serial.println();
}

boolean checkSharp(){
  if(!digitalRead(sharp)){
    objectControl=false;
    return false;
  }
  else if(!digitalRead(sharpLeft)||!digitalRead(sharpRight)){
    goMotors(BRCONST,BLCONST,0);
    delay(1500);
   while(lineControl()) {
    follow_line(1);
  }
  while(digitalRead(sharp)&&digitalRead(sharpLeft)&&digitalRead(sharpRight)){
     goMotors(120, 115, 1);
  }
  return false;
  
  }

  return true;
}




