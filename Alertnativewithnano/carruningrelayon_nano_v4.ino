/*
running motor check 14v on battery voltage
board arduino nano
13v off -13.8v on
delay 3 sec on
delay 5 sec off
battery 12V emergency off
pushbutton  on/off relay control 
             pushbutton select on and voltage measurement must be met to allow on
led active
led motor running
nano board

remark to remember
supply from buckconverter 5v connect to 5v of nano not to vin
when connected to vin the 5v is too low for the nano!!! when you measure your 5v  pin you will only have 3.8v or less
so connect 5v powersupply to the 5v connection and not vin!!!!
*/

#include <elapsedMillis.h>
#define analogInPin A0
#define relay 12
#define buttonPin 10
#define ledredmotorrunning 9
#define ledgreenactive 8
//var
int readvoltage = 0;  // value read from the pot
float voltage = 0;
float offset =0.15;
elapsedMillis scan;
int scaninterval = 1000;
elapsedMillis scanled;
int scanledinterval = 500;

int trigrelayon =448;
int trigrelayoff = trigrelayon-22;
int triglowbattery = 405;
int countlow =0;
int maxcountlow = 5;
int counthigh =0;
int maxcounthigh =5;
//pushbutton
bool lastButtonState = HIGH;  // Previous state of the button
bool buttonState;
bool modeOn =false;
elapsedMillis scanbutton;
int debounceDelay =2000;
//version management
String version ="version4";

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  //config io
  pinMode(buttonPin,INPUT);
  pinMode(relay,OUTPUT);
  pinMode(ledgreenactive,OUTPUT);
  pinMode(ledredmotorrunning,OUTPUT);
  
  //init outputs
  digitalWrite(ledredmotorrunning, LOW);
  digitalWrite(ledgreenactive,LOW);
  digitalWrite(relay,LOW);

  //internal blinkled show when working
  pinMode(LED_BUILTIN, OUTPUT);

   Serial.print("version = ");
   Serial.println(version);
}
void loop() 
{

checkPushButton();
if (scan > scaninterval)
  { 
    // read the analog in value
    readvoltage = analogRead(analogInPin);
    // print the readings in the Serial Monitor
    Serial.print("sensor = ");
    Serial.println(readvoltage);
    Serial.print("off/on=");
    Serial.print(trigrelayoff);
    Serial.print("/");
    Serial.println(trigrelayon);
    //procesrelayoff
    if ( readvoltage <= trigrelayoff)
      { countlow +=1;
        counthigh =0;
        Serial.print("countlow=");
        Serial.println(countlow);
        if (countlow >= maxcountlow)
        {
         digitalWrite(relay,LOW);
         digitalWrite(ledredmotorrunning,LOW);
         countlow = 0; 
        }
      }
    
    if ( readvoltage >= trigrelayon)
      { counthigh +=1;
        Serial.print("counthigh=");
        Serial.println(counthigh);
      }
    if (counthigh >= maxcounthigh)
      {
        counthigh =maxcounthigh;
        if (modeOn)
        {
          digitalWrite(relay,HIGH);
          digitalWrite(ledredmotorrunning,HIGH);
        }
        else 
        {
          digitalWrite(relay,LOW);
          digitalWrite(ledredmotorrunning,LOW);
        }
      }
    //emergency low battery off
    if ( readvoltage <= triglowbattery)
    {  counthigh=0;
       countlow=0;
       digitalWrite(relay,LOW);  
    }
    //check button off
    if (!modeOn)
      { 
        counthigh = 0;
        countlow= 0;
        digitalWrite(relay,LOW);
        digitalWrite(ledredmotorrunning,LOW);
      }
    scan=0;
  }
  
  //led to view switched on blinking on nano
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

void checkPushButton() {
  if (scanbutton >= debounceDelay) {
    bool reading = digitalRead(buttonPin);
    
    if (reading != lastButtonState) 
    {
      scanbutton = 0;  // Reset the timer
      if (reading != buttonState) 
      {
        buttonState = reading;
        if (buttonState == LOW)// Button is pressed
         {  
            modeOn = !modeOn;  // Toggle the mode
            digitalWrite(ledgreenactive,modeOn);
            Serial.println("--------");
            Serial.print("modeOn = ");
            Serial.println(modeOn);
            Serial.println("--------");
         }
      }
    }
    
    lastButtonState = reading;
    
  }
}

