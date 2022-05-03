// Simple sketch to test MIDI connections using a single digital pin and switch

const int buttonPin = 23;
int buttonRead = 0;
int lastButtonState = HIGH;

void sendMIDImessage(byte statusByte, byte data1, byte data2){
  Serial.write(statusByte);
  Serial.write(data1);
  Serial.write(data2);
  }

void setup(){
  pinMode(buttonPin,INPUT_PULLUP);
  
  // Start up serial connection
  Serial.begin(38400);
}

void loop(){
  buttonRead = digitalRead(buttonPin);

  // Check for pin changes and send MIDI signal accordingly
  if (buttonRead != lastButtonState){
    //Serial.print("!\n");
    if (buttonRead == LOW){
      sendMIDImessage(10010000,64,64);
    //  Serial.print("noteon\n");
      lastButtonState = LOW;
    }
    if (buttonRead == HIGH){
      sendMIDImessage(10000000,64,0);
    //  Serial.print("noteoff\n");
      lastButtonState = HIGH;
    }

  }

  // Delay for 1 milisecond for execution stability
  delay(1);
}
