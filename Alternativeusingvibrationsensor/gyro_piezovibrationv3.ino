
/***************************************************************************
nodemcu 1.0 12e
relayboard with esp8266 no serial connection with serial programmer
push reset en io00 to ground and release
piezo vibrationsensor has one an out en digital output sensitivity with potentiometer

set relay either on digital input or analogue trigger

scan every seconds 
3 counts high on
3 counts low off
reset counters after 5s to eliminate random vibrations

work with analogue input and count vibration variation to trigger on

voltage range adc is 0-1v not 0-3.3v depends on your board with volge divider or not
no vibration 0.3v
calculated first voltage but voltagechange is too little =>worked with difference vibration and on pure input 0-1023

***************************************************************************/
#include <elapsedMillis.h>

#define i_shaking 12
#define analogPin A0 // ESP8266 Analog Pin ADC0 = A0 
#define relay 5

//var
elapsedMillis scan;
elapsedMillis scan_analogue;
float scanintervalanalogue = 10;//ms
float scaninterval = 1000; //ms
elapsedMillis cycletime;
int lastcycletime =0;
int adcvalue =0;
int lastadcvalue =0;
float calcVoltage =0;
int counterhigh =0;
int counterlow=0;
int triggerdig =3;//trigger vibration on digital output
int countervibrhigh =0;
int countervibrlow =0;
int countersafety =0;//reset countervibhigh analogue when limit is not reached
int countersafetymax=5; //nr scans to reset countervibrhigh when count is not reached
int triggervibr =100; //triggercount vibration from analogue input
bool bmotoron = false;
bool bdigmotoron = false;
bool banmotoron = false;
String version ="version 3";


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println(version);
  pinMode(i_shaking,INPUT);
  pinMode(relay,OUTPUT);

  //init
  digitalWrite(relay,LOW);
  adcvalue = analogRead(analogPin);
  lastadcvalue = adcvalue;
}
//*************************************************
void loop() 
{  
  if (scan > scaninterval)
      {  
         if (digitalRead(i_shaking))
           {
            counterlow =0;
            counterhigh++;
            if (counterhigh > triggerdig)
            {
              bdigmotoron = true;
              counterhigh = 0;
            }
           }
        else 
          {
            counterlow++;
            if (counterlow > triggerdig)
             { 
               bdigmotoron = false;
               counterlow=0;
               counterhigh =0;
             }
          }
      //via analogue input
      if (countervibrhigh > triggervibr)
       {
         Serial.println("Vibration");
         countervibrhigh=0;
         countervibrlow=0;
        banmotoron =true;
       }

      if (countervibrlow > triggervibr) 
       {
        Serial.println("No vibration");
        banmotoron = false;
        countervibrlow=0;
        countervibrhigh=0;
       }
      //eliminate random triggers
      //reset count analogue after x cylces when limit to trigger is not reached
      if (countersafety> countersafetymax)
        {if (countervibrhigh < triggervibr)
          {
            Serial.println("reset counters");
            countervibrhigh=0;
            countersafety =0;
          }
        }
      countersafety++;
      
      //debug
      Serial.print("counterhigh=");
      Serial.println(counterhigh);
      Serial.print("counterlow=");
      Serial.println(counterlow);
      Serial.print("countervibrhigh=");
      Serial.println(countervibrhigh);
      Serial.print("countervibrlow=");
      Serial.println(countervibrlow);
      //relay control
      bmotoron = banmotoron or bdigmotoron;
      digitalWrite(relay,bmotoron);
      
      scan =0;  
     }  

  if (scan_analogue >scanintervalanalogue)
   {  //get analogue reading
      adcvalue = analogRead(analogPin);
      int dif = abs(adcvalue-lastadcvalue);
      if (dif>5 || (adcvalue >= 500)) //diff and maxvibration 
       {
        countervibrhigh++;
        //prevent going low when random lows
        if (countervibrhigh > 10)
         {countervibrlow = 0;}
       }
      else 
        {
          countervibrlow++;
        }
      
      lastadcvalue = adcvalue;
      scan_analogue=0;
   } 
  //debug
  lastcycletime = cycletime;
  cycletime =0 ;

 if (lastcycletime > 100)
  {
   Serial.print("Cycletime=");
   Serial.println(lastcycletime);
  }
  
}
//********************************************
