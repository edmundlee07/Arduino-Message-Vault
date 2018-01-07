
volatile int counterB;
volatile int counterA; 


void setup() { 
  Serial.begin(9600); // used for testing with serial monitor 
  DDRB |= (1<<5); //enables pin 13 to pinMode(13,OUTPUT) 
  cli(); //clears interrupt bits 
  TCCR1A =0; //default sets TCCR1A/B to 0 
  TCCR1B = 0;
  TCCR1B = (1 << 2); // set frequency to clk/256, matches clock 1 we're using 
  TCCR1A = (1 << 2); // set frequency to clk/256, matches clock 1 we're using 
  TIMSK1 |= (7 << 0); // enable OCR interrupts
  OCR1A = 65500; //output compare register to both A/B
  OCR1B = 65500; //increment specified value and overflows, resets back to 0 
  sei(); // enables interrupt bits for use    
}
  
void loop() {
  // put your main code here, to run repeatedly:

}

- we want our timer to start counting when there are 20 comapre overflows ot the certian timer value 65500 
- so our hall effetc sensor will allow us to have an interrupt function to allow detection 
  of when the progrma will start, once the keycard is waved by the individual 
- we want our timere to start once the person has triggered the hall effect ahs been triggered 
- 

ISR (TIMER1_COMPB_vect) {
  Serial.println("Reached 65500"); // used for testing
  TCNT1 = 0;
  counterB ++; 
  Serial.println(counterB);  
} 


ISR (TIMER1_COMPA_vect) {
  Serial.println("Reached 65500"); // used for testing
  TCNT1 = 0;
  counterA ++; 
  Serial.println(counterA);  
} 
