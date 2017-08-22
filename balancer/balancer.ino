#include "I2Cdev.h"
#include "MPU6050.h"
#include "controller.hpp"

namespace balancer
{
  constexpr int pinMotorA1 = PA0;
  constexpr int pinMotorA2 = PA1;
  constexpr int pinMotorB1 = PA2;
  constexpr int pinMotorB2 = PA3;

struct ControlTraits
{
  static constexpr double p = 9;
  static constexpr double i = 0.001;
  static constexpr double d = 0;
};

MPU6050 accelgyro;

class DeviceTraits
{
public:
  static void read(int& accX, int& accZ, int& gyroY)
  {
    static int16_t ax, ay, az;
    static int16_t gx, gy, gz;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    accX = ax;
    accZ = az;
    gyroY = gy;
  }

  static void write(double value, int precision=3) 
  {
    Serial.print(value, precision);
    Serial.print("\t");
  }

  static void writeln()
  {
    Serial.println();
  }

  static void control(int power)
  {
    if (power > 255)  power = 255;
    if (power < -255) power = -255;

    if (power >= 0) {  //FORWARD
      analogWrite(pinMotorA2, 0);
      analogWrite(pinMotorA1, power);
      analogWrite(pinMotorB2, 0);
      analogWrite(pinMotorB1, power);
    } else {           //BACKWARD
      analogWrite(pinMotorA1, 0);
      analogWrite(pinMotorA2, -power);
      analogWrite(pinMotorB1, 0);
      analogWrite(pinMotorB2, -power);
    }
  }

  static unsigned long time()
  {
    return micros();
  }
};

} // namespace balancer

void setup()
{
  Wire.begin();
  Serial.begin(38400);
  balancer::accelgyro.initialize();
  balancer::accelgyro.testConnection();
}

class Device
{
public:
  using ControlTraits = balancer::ControlTraits;
  using DeviceTraits = balancer::DeviceTraits;
};

Controller<Device> controller;

void loop()
{
  controller.process();
}
