int c;
int recv;
int currBit;
long count;
#define lowFreq 500
#define highFreq 250
#define nextBitFreq 320
#define nextLetterFreq 200

#define messLength 1000000*.2/2

void setup()  
{
  
  pinMode(3, OUTPUT);  
//  pinMode()
  Serial.begin(57600);  
//  modem.begin();
  Serial.println("Start"); 
  recv = 0;  
  sendBit(nextLetterFreq);
//  sendBit(nextBitFreq);
     
}  

void loop() 
{ 
  

  //250 -> 1.6 kHZ
   //500 -> 10000
   // 320 -> 150
  while(Serial.available())
  { //PC to make sure data is received from
      // Serial . println ("Data out");   
       c = Serial.read(); //1byte Lead 
        Serial.print("Got: ");      
        Serial.println(c);      
                sendBit(nextLetterFreq); 
          
          
        for (int i = 0; i < 8; i++ ){
          currBit = bitRead(c, i);
          bitClear(c, i);
          
          if (currBit){
            sendBit( highFreq); 
//            Serial.println("sending 1"); 
            bitWrite(recv, i, 1);
//            sendBit(nextBitFreq);
          
          } else {
            sendBit(lowFreq);
//            Serial.println("sending 0");
            bitWrite(recv, i, 0);
//            sendBit(nextBitFreq);
          
          }
//          Serial.println(bitRead(c, i));
           
          
        }
        sendBit(nextLetterFreq);
//        sendBit(nextBitFreq);
          
//          sendBit(resetFreq);
//          
          Serial.print("Sent: ");
          Serial.println(recv);
          recv = 0;       
 
  } 
}

void sendBit(int freq){
   count = 0;
  while (messLength > (count * freq))
  {
    digitalWrite(3, HIGH);
    delayMicroseconds(freq);
    
    digitalWrite(3, LOW);
    delayMicroseconds(freq);
    count++;
  }
  count = 0;
  while (messLength > (count * nextBitFreq))
  {
    digitalWrite(3, HIGH);
    delayMicroseconds(nextBitFreq);
    
    digitalWrite(3, LOW);
    delayMicroseconds(nextBitFreq);
    count++;
  }
  Serial.print("Sent freq: ");
  Serial.println(freq);
  
}
