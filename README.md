# Use multiple MPU9250 using
- Arduino IDE
- SparkFun SAMD21 Dev Breakout
- MPU9250
- SPI communication
- ROS

# SPI communication circuit
- https://raduino.tistory.com/11

# Arduino zero sync problem
- https://github.com/ROBOTIS-GIT/OpenCR/blob/master/arduino/opencr_arduino/opencr/libraries/turtlebot3_ros_lib/ArduinoHardware.h
- Add '#define USE_USBCON' above '#include <ros.h>'
