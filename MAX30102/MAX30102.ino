/*
  MAX30105 Breakout: Output all the raw Red/IR/Green readings
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  Outputs all Red/IR/Green values.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

#define debug Serial //Uncomment this line if you're using an Uno or ESP
//#define debug SerialUSB //Uncomment this line if you're using a SAMD21

long red, ir, green;
long prev_red, prev_ir, prev_green;
float gain = 1;

void setup()
{
  debug.begin(115200);
  debug.println("MAX30105 Basic Readings Example");

  // Initialize sensor
  if (particleSensor.begin() == false)
  {
    debug.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive
}


void loop()
{
  red = particleSensor.getRed();
  ir = particleSensor.getIR();
  green = particleSensor.getGreen();

  red = (gain * red) + ((1 - gain) * prev_red);
  ir = (gain * ir) + ((1 - gain) * prev_ir);
  green = (gain * green) + ((1 - gain) * prev_green);

  prev_red = red;
  prev_ir = ir;
  prev_green = green;

  debug.print(ir);
  debug.print("\t");

  debug.print(red);
  debug.print("\t");
  
//  debug.print(green);
  debug.println();
}
