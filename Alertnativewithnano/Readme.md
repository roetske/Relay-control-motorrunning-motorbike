# Remarks
Supply of power to nano must be connected to 5v not vin.
I had to discover it the hard way when 5V is supplied to Vin this voltage is too low!!!
You must supply 5v to the 5v pin of the nano.

# Purpose
Purpuse is switch relay when motor is running. 
13.8v and higher on.
13v switch off after 3s.
emergency switchoff when battery is 12.5v.

The box is provided with the the power from the battery and relays output to 2nd connector when motor is running.
# Connections
1) power in
2) power out
3) pushbutton on/off (press once on , press again off)
4) led green box is active
5) red led relay is on motor running

The pushbutton allows you to activate box or not. Its a pushbutton press once =>on(green led on)
press again => box is off (green led is off)
If the green led is on (box active) then if the voltage is high enough the relay will be switched to on ,
to supply the outgoing connector with 12v.

In the program there is an on and off delay of 3seconds for switching the relay on or off.
The pushbutton is also protected anti bounce of 3sec. The pushbutton is now on the box but you can extend it
to whatever place you want.

