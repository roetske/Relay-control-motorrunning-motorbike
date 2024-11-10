# Remarks

Supply of power to nano must be connected to 5v not vin.
I had to discover it the hardway when 5V is supplied to Vin this voltage is too low!!!
You must supply 5v to the 5v pin of the nano.

#Extra features
Purpuse is switch relay when motor is running.
An extra pushbutton is provided to switch on or off. Pushbutton mode on / or off after pressing.
If do not want to use the pushbutton change the modeOn  value to true in ino.
The relay is switched when a voltage of 13.8V is reached and pushbutton mode is on.
2 led =>green modeOn = true red relay is on.

