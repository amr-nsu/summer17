#pragma once

template<class Device>
class Controller
{
public:
  Controller() :
    time_(0),
    angle_(0),
    gyroAngle_(0)
  {
  }

  void process()
  {
    double dt = deltaTime();
    int accX = 0;
    int accZ = 0;
    int gyroY = 0;

    Device::DeviceTraits::read(accX, accZ, gyroY);
    constexpr double rad2grad = 180.0 / 3.14159;
    double accAngle = -atan2(accX, accZ) * rad2grad;
    double gyroRaw = gyroY / 131.0;
    filter(accAngle, gyroRaw, dt);
    int power = control(angle_, gyroRaw, dt);
    apply(power);

    Device::DeviceTraits::write(currentTime(), 3);
    Device::DeviceTraits::write(accAngle, 3);
    Device::DeviceTraits::write(angle_, 3);
    Device::DeviceTraits::write(gyroRaw, 3);
    Device::DeviceTraits::write(dt, 4);
    Device::DeviceTraits::write(gyroAngle_, 3);
    Device::DeviceTraits::write(power);
    Device::DeviceTraits::writeln();
  }

private:
  void filter(double accAngle, double gyroRaw, double dt)
  {
    constexpr double shift = 0.003;
    constexpr double k = 0.9;
    gyroAngle_ += gyroRaw * dt - shift;
    angle_ = k * (angle_ + gyroRaw * dt - shift) + (1 - k) * accAngle;    
  }

  double deltaTime()
  // precess delta time in seconds
  {
    unsigned long now = Device::DeviceTraits::time();
    unsigned long delta = now - time_;
    time_ = now;
    return delta / 1e6;
  }

  double currentTime()
  // current time in seconds
  {
    return time_ / 1e6;
  }

  int control(double e, double de, double dt)
  {   
    if (e > 2.5) return 43;
    if (e < -2.5) return -43;

    static double i = 0;
    double p = Device::ControlTraits::p * e;
    i += Device::ControlTraits::i * e * dt;
    double d = Device::ControlTraits::d * de;

    if (i > 255) i = 255;
    if (i < -255) i = -255;

    int power = round(p + i + d);
    if (power > 255) power = 255;
    if (power < -255) power = -255;
    return power;
  }

  void apply(int power)
  {
    Device::DeviceTraits::control(power);
  }

  unsigned long time_;
  double angle_;
  double gyroAngle_;
};


