//#include <Time.h>  

char c;
long count;
int freq;
void setup()
  
{
  
  pinMode(3, OUTPUT);  
//  pinMode()
  Serial.begin(57600);  
//  modem.begin();
  Serial.println("Start"); 
    freq = 500; 
}  

void loop() 
{ 
  sendBit(320);
  sendBit(250);
  sendBit(500);
  sendBit(250);
    
}
void sendBit(int freq){
   count = 0;
  while ( 1000000> (count * freq))
  {
    digitalWrite(3, HIGH);
    delayMicroseconds(freq);
    
    digitalWrite(3, LOW);
    delayMicroseconds(freq);
    count++;
  }
  Serial.print("Sent freq: ");
  Serial.println(freq);
  
}
 
