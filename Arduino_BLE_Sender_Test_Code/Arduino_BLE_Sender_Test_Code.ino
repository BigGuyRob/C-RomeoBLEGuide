/* Sender Board:
 *  AT+BIND = MAC ADDRESS OF RECIEVER BOARD 
 *  AT+MAC = ? TO GET THE MAC ADDRESS
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.println(115200);
}

void loop() {
  Serial.println(char('A'));
  //When the reciever reads a character 'A' it will execute a digitalWrite to turn pin 13 on
  delay(1000);
  //Delay to keep the reciever reading 'A' for one second
}
