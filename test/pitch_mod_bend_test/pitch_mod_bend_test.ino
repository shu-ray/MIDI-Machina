/*
    A few notes to self:
    - Minimize calling AnalogRead() and DigitalRead(), on a single pin as possible to avoid inconsistencies
*/

// Pitch Bend pin
const int pBendPin_x = A0;
const int pBendPin_y = A1;
int pBendIdleVal_x = 0;
int pBendIdleVal_y = 0;

// Pitch Modulation pin
const int pModPin_x = A2;
const int pModPin_y = A3;
int pModIdleVal_x = 0;
int pModIdleVal_y = 0;

// Documentation about MIDI programming - http://www.music-software-development.com/midi-tutorial.html - https://midi.org/specifications/midi1-specifications
void MIDI(byte statusByte, byte data1, byte data2){
  Serial.write(statusByte);
  Serial.write(data1);
  Serial.write(data2);
}

// void pitchBend(){
    
// }

// void pitchModulate(){

// }


void setup(){
    Serial.begin(38400);

    // Calibration
    int i = 0;
    while (millis() < 3000){
        if (millis() % 300 == 0){
            Serial.println(millis());                      
            pBendIdleVal_x += analogRead(pBendPin_x);   
            pBendIdleVal_y += analogRead(pBendPin_y);
            pModIdleVal_x += analogRead(pModPin_x);
            pModIdleVal_y += analogRead(pModPin_y);
        i++;
        delay(1);
        }
    }

    // Divide the sum of those analog readings by 10 to get the average value
    pBendIdleVal_x = round(pBendIdleVal_x / 10);
    pBendIdleVal_y = round(pBendIdleVal_y / 10);
    pModIdleVal_x = round(pModIdleVal_x / 10);
    pModIdleVal_y = round(pModIdleVal_y / 10);

    Serial.println(pBendIdleVal_x);
    Serial.println(pBendIdleVal_y);
    Serial.println(pModIdleVal_x);
    Serial.println(pModIdleVal_y);
    Serial.println(i);

}

void loop(){
    // Delay for 1 milisecond for execution stability
    delay(1);
}