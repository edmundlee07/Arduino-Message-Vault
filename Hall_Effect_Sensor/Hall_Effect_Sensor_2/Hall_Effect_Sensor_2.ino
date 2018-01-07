
 void setup()
 {
   Serial.begin(9600);
   
   //Initialize the intterrupt pin (Arduino digital pin 2)
   //interrupt function to detect if magnet has passed the HALL Effect Sensor 
   attachInterrupt(digitalPinToInterrupt(2), magnet_detect, RISING);
 }
 
 void loop()
 {
  
 }

 //This function is called whenever a magnet/interrupt is detected by the arduino
 //Will allow 
 void magnet_detect()
 {
   Serial.println("magnetic field detected");
 }





