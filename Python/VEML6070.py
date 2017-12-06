# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# VEML6070
# This code is designed to work with the VEML6070_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# VEML6070 address 0x38(56)
# Select command register
# 0x02(02)      Integration time = 0.5T, Shutdown mode disabled
bus.write_byte(0x38, 0x02)

time.sleep(0.5)

# VEML6070 address 0x38(56)
# Read data back, 2 bytes
# uvlight msb, uvlight lsb
bus.write_byte(0x38, 0x73)
data0 = bus.read_byte(0x38)
bus.write_byte(0x38, 0x71)
data1 = bus.read_byte(0x38)

# Convert the data
uvlight = data0 * 256 + data1

# Output data to screen
print "UV Light of The Device : %d" %uvlight
