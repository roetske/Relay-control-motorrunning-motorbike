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
opamp for measuring voltage 0-15v reduced to 0-3.3v.<br />
2 relay 1 switched by esp8266 when motor is running -use it for future use extra equipment when i need power<br />
        2nd relay for fan gets only power when relay one is switched and manual switch fan is on <br />
teachbutton for teaching voltagelevel motor running.<br />
led relay one active (motor is running) <br />
power direct from battery with awg 18 fuse 7.5A<br />
# Remarks
Cabling stays original and box and cable can be easily removed.<br />
box has 4 short cables with seperate connectors for rapid connection.<br />
power<br />
motor running <br />
fan <br />
switch fan <br />
The switchbox is placed in box where radio was before. => quick acces.<br />
Just made the box now to implement on motorbike. I will also put a fly diode across fan , cutting off fan can use a serious ripple on powersupply <br />
because of inductive load. This can freeze the esp8266 (uses the same powersupply).  <br />
Implemented for this reason also wathchdog in code to restart automatically esp when this happens.<br />
Will give update how reliable it works in the future.<br />

