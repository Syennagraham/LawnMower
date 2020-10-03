# RC Lawn Mower 
Instructions to create a PS2/Microcontroller controlled lawn mower.


## Electronics 
### 1.  Connect PS2 to Arduino

#### Connect the PS2 Wireless Transmitter to the Arduino
![PS2 Transmitter Wiring Diagram](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/transmitter_wiring.png)

![Arduino Wiring Diagram](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/arduino_wiring.png)

### 2.  Upload the Arduino Code
1. Go to the Arduino Software
2. Upload PS2 library available above.
3. Connect your Arduino UNO to your laptop.
4. Make sure the serial monitor baud is set to 9600.
5. Upload **[lawn_mower_main.ino](https://github.com/Syennagraham/LawnMower/blob/master/lawn_mower_main.ino "lawn_mower_main.ino")** code to the sketch book and upload this code to the Arduino.
6. Monitor the serial monitor for output. 


### 3. Hook up the Sabertooth Motor Controller

![Sabertooth Motor Controller](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/sabertooth_plain.png)

#### Dip Switches
![Dip Switches](https://github.com/Syennagraham/LawnMower/blob/master/diagrams/dip_switches.jpg)


## Structure

More to come.
#### Physical structure consists of:
    REEL Lawn mower
      - The blades and wheels of the mower
    4 bike gears and 2 bike chains (taken from child's size bike)
      - Connected to motor to turn the wheel
    1 drill battery
      - Provides power. Battery is connected to motor controller with trigger from drill
    4 osyter clamps 
      - Holds drill batteries to wood board
    Sabertooth motor controller
      - Controls the amount of power input to the motor. Uses serial communication with motors. 
    2 large gears
      - Welded with JD Weld to the tires. Larger bike gears are attached to this gear.
    2 drill motors
      - With input from the arduino, these drills motors turn the wheels. Taken from two cheap (goodwill/yardsale) drills. 
    Arduino 
      - Used to turn analog signal from PS2 controller into serial signals to send to motorcontroller
    Wood Board
      - Used as frame on top of blades to hold electronics
    2 T Frame metal structure pieces
      - Used to hold wood board to REEL mower frame
    PS2 controller
      - Sends signal of which direction via analog to the Ardiuno. 
  


##### Sources
https://surtrtech.com/2018/11/29/interfacing-wireless-ps2-controller-with-arduino/
