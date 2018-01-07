#include "pitches.h" 
String secretMessage;
int choice = 48;  

volatile int counter;

int pinTone = 9;

int melody1[] = {
  NOTE_C4, NOTE_C6, NOTE_C4
};

// 2 = half notes, 4 = quarter note, 8 = eighth note, 16 = sixteenth note 
int noteValue1[] = {
  4, 4, 4
};


void setup() {
  
  DDRB |= (1<<5); //enables pin 13 to pinMode(13,OUTPUT) 
  cli(); //clears interrupt bits 
  TCCR1A =0; //default sets TCCR1A/B to 0 
  TCCR1B = 0;
  TCCR1B = (1 << 2); // set frequency to clk/256, matches clock 1 we're using 
  TIMSK1 |= (7 << 0); // enable OCR interrupts
  //OCR1A = 62500; //output compare register to both A/B
  OCR1B = 65500; //increment specified value and overflows, resets back to 0 
  sei(); // enables interrupt bits for use  
  
  Serial.begin(9600); 
  Serial.println("Hello, welcome to your personal message vault"); 

  if ( counter < 20 ) 
  {
    while(choice == 48 && counter < 21) 
    {
      Serial.println("please type in a message you would like to keep safe"); 
  
      while(!Serial.available() && counter < 21)
      {
    
      }
    if(counter < 20)
    {
      secretMessage = Serial.readString();
      Serial.print("the message you have entered in is: "); 
      Serial.println(secretMessage); 
  
      Serial.println("If you would like to keep this message"); 
      Serial.println("1 = yes, keep the message"); 
      Serial.println("0 = no, discard and start over"); 

      while(!Serial.available() && counter < 21)
      {
    
      }
      
    if(counter<20)
      {
        choice = Serial.read(); 
      }
    }
   }
   if( counter >= 20)
   {
     Serial.println("The program has timed out, please try again later"); 
   }
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
      int noteDuration = 1000 / noteValue1[currentNote];

      // tone() function generates a square wave frequency on a pin
      // Arduino UNO accepts frequency between 31 - 65535 (Hz) 
      // Note frequency corresponds with pitches.h header file 
      // tone(pin, frequency, duration) 
      tone(pinTone, melody1[currentNote], noteDuration);

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

ISR (TIMER1_COMPB_vect) {
  //Serial.println("Reached 65500"); 
  TCNT1 = 0;
  counter ++; 
  //Serial.println(counter);  
} 
