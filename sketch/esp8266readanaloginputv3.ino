/*
voor motorfiets
1.87= 11v  526
2 =  12v   666
2.12 =13v  708
2.22 =14   735
2.30 =15   760
2.38 =16   784
esp8266 generic device
hmm voltage difference is critical
loaded battery can be 
12.6 v
charging 14v
difference is 1.4v that is little to work with hysteresis 
which you must have otherwise you can have a rattling relay
10sec try high then high
5sec low then low
emergency low bat off =>here extra time? reset beeper
teachpin 5 sec push then calibration on
add store teached value in flash
*/
#include <elapsedMillis.h>
#include <EEPROM.h>

#define DEFAULT_VALUE 0 // Define the default value
#define EEPROM_SIZE 4  //size for one int
#define outputpin 13
#define teachpin 5
#define analogInPin 0

String version ="version3";
int readvoltage = 0;  // value read from the pot
float voltage = 0;
float offset =0.15;
elapsedMillis scan;
elapsedMillis teachpinscan;
int trigscan =5000;
int trigrelayon =710;
int trigrelayoff = trigrelayon-50;//50 1volt
int triglowbattery = trigrelayon-150;//-3V
int countlow =0;
int maxcountlow = 5;
int counthigh =0;
int maxcounthigh =10;
//teachpin check
bool bcurrswitch = false;
bool blastswitch = false;
bool bCheckingSwitch = false;
//eeprom
int address = 0; // Starting address
int readValue;
void setup() 
{
  // initialize serial communication at 115200
  Serial.begin(115200);
  Serial.print("Version=");
  Serial.println(version);
  
  pinMode(outputpin, OUTPUT); 
  pinMode(teachpin, INPUT);
  digitalWrite(outputpin,LOW);
  //get flash value
  // Read the integer value from EEPROM
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(address, readValue); 
  delay(500);
  //check initialised
  if (readValue==DEFAULT_VALUE)
     {Serial.println("Oeps not calibrated");
     //uses standard value trigrelayon set above
     }
  else
     {Serial.print("readValue from flash=");
      Serial.println(readValue);
      trigrelayon= readValue;
     }
  delay(1000);
 // Initialize the watchdog timer
    ESP.wdtEnable(2000); // Enable watchdog timer with a 2-second timeout
}

void loop() {

  if (scan > 1000)
  { // Reset the watchdog timer
    ESP.wdtFeed(); // Feed the watchdog to prevent reset
    // read the analog in value
    readvoltage = analogRead(analogInPin);
    // print the readings in the Serial Monitor
    Serial.println("******");
    Serial.print("trigOn= ");
    Serial.println(trigrelayon);
    Serial.print("trigOff= ");
    Serial.println(trigrelayoff);
    Serial.print("sensor = ");
    Serial.println(readvoltage);
    Serial.println("******");
    //procesrelayoff
    if ( readvoltage <= trigrelayoff)
    {  countlow +=1;
       Serial.print("countlow=");
       Serial.println(countlow);
       if (countlow >= maxcountlow)
        {
         Serial.println("RelayOff");
         digitalWrite(outputpin,LOW);
         countlow = 0;
         counthigh =0;
        }
    }
    if ( readvoltage >= trigrelayon)
    { counthigh +=1;
      if (counthigh >= maxcounthigh)
        {
         counthigh =maxcounthigh;
         Serial.println("RelayOn");
         digitalWrite(outputpin,HIGH);
        }
      countlow = 0;
    }
    //emergency low battery off
    if ( readvoltage <= triglowbattery)
    {  counthigh=0;
       digitalWrite(outputpin,LOW);
       Serial.println("EmergencyRelayOff");
    }
    checkteachpin();
      
    scan=0;
  }
  delay(10);
}

void checkteachpin()
//read the switch (for simplicity, no debouncing done)
{    bcurrswitch = digitalRead( teachpin );
    //if the switch is low now and doesn't match its
    //previous reading, it means the switch has changed
    //either unpressed-to-pressed or pressed-to-unpressed
    if( bcurrswitch != blastswitch )
    {
        //if high, the change was unpressed to pressed
        if( bcurrswitch)
        {
            //in that case, get the time now to start the
            //5-sec delay...
            teachpinscan = 0;
            bCheckingSwitch = true;
            
        }//if
        else
        {
            //geen input
            bCheckingSwitch = false;
            
        }//else
        
        //and save the 
        blastswitch = bcurrswitch;
        
    }
  if( bCheckingSwitch )
    {
        //if the millis count now is 5000 or more higher
        //than it was when the press was detected (timeStart),
        //perform action
        if( teachpinscan >trigscan)
            {  
              trigrelayon = readvoltage;
              Serial.print("Adjustingtriggeron =");
              Serial.println(trigrelayon);
              //write new trigger to flash
              EEPROM.put(address, trigrelayon); // Store the integer
              EEPROM.commit(); // Commit the changes to EEPROM
             //no continuous writing otherwise you destroy flash
              bCheckingSwitch = false;
            }
    }       
}

// //test output
    // if (digitalRead(outputpin))
    //   {digitalWrite(outputpin,LOW);}
    // else
    //   {digitalWrite(outputpin,HIGH);}