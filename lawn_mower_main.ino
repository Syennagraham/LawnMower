#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class

int error = 0; 
byte type = 0;
byte vibrate = 0;
int saberToothPin = 3;  // Hook S1 of the Sabertooth to 3  
// Hook the PS2 controller to arduino following diagram on github page https://github.com/Syennagraham/LawnMower

void setup()
{
  Serial.begin(9600);
  
  pinMode(saberToothPin, OUTPUT);
  
  error = ps2x.config_gamepad(13,11,10,12, true, true); // setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  
  if(error == 0)
  {
    Serial.println("Found Controller, configured successful");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
  }
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug.");
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug.");
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
}

void loop()
{
    // skip loop if no controller found
    if(error == 1)
      return; 
    
    // Controller
    // read controller and set large motor to spin at 'vibrate' speed
    ps2x.read_gamepad(false, vibrate);
    
    
    // this will set the large motor vibrate speed based on how hard you press the blue (X) button
    vibrate = ps2x.Analog(PSAB_BLUE);
    
    // print stick values if either is TRUE
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
    {
      Serial.print("JoyStick Value:");
      Serial.println(ps2x.Analog(PSS_RY), DEC);
      
      // Right stick, Y axis. Other options: LX, RY, RX  
      // Currently up is stop and down is faster, right in the middle is slow
      // Need to switch joystick directions
      
      int PS2direction = ps2x.Analog(PSS_RY); 
      analogWrite(saberToothPin, PS2direction);
      
    }
  //}
  delay(50);
}
