#include <Wire.h> //I2C Arduino Library

#define addr 0x1E //I2C Address for The HMC5883
//#define addr 0x0D
void setup() {
  Serial.begin(115200);
  Wire.begin();

  Wire.beginTransmission(addr); //start talking
  Wire.write(0x09); // Set the Register
  Wire.write(0x1D); // Tell the HMC5883 to Continuously Measure

  //  Wire.write(0x02); // Set the Register
  //  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
}


  int x, y, z; //triple axis data
void loop() {


  //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr);
  Wire.write(0x00); //start with register 3.
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();


  //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    Serial.print("asdf\t");
    x = Wire.read() << 8; //MSB x
    x |= Wire.read(); //LSB x
    z = Wire.read() << 8; //MSB z
    z |= Wire.read(); //LSB z
    y = Wire.read() << 8; //MSB y
    y |= Wire.read(); //LSB y
  }

  // Show Values
  Serial.print("X Value: ");
  Serial.println(x);
  Serial.print("Y Value: ");
  Serial.println(y);
  Serial.print("Z Value: ");
  Serial.println(z);
  Serial.println();

  delay(500);
}
