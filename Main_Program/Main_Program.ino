#include "pitches.h" 
String secretMessage;
int choice = 48;  


int pinTone = 9;

int melody[] = {
  NOTE_C4, NOTE_C6, NOTE_C4
};

// 2 = half notes, 4 = quarter note, 8 = eighth note, 16 = sixteenth note 
int noteValue[] = {
  4, 4, 4
};


void setup() {
  Serial.begin(9600); 
  Serial.println("Hello, welcome to your personal message vault"); 
 
  while(choice == 48) 
  {
    Serial.println("please type in a message you would like to keep safe"); 
  
    while(!Serial.available())
    {
    
    }
  
    secretMessage = Serial.readString();
    Serial.print("the message you have entered in is: "); 
    Serial.println(secretMessage); 
  
    Serial.println("If you would like to keep this message"); 
    Serial.println("1 = yes, keep the message"); 
    Serial.println("0 = no, discard and start over"); 

    while(!Serial.available())
    {
    
    }

    choice = Serial.read();    
  }

  if ( choice == 49 )
  {
    Serial.println("message has been saved, please wait while the vault is locking"); 
    for ( int i = 0 ; i < 2 ; i ++ )
    {
      // iterates through the notes within the melody 
      for (int currentNote = 0; currentNote < 3 ; currentNote++) 
      {
      
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
    
    Serial.println("your message is secured");   
  }
  
 
}




void loop() 
{

}
