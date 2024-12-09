# Using vibrationsensor
Tested adxl345 nok. Shaking tube nok ended up with piezo vibration sensor.

Test using piezo vibrationsensor to trigger relay on.
The sensor has digital output that you can set vibration level with potentiometer.
Also an analog output when shaken.
I used both to control a relay.
For the analogue output i trigger on a count of a difference on the output of the analogue output.
For the digital output set when shaken it has to be on for a certain time.

Not tested yet on my motorbike or car. Tested it on small dc engine running.
If it works it would be a great alternative to detect motor running
and not using the voltage of the alternator.
1st test in car not directly what i want. depends very much on the place where you put the sensor.
You need place where vibration is.
The project is a work in progress. I will update working or not.

# Remarks
Used relay board with esp8266. To my surprise discovered analogue input
measuring range esp8266 0-1V for a bare chip. Only on certain boards like nodemcu esp8266 there is a resistordivider onboard that allows
you to measure voltages 0-3.3V.
