// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// VEML6070
// This code is designed to work with the VEML6070_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// VEML6070 I2C address is 0x38(56)
#define Addr 0x38

float uvlight = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "VEML6070");
  Particle.variable("uvlight", uvlight);
  
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select command register
  // Integration time = 0.5T, shutdown mode disable 
  Wire.write(0x02);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop() 
{
  unsigned int data[2];
 
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data msb register
  Wire.write(0x73);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  if(Wire.available() == 1)
  {
    data[0] = Wire.read();
  }
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data lsb register
  Wire.write(0x71);
  // Stop I2C Transmission
  Wire.endTransmission();
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  if(Wire.available() == 1)
  {
    data[1] = Wire.read();
  }

  // Convert the data
  float uvlight = data[0] * 256.0 + data[1];
  
  // Output data to dashboard
  Particle.publish("UV Light of The Device : ", String(uvlight));
  delay(1000);     
}
