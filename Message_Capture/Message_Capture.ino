String secretMessage;
int choice = 48;  

void setup() {
  Serial.begin(9600); // enables serial prot, sets data rate to 9600 bps 
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

  Serial.println("message has been saved, please wait while the vault is locking"); 
 
}




void loop() 
{

}
