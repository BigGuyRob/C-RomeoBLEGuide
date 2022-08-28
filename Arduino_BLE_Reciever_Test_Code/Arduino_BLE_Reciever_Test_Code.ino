/* Reciever Board:
 *  AT+BIND = MAC ADDRESS OF SENDER BOARD
 *  AT+MAC = ? TO GET THE MAC ADDRESS 
 * 
 */
void setup() {
 Serial.begin(57600);
 Serial.println("115200");
}

void loop() {
  if(Serial.read() == 54){
    Serial.println(54);
  }
}
