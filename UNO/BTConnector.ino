// Library to make a Software UART
#include <SoftwareSerial.h>

#define RX 3
#define TX 2

// Use below values for Arduino Mega pin configurations

// #define RX 11
// #define TX 10

#define BAUDRATE 9600

char c = ' ';
boolean new_line = true;

// Instantiation of a Software UART
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

void setup() {  

  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);
  
  // HM-10 default speed in AT command mode
  BTSerial.begin(BAUDRATE);
  
  Serial.println("Enter AT commands:");
}

void loop() {
  
  // Keep reading from HM-10 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HM-10
  if (Serial.available()) {

    // Read from the Serial buffer (from the user input)
    c = Serial.read();

    // Do not send newline ('\n') nor carriage return ('\r') characters
    if(c != 10 && c != 13)
      BTSerial.write(c);

    // If a newline ('\n') is true; print newline + prompt symbol; toggle
    if (new_line) { 
      Serial.print("\r\n>");
      new_line = false;
    }

    // Write to the Serial Monitor the bluetooth's response
    Serial.write(c);
    
    // If a newline ('\n') is read, toggle
    if (c == 10)
      new_line = true;
  }
}
