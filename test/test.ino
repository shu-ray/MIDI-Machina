// Simple sketch to test MIDI connections using a single digital pin and switch

const int buttonPin = 2;
int lastButtonState = LOW;

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

  // Check for pin changes and send MIDI signal accordingly
  if (digitalRead(buttonPin) != lastButtonState){
    if (lastButtonState == HIGH) sendMIDImessage(10010000,00111100,64);
    if (lastButtonState == LOW) sendMIDImessage(10000000,00111100,00000000);
    //if (lastButtonState == LOW) Serial.println("on");
    //if (lastButtonState == HIGH) Serial.println("off");
    }

  // Set last pin state
  lastButtonState = digitalRead(buttonPin);

  // Delay for 1 milisecond for execution stability
  delay(1);
}
