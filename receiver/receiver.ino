/* FreqMeasure - Example with serial output
 * http://www.pjrc.com/teensy/td_libs_FreqMeasure.html
 *
 * This example code is in the public domain.
 * 
 * input pin 8
 * 
 * can't use analogwrite on pin 9 or 10
 */
#include <FreqMeasure.h>

#define DEBUG 0

#define BAUD_RATE   (100)  // depricated
#define LOW_FREQ    (1000) // orig 882 but 920 measured from scope
#define HIGH_FREQ   (1500) // orig 1746 but 1950 measured from scope
#define MAX_FREQ    (2000)
#define EXTRA_FREQ  (2500)

#define SPREAD (250)


void setup() {
  Serial.begin(57600);
  FreqMeasure.begin();
  Serial.println("Frequency Measurement");
}

double sum=0;
int count=0;

int data = 0;
int previousData = 0;
int current = 0;
int hystCount = 0;

int bitCount = 8;
byte currentByte = 0;

int hyst = 200; //reasonably good at 200

int message = 0;

float frequency;

void loop() {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 100) {
      frequency = FreqMeasure.countToFrequency(sum / count);
      //Serial.println(frequency);
      sum = 0;
      count = 0;

      if(frequency > (LOW_FREQ - SPREAD) && frequency < (LOW_FREQ + SPREAD))
      {data = 0;}
      else if(frequency > HIGH_FREQ - SPREAD && frequency < HIGH_FREQ + SPREAD)
      {data = -1;}
      else if(frequency > MAX_FREQ - SPREAD && frequency < MAX_FREQ + SPREAD)
      {data = 1;}
      else if(frequency > EXTRA_FREQ - SPREAD && frequency < EXTRA_FREQ + SPREAD)
      {data = -2;}
    }
    if (data != current)
    {
      hystCount++;
      if(hystCount >= hyst)
      {
        current = data;
        hystCount = 0;
//        Serial.print("Hysteresis reached, new value is: ");
//        Serial.println(current);
      }
    }
    if(data == -1 && previousData != -1)
    {
        message = current;
        if(DEBUG){
        Serial.print("Received a bit!!!   Frequency: ");
        Serial.print(frequency);
        Serial.print("   Last Bits:   ");
        Serial.print(data);
        Serial.print(" ");
        Serial.print(previousData);
        Serial.print(" Estimated Message: ");
        Serial.println(message);
        Serial.print(" bitcount: "); Serial.println(bitCount);
        }
        
        if(message == 1)
        {
          currentByte |= (1 << bitCount);  
        }
        bitCount++;
        if(bitCount >= 8)
        {
          if(DEBUG){
            Serial.print("Char received:  ");
            Serial.println(currentByte, BIN);
            }
            if(currentByte != 126) //126 is tilde for newline
            {
              Serial.print((char) currentByte);
            }
            else
            {
              Serial.println();
            }
          
          bitCount = 0;
          currentByte = 0;
        }
        if(message == -2)
        {
          bitCount = 0;
          currentByte = 0;
        }
    }
    previousData = data;
  }
}



