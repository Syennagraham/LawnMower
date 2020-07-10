# RC Lawn Mower 
Instructions to create a PS2/Microcontroller controlled lawn mower.

## 1.  Connect PS2 to Arduino

### Connect the PS2 Wireless Transmitter to the Arduino
![PS2 Transmitter Wiring Diagram](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/transmitter_wiring.png)

![Arduino Wiring Diagram](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/arduino_wiring.png)

## 2.  Upload the Arduino Code
1. Go to the Arduino Software
2. Upload PS2 library available above.
3. Connect your Arduino UNO to your laptop.
4. Make sure the serial monitor baud is set to 9600.
5. Upload **[lawn_mower_main.ino](https://github.com/Syennagraham/LawnMower/blob/master/lawn_mower_main.ino "lawn_mower_main.ino")** code to the sketch book and upload this code to the Arduino.
6. Monitor the serial monitor for output. 


## 3. Hook up the Sabertooth Motor Controller

![Sabertooth Motor Controller](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/sabertooth_plain.png)

### Dip Switches
![Dip Switches](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/dip_switches.jpg)


#### Sources
https://surtrtech.com/2018/11/29/interfacing-wireless-ps2-controller-with-arduino/
