
 volatile byte half_revolutions;
 unsigned int rpm;
 unsigned long timeold;
 
 void setup()
 {
   Serial.begin(9600);
   //Initialize the intterrupt pin (Arduino digital pin 2)
   //interrupt function to detect if magnet has passed the HALL Effect Sensor 
   attachInterrupt(0, magnet_detect, RISING);
   /*
   half_revolutions = 0;
   rpm = 0;
   timeold = 0;
   */
 }
 void loop()//Measure RPM
 {
  /*
   if (half_revolutions >= 20) { 
     rpm = 30*1000/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
     Serial.println(rpm,DEC);
   }
   */
 }

 //This function is called whenever a magnet/interrupt is detected by the arduino
 //Will allow 
 void magnet_detect()
 {
   //half_revolutions++;
   Serial.println("detect");
 }





