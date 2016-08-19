# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# VEML6070
# This code is designed to work with the VEML6070_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# VEML6070 address 0x38(56)
# Select command register
#		0x02(02)	Integration time = 0.5T, Shutdown mode disabled
data = [0x02]
i2c.write(0x38, data)

time.sleep(0.5)

# VEML6070 address 0x38(56)
# Read data back, 2 bytes
# uvlight msb, uvlight lsb
data0 = i2c.readBytes(0x38, 0x73, 1)
data1 = i2c.readBytes(0x38, 0x71, 1)

# Convert the data
uvlight = data0[0] * 256 + data1[0]

# Output data to screen
print "UV Light of The Device : %d" %uvlight