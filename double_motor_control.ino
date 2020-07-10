/*
 * DIP SWITCHES
 * OFF : 1 and 2
 * ON  : 3, 4, 5 and 6
 */

#include <SoftwareSerial.h>
#include <USBSabertooth.h>

SoftwareSerial      SWSerial(NOT_A_PIN, 11); // RX on no pin (unused), TX on pin 11 (to S1).
USBSabertoothSerial C(SWSerial);             // Use SWSerial as the serial port.
USBSabertooth       ST(C, 128);              // Use address 128.

void setup()
{
  SWSerial.begin(9600);
}
void loop()
{
  int power;
  
  // Ramp motor 1 from -2047 to 2047 (full reverse to full forward),
  // waiting 20 ms (1/50th of a second) per step.
  // ST.motor(NUMBER CORRESPONDING TO MOTOR, POWER LEVEL)
  
  for (power = -300; power <= 300; power += 16)
  {
    ST.motor(1, power);
    ST.motor(2, power);
    delay(20);
  }
  
  // Now go back the way we came.
  for (power = 300; power >= -300; power -= 16)
  {
    ST.motor(1, power);
    ST.motor(2, power);
    delay(20);
  }
}
