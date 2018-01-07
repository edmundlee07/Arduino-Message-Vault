
//Code generates a tone with the 8-ohm speaker

//include header file with various pitches 
#include "pitches.h"

// what pin will generate signal to speaker
int pinTone = 9;

// notes in the melody:
int melody[] = {
  NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D6
};

// note durations array contains the values of musical notes 
// 2 = half notes, 4 = quarter note, 8 = eighth note, 16 = sixteenth note 
int noteValue[] = {
  16, 16, 16, 2
};

void setup() {
  
  // iterates through the notes within the melody 
  for (int currentNote = 0; currentNote < 4 ; currentNote++) {

    // note duration = take one second / note value 
    int noteDuration = 1000 / noteValue[currentNote];

    // tone() function generates a square wave frequency on a pin
    // Arduino UNO accepts frequency between 31 - 65535 (Hz) 
    // Note frequency corresponds with pitches.h header file 
    // tone(pin, frequency, duration) 
    tone(pinTone, melody[currentNote], noteDuration);

    // need to set time delay between notes in order to tell them apart 
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // stops square wave generation from tone() function
    // stopes tone generation from pin 9 
    noTone(pinTone);
  }
  
}

void loop() {
  
}
