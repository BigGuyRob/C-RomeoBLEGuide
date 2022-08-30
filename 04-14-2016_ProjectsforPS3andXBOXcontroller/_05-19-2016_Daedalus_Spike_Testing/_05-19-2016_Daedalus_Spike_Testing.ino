const int RevRight = 3;
const int FwdRight = 4;
const int RevLeft = 5;
const int FwdLeft = 6;

void setup() {
pinMode(RevLeft,OUTPUT);
pinMode(RevRight,OUTPUT);
pinMode(FwdRight,OUTPUT);
pinMode(FwdLeft,OUTPUT);
}

void loop() {
Forward();
Stop();
Backwards();
Stop();
}

void Forward(){
  //Light Should be Green on the Spike Relay
  digitalWrite(FwdRight,HIGH);
  digitalWrite(FwdLeft,HIGH);
  digitalWrite(RevRight,LOW);
  digitalWrite(RevLeft,LOW);
  delay(3000);
}
void Stop(){
  //Light Should be Orange on the Spike Relay
 digitalWrite(FwdRight,LOW);
  digitalWrite(FwdLeft,LOW);
  digitalWrite(RevRight,LOW);
  digitalWrite(RevLeft,LOW);
  delay(2000);
}
void Backwards(){
  //Light Should be Red on the Spike Relay
 digitalWrite(FwdRight,LOW);
  digitalWrite(FwdLeft,LOW);
  digitalWrite(RevRight,HIGH);
  digitalWrite(RevLeft,HIGH);
  delay(3000);
}

