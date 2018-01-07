#include "pitches.h" 
String secretMessage;
int choice = 48;  
int pinTone1 = 7;

int unlockAttempt; 

volatile int counter;
volatile int programStart; 
volatile int programEnd;  
volatile int programLock; 

int timeStamp1; 
int timeStamp2; 
int timeStamp3; 
int timeStamp4; 
int timeStamp5; 
int timeStamp6; 
int programTimeOut; 

int melody1[] = {
  NOTE_C4, NOTE_C6, NOTE_C4
};

int melody2[] = {
  NOTE_E2, NOTE_E2, NOTE_E2
};

int melody3[] = {
  NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D6
};

// 2 = half notes, 4 = quarter note, 8 = eighth note, 16 = sixteenth note 
int noteValue1[] = {
  4, 4, 4
};

int noteValue2[] = {
  16, 16, 16, 2
};


void setup() {

  //player will swipe magnetic card to initate the program unlcoking mode 
  attachInterrupt(digitalPinToInterrupt(2), magnet_detect, RISING);

  //will detect if signal goes through to interrupt pin 18 - unlock signal
  attachInterrupt(digitalPinToInterrupt(18), message_unlocked , RISING);

  //will detect if signal goes through to interrupt pin 3 - shutdown signal
  attachInterrupt(digitalPinToInterrupt(3), message_lockdown, RISING);

  //will detect if signal goes through to interrupt pin 21 - shutdown signal
  attachInterrupt(digitalPinToInterrupt(21), message_lockdown1, RISING);
  
  DDRB |= (1<<5); //enables pin 13 to pinMode(13,OUTPUT) 
  DDRB |= (1<<4); //enables pin 12 to pinMode(12,OUTPUT)
  DDRB |= (1<<3); //enables pin 11 to pinMode(11,OUTPUT)
  DDRB |= (1<<2); //enables pin 10 to pinMode(10,OUTPUT)
  pinMode(9, OUTPUT); 
  pinMode(12,OUTPUT); 
  
  cli(); //clears interrupt bits 
  TCCR1A =0; //default sets TCCR1A/B to 0 
  TCCR1B = 0;
  TCCR1B = (1 << 2); // set frequency to clk/256, matches clock 1 we're using 
  TIMSK1 |= (7 << 0); // enable OCR interrupts
  //OCR1A = 62500; //output compare register to both A/B
  OCR1B = 65500; //increment specified value and overflows, resets back to 0 
  sei(); // enables interrupt bits for use  

  Serial.begin(9600); 
  timeStamp1 = counter; 
  Serial.print("Program started at: ");
  Serial.print(timeStamp1); 
  Serial.println(" Seconds"); 
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
     timeStamp2 = counter; 
     Serial.print("Program timed out at: ");
     Serial.print(timeStamp2); 
     Serial.println(" Seconds");
     Serial.println("The program has timed out, please try again later"); 
        
     digitalWrite(10,HIGH); 

    for ( int i = 0 ; i < 2 ; i ++ )
    {
      // iterates through the notes within the melody 
      for (int currentNote = 0; currentNote < 3 ; currentNote++) 
      {
      
      // note duration = take one second / note value 
      int noteDuration = 1000 / noteValue1[currentNote];

      // tone(pin, frequency, duration) 
      tone(pinTone1, melody2[currentNote], noteDuration);

      // need to set time delay between notes in order to tell them apart 
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    
      // stops square wave generation from tone() function
      // stopes tone generation from pin 9 
      noTone(pinTone1);    
      }  
    }
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

      // tone(pin, frequency, duration) 
      tone(pinTone1, melody1[currentNote], noteDuration);

      // need to set time delay between notes in order to tell them apart 
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    
      // stops square wave generation from tone() function
      // stopes tone generation from pin 9 
      noTone(pinTone1);    
      }  
    }  
    Serial.println("your message is secured"); 
    
    timeStamp3 = counter; 
    Serial.print("Message locked at: ");
    Serial.print(timeStamp3); 
    Serial.println(" Seconds");
       
    digitalWrite(9,HIGH);
  }

  

}


void loop() {

  programStart = 0; 
  programLock = 0; 

  while(!Serial.available() && programStart == 0)
  {
    
  }

  digitalWrite(10,LOW); 
  
  if ( programStart > 0 ) 
  {
    Serial.println("Card detected...");
    Serial.println("Card accepted...");
    digitalWrite(11,HIGH);
      
    timeStamp4 = counter; 
    Serial.print("HALL Effect sensor triggered at: ");
    Serial.print(timeStamp4); 
    Serial.println(" Seconds");
     
    digitalWrite(12,HIGH);     
  }


  Serial.println("Program state: Unlocking mode");
      
  programTimeOut = timeStamp4 + 15; 


  if ( programTimeOut > counter )
  {
    
    while(!Serial.available() && programEnd == 0 && programTimeOut > counter && programLock == 0)
    {
    
    }

    if ( programEnd > 0 )
    {    
      for (int currentNote = 0; currentNote < 4 ; currentNote++) 
      {
        int noteDuration = 1000 / noteValue2[currentNote]; 
        // tone(pin, frequency, duration) 
        tone(pinTone1, melody3[currentNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
    
        noTone(pinTone1);
     }

      Serial.println("Message has been unlocked successfully!");

      digitalWrite(13,HIGH); 

      unlockAttempt ++ ; 
      timeStamp5 = counter; 
      Serial.print("Message unlocked at: ");
      Serial.print(timeStamp5); 
      Serial.println(" Seconds");
     
      Serial.print("Message: "); 
      Serial.println(secretMessage);

      
      timeStamp6 = counter - timeStamp3 ; 
      Serial.print("Message lock time duration: ");
      Serial.print(timeStamp6); 
      Serial.println(" Seconds");

      Serial.print("Number of unlock attempts: "); 
      Serial.println(unlockAttempt); 
    } 

  }

  if (programEnd == 0 || programLock > 0) 
  {
  
  digitalWrite(10,HIGH); 

    for ( int i = 0 ; i < 2 ; i ++ )
    {
      // iterates through the notes within the melody 
      for (int currentNote = 0; currentNote < 3 ; currentNote++) 
      {
      
      // note duration = take one second / note value 
      int noteDuration = 1000 / noteValue1[currentNote];

      // tone(pin, frequency, duration) 
      tone(pinTone1, melody2[currentNote], noteDuration);

      // need to set time delay between notes in order to tell them apart 
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    
      // stops square wave generation from tone() function
      // stopes tone generation from pin 9 
      noTone(pinTone1);    
      }  
    }

    Serial.println("unlocking mode has been disabled");
    Serial.println("please try again"); 
    Serial.print("Program unlocking has timed out at: ");
    Serial.print(counter); 
    Serial.println(" Seconds");
    unlockAttempt ++ ;  
    digitalWrite(11,LOW);
    digitalWrite(12,LOW); 
  
  }
    
}



 void magnet_detect()
 {
   programStart ++; 
 }

 void message_unlocked()
 {  
   programEnd ++; 
 }

 void message_lockdown()
 {
   programLock ++; 
 }

 void message_lockdown1()
 {
    programLock ++; 
 }

 ISR (TIMER1_COMPB_vect) {
    TCNT1 = 0;
    counter ++; 
    Serial.println(counter);  
  }  
