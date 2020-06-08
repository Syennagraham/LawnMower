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
  }
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug.");
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug.");
}

void loop()
{
    // skip loop if no controller found
    if(error == 1)
      return; 
    
    // Controller
    // read controller and set large motor to spin at 'vibrate' speed
    ps2x.read_gamepad(false, vibrate);
    
    // print stick values if either is TRUE
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
    {
      // Right stick, Y axis. Other options: LX, RY, RX  
      Serial.print("JoyStick Value:");
      Serial.println(ps2x.Analog(PSS_RY), DEC);

      if(ps2x.Analog(PSS_RY) >= 127 && ps2x.Analog(PSS_RY) <= 255) //real center value is 128, but 140 is needed because controller is HIGHLY sensitive
      {
        int initialSpeed = 128;
        initialSpeed = map(ps2x.Analog(PSS_RY),127 , 255, 0 , 255);
        /*
        Syntax  
                  map(value, fromLow, fromHigh, toLow, toHigh)
        Parameters
                  value: the number to map.
                  fromLow: the lower bound of the value’s current range.
                  fromHigh: the upper bound of the value’s current range.
                  toLow: the lower bound of the value’s target range.
                  toHigh: the upper bound of the value’s target range.
        */
        analogWrite(saberToothPin, initialSpeed);
      }
      else
      { 
        // Map 0 to 255 as well, so you can move the joystick up to move the mower instead of down.
        int motorSpeed = map(ps2x.Analog(PSS_RY),0 , 255, 255 , 0);
        //analogWrite(saberToothPin, ps2x.Analog(PSS_RY));  
        analogWrite(saberToothPin, motorSpeed);  
      }
      
    }
    
  delay(50);
}
