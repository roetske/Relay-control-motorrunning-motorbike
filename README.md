# Relay-control-motorrunning-motorbike - getting power 12v
Switch relay for power 12v when motor running- extra feature fan control cooling with switch. <br />
My bmw r1150rt gets very hot during slow traffic. Finally found original police motor fan and holder :).<br />
The fan is operated with manual switch. Problem was only allow the fan to work when motor is running.<br />
If I used direct 12v from battery , and the manual switch of the fan is left on the battery would drain.<br />
I could take voltage from running lights but did not want to interfere with existing cabling.<br />
Needed also power for extra equipment in the future that need 12v only when motor is running and yes fused correctly.<br />
Made a voltage control detector with esp8266 where I read the voltage from the battery. 14v when motor running -12.5V not running.<br />
Implemented also teachbutton to set triggerpoint for switching relay on and store it in flash when teached.<br />
The unit consist of box.<br />
esp8266 mini.<br />
voltagedivider with zener to opamp for measuring voltage 0-15v reduced to 0-3.3v.<br />
2 relay 1 switched by esp8266 when motor is running -use it for future use extra equipment when i need power<br />
        2nd relay for fan gets only power when relay one is switched and manual switch fan is on <br />
teachbutton for teaching voltagelevel motor running.<br />
led relay one active (motor is running) <br />
power direct from battery with awg 18 fuse 7.5A<br />
# hardware
esp8266mini<br />
buckconverter outputs 5v<br />
opamp to with resistor divider 0-16v to 0-3.3v to analogue input esp8266<br />
diode flywheel across power input (cutoff narsty emk from inductive loads) <br />
-diode in series power<br />
0.5 fuse resettable protect power electronics <br />
red led indicating motorrunning on <br />
2 relay in one module 10a switching power per relay(first i wanted to use automotive relay but too bulky)<br />
input button to teach voltage motorrunning (press 5sec and your trigger on voltage is teached and saved)<br />
wago 221 for connections wireloom in box <br />
box to put it all in<br />
2x 2p male female automotive connector<br />
2x 5.5mm male female powerconnector for switch fan and light fan on<br />
2x battery connector see picture<br />
loomtape to wrap cables<br />
powercable from battery silicone cable 18awg<br />
powercable from battery fuse holder with fuse 7.5A<br />
wrapped all cables with loomtape and powercable extra cable sleeve.
important sprayed print and inside box with contact70 (coats everything with thin plastic layer protection against humidity and corrosion)<br />
# conclusion
See the last remark , turned out keeping it simple. used radio contact output power to switch relay and extra relay for the fan. No electronics needed lol just simple relays in a box.<br />
The other remark with the oilpressuresensor was also a simple but effective way to have 12v running. Turns also on my bike the oil pressure indicator is just an indicator and nothing more. <br />
# Remarks
Cabling stays original and box and cable can be easily removed.<br />
box has 5 short cables with seperate connectors for rapid connection.<br />
power<br />
motor running <br />
fan <br />
switch fan <br />
cable light when fan is on <br />
The switchbox is placed in box where radio was before. => quick acces.<br />
Just made the box now to implement on motorbike. <br />
I will also put a fly diode across fan , cutting off fan can use a serious ripple on powersupply <br />
because of inductive load. This can freeze the esp8266 (uses the same powersupply).  <br />
Implemented for this reason also wathchdog in code to restart automatically esp when this happens.<br />
Will give update how reliable it works in the future.<br />
Update <br />
adjusted switch time on from 10 to 3 sec.(org 10 sec) too long.<br />
added light fan on (parallel with cable on output relay2).<br />
# Alternative with nano
Played around with lm358 standalone but had to use potentiometers for trigger and switch interval. (difference off and on hyst = 1v) did not find it good. <br />
A better alternative was with arduino nano clone simple and good. Also board does the detecting and than switches coil for your outside relay 12v. :)<br />
Standalone without controller was 20 years ago the best way to go, but now esp8266 or nano cost is minimal and gives you more options for better control. <br />
you can program your hysteresis and timeon and off delay like you want.<br />

# Alternative with piezo vibration sensor
Would be great alternative instead of measuring alternator voltage.<br />
Tested it vibration is the thing to trigger but depends very much on the vibration + where you place your circuit with vibrationsensor.<br />

# Alternative with tiltsensor or gyro which measures angles of motor
Played around with this idea when motor is tilted(=on side stand relay off) but also have centerstand. <br />
Abandoned this idea very rapidly.<br />

# Alternative Using the oilpressure sensor 
Normally you can use the wire that control the lights to switch relay for bike running but lights are  directly on when contact is on and motor is not running yet.<br />
Found that you can use the oilpressureswitch is nc switch.<br />
On my motorbike oilpressure switch just controls indicator light oilpressure (the light is on contact on-- then when motor is running light is off)<br />
The oilpressureswitch goes open when motor is running.<br />
You can make simple circuit with transistor , resistor and bypass diode that switches relay when oilpressureswitch goes to open.<br />
Fusing is important !! Added switch to turn it off and indicatorlamp relay is on.<br />
See schematic.<br />
Control box transistor circuit and relay 12v <br />
Input gnd and 12v from battery fused.<br />
Input wire from oilpressureswitch(you just add extra wire on oil pressureswitch to controlbox)<br />
Just brainstorming you could also use vacuum sensor that is also a valid and stable indicator motorrunning <br />

# alternative using powersocket radio

monitoring the voltage was not stable when idling . was erronous on off relay on off.<br />
Wanted to to intervene as little in the existing caling and circuits. I eliminated the radio cassette(yes motorbike is old) longtime ago.<br />
Got myself a haynes book on my motorbike. I could use the powersocket cable of the radio aha.<br />
Has power 15A and contact on wire. Used this to power contact on relay in box.<br />
For the fan i used a second relay wich only get power whenfirst relay is on. This relay is activated with switch on dashboard. <br />
The first relay is relay with 3 fuse on it for 3 circuits. <br />
3 circuit 3A 5A 7.5A.  <br />
3A for dashcam  <br />
5A for fan that goes to 2nd relay when switch fan on is on. <br />
7.5A for 12v socket. <br /> <br />
I put also a red led behind each circuit (lit when power after fuse). The advantage is you do not have to open the box , to check is blown.<br />
Advantages are. Main power to box is already fused and each circuit in powerbox is fused also.
Also on the box switch with led that cuts the contact on wire. so you can  poweroff everthing in extra circuit.
Keep it simple that must be the motto :) <br />

