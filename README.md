# AutoVoltmeter

Psoc 4 CY8CKit-049 4200 usb break-off bootloader chip

Trying to make a 2 channel voltmeter fro my car:

1 reads the battery
2 reads the alternator

3 external temperature sensor
4 internal temperature sensor

ADC muxed 10 bit input

Oled SSD1306 display cycles through the battery with
   B: xx.x
   A: xx.x
   
 temperature
   O: xx.x
   I: xx.x
   
 Where B is battery, A is alternator, O is outside, I is inside temperature.
 
 the ADC reads the B and A channels.  The O and I channels are currently not in use because when the thermistor calculator is in the project, the display only cycles a few times and goes off.
 
 the ADC -> uint32 -> volts -> scaled to input volts -> string for oled viewing is problematic.  What happened to ftoa()?
