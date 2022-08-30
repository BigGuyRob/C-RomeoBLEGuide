/*
  Arduino Board
  AT-Command set to peripheral, as a reciever and connected
  to another Arduino Board, with Mac Address 0xC4EDBA4B76BE
  that Mac Address is a controller, Arduino Romeo BLE v1.0
  

  The receiver is using commands from the test code at
  DFRobot.com  for the cherokee mobile robot to reference
  and execute when characters are recieved from the sender

  If the controller is linked with the reciever it is in "Controller Mode"
  Where you can control the car, any other time it is in "Drone Mode"
  Where 3 ping sensors dictate where the car goes
*/

int horn = 12;
int speedPin_M1 = 5;     //M1 Speed Control
int speedPin_M2 = 6;     //M2 Speed Control
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control
const int frontpingPin = 2;
const int rightpingpin = 11;
const int leftpingpin = 9;
long frontduration = 0;
long frontinches;
 long rightduration = 0;
 long rightinches;
 long leftduration = 0;
 long leftinches;

void setup() {
  pinMode(frontpingPin,OUTPUT);
  pinMode(rightpingpin,OUTPUT);
  pinMode(leftpingpin,OUTPUT);
  Serial.begin(115200);
  Serial.print("Initialize");
  Serial.println();
  
}

void loop() {
CheckPing();
//while (!Serial.available()){
  //AutoMode();
//}
//ControllerMode();
Serial.println("Front =");
Serial.print(frontinches);
Serial.println("Left =");
Serial.print(leftinches);
Serial.println("Right =");
Serial.print(rightinches);
}

void CheckPing(){
  CheckFrontDistance();
  CheckSideDistances();
}

void AutoMode(){
  if (frontinches >= 5){
    carAdvance(250,250);
  }else{
    carStop();
  }
}

void ControllerMode(){
if (Serial.available()){
  delay(1);
  //Backwards Signal
  if (Serial.read() == 'A') {
   carBack(250,250);
    delay(1);
    //Forward Signal
  } else if (Serial.read() == 'B'){
   carAdvance(250,250);
    delay(1);
    }  else if(Serial.read() == 'R'){
      tone(horn,512);
      delay(1);
    } else if (Serial.read() == 'D'){
      carTurnLeft(250,250);
      delay(1);
    } else if (Serial.read() == 'F'){
      carTurnRight(250,250);
      delay(1);
    }
    else {
      carStop();
      noTone(horn);
      delay(1);
    }
  }
}

 
  void CheckFrontDistance(){
  pinMode(frontpingPin, OUTPUT);
  digitalWrite(frontpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontpingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(frontpingPin, LOW);
  pinMode(frontpingPin, INPUT);
  frontduration = pulseIn(frontpingPin, HIGH);
  frontinches = frontmicrosecondsToInches(frontduration);
   delayMicroseconds(1);
  }

  void CheckSideDistances(){
  //Right Side
  pinMode(rightpingpin, OUTPUT);
  digitalWrite(rightpingpin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightpingpin, HIGH);
  delayMicroseconds(5);
  digitalWrite(rightpingpin, LOW);
  pinMode(rightpingpin, INPUT);
  rightduration = pulseIn(rightpingpin, HIGH);
  rightinches = rightmicrosecondsToInches(rightduration);
 delayMicroseconds(1);
//Left Side
  pinMode(leftpingpin, OUTPUT);
  digitalWrite(leftpingpin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftpingpin, HIGH);
  delayMicroseconds(5);
  digitalWrite(leftpingpin, LOW);
  pinMode(leftpingpin, INPUT);
  leftduration = pulseIn(leftpingpin, HIGH);
  leftinches = leftmicrosecondsToInches(leftduration);
  delayMicroseconds(1); 
  }
void carAdvance(int leftSpeed,int rightSpeed){         //Move backward
  analogWrite (speedPin_M2,leftSpeed);              //PWM Speed Control
  digitalWrite(directionPin_M1,HIGH);    
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,HIGH);
} 

void carStop(){                 //  Motor Stop
  digitalWrite(speedPin_M2,0); 
  digitalWrite(directionPin_M1,LOW);    
  digitalWrite(speedPin_M1,0);   
  digitalWrite(directionPin_M2,LOW);    
}   

void carBack(int leftSpeed,int rightSpeed){       //Move forward
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,LOW);   
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,LOW);
}

void carTurnLeft(int leftSpeed,int rightSpeed){      //Turn Right
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,HIGH);    
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,LOW);
}

void carTurnRight(int leftSpeed,int rightSpeed){      //Turn Left
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,LOW);    
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,HIGH);
}

long frontmicrosecondsToInches(long frontmicroseconds) {
  return frontmicroseconds / 74 / 2;
}
long rightmicrosecondsToInches(long rightmicroseconds){
  return rightmicroseconds /74 / 2;
}
long leftmicrosecondsToInches(long leftmicroseconds){
  return leftmicroseconds /74 / 2;
}
