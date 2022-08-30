const int RevRight = 3;
const int FwdRight = 4;
const int RevLeft = 5;
const int FwdLeft = 6;
const int FpingPin = 2;
long Fduration, Finches;
#include <PS3BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch
void setup() {
Serial.begin(115200);
pinMode(RevLeft,OUTPUT);
pinMode(RevRight,OUTPUT);
pinMode(FwdRight,OUTPUT);
pinMode(FwdLeft,OUTPUT);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop(){
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    } else {
      if (PS3.getButtonPress(UP)) {
        Serial.println('F');
        Forward();
        delay(1);
      }else if (PS3.getButtonPress(DOWN)) {
        Serial.print(F("\r\nDown"));
        Backwards();
        delay(1);
      } else if(PS3.getButtonPress(RIGHT)){
        Serial.print(F("\r\nRight"));
        Right();
        delay(1);
        } else if(PS3.getButtonPress(LEFT)){
        Serial.print(F("\r\nLeft"));
        Left();
        delay(1);
      }else{
        Serial.println("Stop");
        Stop();
        }    
      }
    }else{
      Serial.println("Auto");
    }
  }

void Backwards(){
  //Light Should be Red on the Spike Relay
 digitalWrite(FwdRight,LOW);
  digitalWrite(FwdLeft,LOW);
  digitalWrite(RevRight,HIGH);
  digitalWrite(RevLeft,HIGH);
  // Test With Servo analogWrite(5,1);
  delay(1);
}
void Stop(){
  //Light Should be Orange on the Spike Relay
 digitalWrite(FwdRight,LOW);
  digitalWrite(FwdLeft,LOW);
  digitalWrite(RevRight,LOW);
  digitalWrite(RevLeft,LOW);
  // Test With Servo analogWrite(5,0);
  delay(1);
}

void Forward(){
  //Light Should be Green on the Spike Relay
  digitalWrite(FwdRight,HIGH);
  digitalWrite(FwdLeft,HIGH);
  digitalWrite(RevRight,LOW);
  // Test With Servo analogWrite(5,254);
  digitalWrite(RevLeft,LOW);
  delay(1);
}
void Right(){
  //Light Should be Red on the Spike Relay
 digitalWrite(FwdRight,LOW);
  digitalWrite(FwdLeft,HIGH);
  digitalWrite(RevRight,HIGH);
  digitalWrite(RevLeft,LOW);
  // Test With Servo analogWrite(5,1);
  delay(1);
}
void Left(){
  //Light Should be Red on the Spike Relay
 digitalWrite(FwdRight,LOW);
  digitalWrite(FwdLeft, HIGH);
  digitalWrite(RevRight,HIGH);
  digitalWrite(RevLeft,LOW);
  // Test With Servo analogWrite(5,1);
  delay(1);
}

void AutoMode(){
  pinMode(FpingPin, OUTPUT); //output
  digitalWrite(FpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(FpingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(FpingPin, LOW); //input
  pinMode(FpingPin, INPUT);
  Fduration = pulseIn(FpingPin, HIGH);

  Finches = FmicrosecondsToInches(Fduration);

  Serial.println(Finches);
if (Finches <= 10){
  Stop();
  }else{
    Forward();
  }
}

long FmicrosecondsToInches(long Fmicroseconds) {
  return Fmicroseconds / 74 / 2;
}

