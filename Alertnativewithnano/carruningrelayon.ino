/*
running motor check 14v on battery voltage
board arduino nano
12.8v off -13.8v on
delay 3 sec on
delay 5 sec off
battery 12V emergency off

12v 425
12.8v 453
13v 459 =>459-425 =34
13.8v 482
*/

#include <elapsedMillis.h>


#define analogInPin A0
#define relay 12

//var
int readvoltage = 0;  // value read from the pot
float voltage = 0;
float offset =0.15;
elapsedMillis scan;
int scaninterval = 1000;
elapsedMillis scanled;
int scanledinterval = 500;

int trigrelayon =482;
int trigrelayoff = 453;
int triglowbattery = 425;
int countlow =0;
int maxcountlow = 5;
int counthigh =0;
int maxcounthigh =3;

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  //internal blinkled show when working
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() 
{
if (scan > scaninterval)
  { 
    // read the analog in value
    readvoltage = analogRead(analogInPin);
    // print the readings in the Serial Monitor
    Serial.print("sensor = ");
    Serial.println(readvoltage);
    //procesrelayoff
    if ( readvoltage <= trigrelayoff)
    {  countlow +=1;
       Serial.print("countlow=");
       Serial.println(countlow);
       if (countlow >= maxcountlow)
        {
         digitalWrite(relay,LOW);
         countlow = 0;
         counthigh =0;
        }
    }
    if ( readvoltage >= trigrelayon)
    { counthigh +=1;
      if (counthigh >= maxcounthigh)
        {
         counthigh =maxcounthigh;
         digitalWrite(relay,HIGH);
        }

      countlow = 0;
    }
    //emergency low battery off
    if ( readvoltage <= triglowbattery)
    {  counthigh=0;
       digitalWrite(relay,LOW);  
    }
     
    scan=0;
  }
  if (scanled > scanledinterval)
   {
      if (digitalRead(relay))
       { //showoutput
         if (digitalRead(LED_BUILTIN))
           {digitalWrite(LED_BUILTIN,LOW);}
         else
          {digitalWrite(LED_BUILTIN,HIGH);}
       }   
      scanled =0;
    }
 
}


