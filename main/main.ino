const int notePin[25] = {};

// Storing every note pins latest state by using 2D array as dictionary-like functionality
int lastNotePinState[25][2] = {{}};
int notePrefix = 22;

void sendMIDImessage(byte statusByte, byte data1, byte data2)
{
  Serial.write(statusByte);
  Serial.write(data1);
  Serial.write(data2);
}

void listenKeyboardNotes()
{
    for (int i = 22; i < 48; i++)
    {
        if (digitalRead(i) == HIGH)
        {
            switch (i)
            {
            case 22:
                sendMIDImessage();
                break;
            case 23:
                sendMIDImessage();
                break;
            }
        }
    }
}

void setup(){
    
    // Initialize pins and lastNotePinState 2D array
    for (int i = 22; i < 48; i++)
    {
        pinMode(notePin[i], INPUT_PULLUP);
        // Truncate "i" by notePrefix to set the first element of the 2D array
        lastNotePinState[i-notePrefix][0] = i;
        lastNotePinState[i-notePrefix][1] = LOW;

    }
}