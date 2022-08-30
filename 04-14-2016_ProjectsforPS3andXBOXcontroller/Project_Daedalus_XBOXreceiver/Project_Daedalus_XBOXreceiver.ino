const int right = 10;
const int left = 9;

void setup() {
  Serial.begin(115200);
  pinMode(right,OUTPUT);
  pinMode(left,OUTPUT);
}
void loop() {

    if (Serial.read() == ('F')){
       digitalWrite(right,HIGH);
       digitalWrite(left,HIGH);
       delay(2);
       digitalWrite(left,LOW);
       digitalWrite(right,LOW);
    } else if (Serial.read() == ('B')){
      digitalWrite(left,HIGH);
      digitalWrite(right,HIGH);
      delay(1);
      digitalWrite(right,LOW);
      digitalWrite(left,LOW);
      delay(1);
    } else  if (Serial.read() == ('R')){
      //carTurnRight(250,250);
      delay(1);
    } else if (Serial.read() == ('L')){
      //carTurnLeft(250,250);
      delay(1);
    } else  if(Serial.read() == ('S')) {
      digitalWrite(left,HIGH);
      digitalWrite(right,HIGH);
      delayMicroseconds(1500);
      digitalWrite(left,LOW);
      digitalWrite(right,LOW);
      delayMicroseconds(500);
    }
}



