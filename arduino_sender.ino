
#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);  //SRX = Din-2, STX = Dpin-3
int receivedNumber;

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
}

void loop()
{
    if (Serial.available()) {
      receivedNumber = Serial.parseInt(); // Read an integer from the Serial Monitor
      
    // Check if the parsing was successful
    if (Serial.read() == '\n') {
      // If a newline character is received, it indicates the end of the number
      Serial.print("Received number: ");
      Serial.println(receivedNumber);
      mySerial.println(receivedNumber);
          
    }
    /*recieve ack*/
     if (mySerial.available())
    {
      Serial.write((char)mySerial.read());
    }
  }
  delay(1000); // Delay for 1 second before sending another number (adjust as needed)

 
}