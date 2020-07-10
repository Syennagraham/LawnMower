/*
 * DIP SWITCHES
 * OFF : 1 and 2
 * ON  : 3, 4, 5 and 6
 * 
 * Ramp motor 1 from -2047 to 2047 (full reverse to full forward)
 * 
 * waiting 20 means delay(20)
 * ST.motor(NUMBER CORRESPONDING TO MOTOR, POWER LEVEL)
 */

#include <SoftwareSerial.h>
#include <USBSabertooth.h>
#include <PS2X_lib.h>

SoftwareSerial      SWSerial(NOT_A_PIN, 6);  // RX on no pin (unused), TX on pin 6 (to S1).
USBSabertoothSerial C(SWSerial);             // Use SWSerial as the serial port.
USBSabertooth       ST(C, 128);              // Use address 128.
PS2X ps2x;                                   // create PS2 Controller Class

int error = 0; 
byte type = 0;
byte vibrate = 0;
int saberToothPin = 6;  // Hook S1 of the Sabertooth to 3  
// Hook the PS2 controller to arduino following diagram on github page https://github.com/Syennagraham/LawnMower

void setup()
{
  SWSerial.begin(9600);
  Serial.begin(9600);
  
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
    int power;
    
    // skip loop if no controller found
    if(error == 1)
      return; 
    
    // Controller
    // read controller and set large motor to spin at 'vibrate' speed
    ps2x.read_gamepad(false, vibrate);
    
    // print stick values if either is TRUE
    // IF YOU ARE HOLDING A BUMPER BUTTON, THE REST OF THE ACTIONS WILL FOLLOW
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
    {
      // Right stick, Y axis. Other options: LX, LY, RX  
      Serial.print("PS2 RIGHT Y AXIS VALUE: ");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print("\t");
      
      // Left stick, Y axis. Other options: LX, RY, RX 
      Serial.print("PS2 LEFT Y AXIS VALUE: ");
      Serial.println(ps2x.Analog(PSS_LY), DEC);

      // IF THE RIGHT JOYSTICK BEING PUSHED UP, MOVE M2 FORWARD 
      if(ps2x.Analog(PSS_RY) >= 0 && ps2x.Analog(PSS_RY) <= 126) //real center value is 128, but 140 is needed because controller is HIGHLY sensitive
      {

        // Map the incoming analog value from the joystick to the serial command given to the sabertooth
        // Positve 200 here is used to be the fastest speed forwards
        power = map(ps2x.Analog(PSS_RY),127, 0, 0 , 200);
        Serial.print("FORWARD : ");
        Serial.println(power);
  
        ST.motor(2, power);
  
      }
      //  IF THE RIGHT JOYSTICK BEING PUSHED DOWN, MOVE M2 BACKWARDS
      else if (ps2x.Analog(PSS_RY) >= 128 && ps2x.Analog(PSS_RY) <= 255)
      { 
        // Map the incoming analog value from the joystick to the serial command given to the sabertooth
        // Negative 200 here is used to be the fastest speed backwards
        power = map(ps2x.Analog(PSS_RY),128, 255, 0, -200);
        Serial.print("BACKWARD :");
        Serial.println(power);
        
        ST.motor(2, power);
      }
      else 
      {
        ST.motor(2, 0);
      }

      // IF THE LEFT JOYSTICK BEING PUSHED UP, MOVE M1 FORWARD 
      if(ps2x.Analog(PSS_LY) >= 0 && ps2x.Analog(PSS_LY) <= 126) //real center value is 128, but 140 is needed because controller is HIGHLY sensitive
      {

        // Map the incoming analog value from the joystick to the serial command given to the sabertooth
        // Positve 200 here is used to be the fastest speed forwards
        power = map(ps2x.Analog(PSS_LY),127, 0, 0 , 200);
        Serial.print("FORWARD : ");
        Serial.println(power);
  
        ST.motor(1, power);
  
      }
      //  IF THE LEFT JOYSTICK BEING PUSHED DOWN, MOVE M1 BACKWARDS
      else if (ps2x.Analog(PSS_LY) >= 128 && ps2x.Analog(PSS_LY) <= 255)
      { 
        // Map the incoming analog value from the joystick to the serial command given to the sabertooth
        // Negative 200 here is used to be the fastest speed backwards
        power = map(ps2x.Analog(PSS_LY),128, 255, 0, -200);
        Serial.print("BACKWARD :");
        Serial.println(power);
        
        ST.motor(1, power);
      }
      else 
      {
        ST.motor(1, 0);
      }
    }
    
  delay(50);
}
