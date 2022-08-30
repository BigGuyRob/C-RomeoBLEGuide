int speedPin_M1 = 5;     //M1 Speed Control
int speedPin_M2 = 6;     //M2 Speed Control
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control

#include <XBOXUSB.h>
//#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXUSB Xbox(&Usb);
//XBOXRECV Xbox(&Usb);

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
}
void loop() {
  Usb.Task();
  if (Xbox.Xbox360Connected /*||Xbox.XboxReceiverConnected*/) {
    Xbox.setLedOn(LED1);
    //for (uint8_t i = 0; i < 4; i++) {
      //if(Xbox.Xbox360Connected[i]){
    if (Xbox.getButtonPress(R2) > 50) {
      Serial.println('F');
       Xbox.setRumbleOn(Xbox.getButtonPress(L2), Xbox.getButtonPress(R2));
      delay(1);
    } else
       if (Xbox.getButtonPress(L2) > 50) {
        Serial.println('B');
         Xbox.setRumbleOn(Xbox.getButtonPress(L2), Xbox.getButtonPress(R2));
      delay(1);
    } else if(Xbox.getButtonClick(RIGHT)){
        Serial.println('R');
        delay(1);
    }else if(Xbox.getButtonClick(LEFT)){
        Serial.println('L');
        delay(1);
    } else if(Xbox.getButtonClick(B)){
        Serial.println('S');
        delay(1);
    }else{
      Xbox.setRumbleOn(0,0);
      delay(1);
      
      
        }
      }
    }
  //}
//}
