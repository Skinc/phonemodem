int c;
int recv;
int currBit;
long count;
//predefined freqs for 0bit, 1bit, nextbit, nextByte
#define lowBit 500
#define highBit 250
#define nextBit 320
#define nextLetter 200

//length of the messages. replace the middle number with the amount of time in secs per letter
#define messLength 1000000*.2/2

void setup()  
{
  
  pinMode(3, OUTPUT);  
  Serial.begin(57600);  
  Serial.println("Start"); 
  recv = 0;  
  //send the start bit
  sendBit(nextLetter);     
}  

void loop() 
{ 
  while(Serial.available())
  { 
        c = Serial.read(); //1byte Lead 
        Serial.print("Got: ");      
        Serial.println(c);   
        // send the prepare to read bit   
        sendBit(nextLetter); 
          
          
        //for each bit in letter, send bit then send nextBit. 
        for (int i = 0; i < 8; i++ ){
          // read the bit
          currBit = bitRead(c, i);
          bitClear(c, i);
          
          if (currBit){
            sendBit( highBit); 
            bitWrite(recv, i, 1);
          
          } else {
            sendBit(lowBit);
            bitWrite(recv, i, 0);
          }
           
          
        }
        // send nextLetter to save we finished the letter
        sendBit(nextLetter);
          Serial.print("Sent: ");
          Serial.println(recv);
          recv = 0;       
 
  } 
}

void sendBit(int freq){
   count = 0;
   //send bit 
   //while counts how many times we've gone through the squarewave. That times the period gets us the message length
   //messagelength is how long we're sending the message for. 
  while (messLength > (count * freq))
  {
    digitalWrite(3, HIGH);
    delayMicroseconds(freq);
    
    digitalWrite(3, LOW);
    delayMicroseconds(freq);
    count++;
  }
  count = 0;
  
  //send the nextBit freq to say we finished that bit
  while (messLength > (count * nextBit))
  {
    digitalWrite(3, HIGH);
    delayMicroseconds(nextBit);
    
    digitalWrite(3, LOW);
    delayMicroseconds(nextBit);
    count++;
  }
  Serial.print("Sent freq: ");
  Serial.println(freq);
  
}
