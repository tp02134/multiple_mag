/*
Basic_SPI.ino
Brian R Taylor
brian.taylor@bolderflight.com

Copyright (c) 2017 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define USE_USBCON //error solution

#include "MPU9250.h"
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/MagneticField.h>
#include <std_msgs/String.h>

sensor_msgs::MagneticField mag_msg1;
sensor_msgs::MagneticField mag_msg2;
sensor_msgs::MagneticField mag_msg3;
sensor_msgs::MagneticField mag_msg4;

ros::NodeHandle nh;
ros::Publisher pub_mag1("mag1", &mag_msg1);
ros::Publisher pub_mag2("mag2", &mag_msg2);
ros::Publisher pub_mag3("mag3", &mag_msg3);
ros::Publisher pub_mag4("mag4", &mag_msg4);


// an MPU9250 object with the MPU-9250 sensor on SPI bus 0 and chip select pin 10
MPU9250 IMU1(SPI,9);
MPU9250 IMU2(SPI,10);
MPU9250 IMU3(SPI,11);
MPU9250 IMU4(SPI,12);

int status1;
int status2;
int status3;
int status4;

void setup() {
  // start communication with IMU 
  status1 = IMU1.begin();
  status2 = IMU2.begin();
  status3 = IMU3.begin();
  status4 = IMU4.begin();

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(pub_mag1);
  nh.advertise(pub_mag2);
  nh.advertise(pub_mag3);
  nh.advertise(pub_mag4);
  
}

void loop() {
  // read the sensor
  IMU1.readSensor();
  IMU2.readSensor();
  IMU3.readSensor();
  IMU4.readSensor();
  
  // display the data
  mag_msg1.header.stamp = nh.now();
  mag_msg1.header.frame_id = "/world";
  mag_msg1.magnetic_field.x = IMU1.getMagX_uT();
  mag_msg1.magnetic_field.y = IMU1.getMagY_uT();
  mag_msg1.magnetic_field.z = IMU1.getMagZ_uT();

  mag_msg2.header.stamp = nh.now();
  mag_msg2.header.frame_id = "/world";
  mag_msg2.magnetic_field.x = IMU2.getMagX_uT();
  mag_msg2.magnetic_field.y = IMU2.getMagY_uT();
  mag_msg2.magnetic_field.z = IMU2.getMagZ_uT();

  mag_msg3.header.stamp = nh.now();
  mag_msg3.header.frame_id = "/world";
  mag_msg3.magnetic_field.x = IMU3.getMagX_uT();
  mag_msg3.magnetic_field.y = IMU3.getMagY_uT();
  mag_msg3.magnetic_field.z = IMU3.getMagZ_uT();

  mag_msg4.header.stamp = nh.now();
  mag_msg4.header.frame_id = "/world";
  mag_msg4.magnetic_field.x = IMU4.getMagX_uT();
  mag_msg4.magnetic_field.y = IMU4.getMagY_uT();
  mag_msg4.magnetic_field.z = IMU4.getMagZ_uT();
  
  pub_mag1.publish(&mag_msg1);
  pub_mag2.publish(&mag_msg2);
  pub_mag3.publish(&mag_msg3);
  pub_mag4.publish(&mag_msg4);

  nh.spinOnce();
  delay(10);
}
