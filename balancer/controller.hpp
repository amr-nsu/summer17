#pragma once

template<class Device>
class Controller
{
public:
  Controller() :
    time_(0),
    filterAngle_(0),
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
    double gyroRaw = Device::DeviceTraits::gyro(gyroY);
    double accAngle = Device::DeviceTraits::angle(accX, accZ);
    filter(accAngle, gyroRaw, dt);
    int power = control(gyroRaw, dt);
    apply(power);

    Device::DeviceTraits::write(currentTime(), 3);
    Device::DeviceTraits::write(accAngle, 3);
    Device::DeviceTraits::write(filterAngle_, 3);
    Device::DeviceTraits::write(gyroRaw, 3);
    Device::DeviceTraits::write(dt, 4);
    Device::DeviceTraits::write(gyroAngle_, 3);
    Device::DeviceTraits::write(power);
    Device::DeviceTraits::writeln();
  }

private:
  void filter(double accAngle, double gyroRaw, double dt)
  {
    constexpr double k1 = Device::ControlTraits::filter_gain;
    constexpr double k2 = 1 - k1;
    constexpr double shift = 0.003;
    gyroAngle_ += gyroRaw * dt - shift;
    filterAngle_ = k1 * (filterAngle_ + gyroRaw * dt - shift) + k2 * accAngle;
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

  int control(double de, double dt)
  {
    constexpr int limit = Device::ControlTraits::limit;
    constexpr double threshold = Device::ControlTraits::threshold;
    constexpr int threshold_control = Device::ControlTraits::threshold_control;

    double e = filterAngle_;
    if (e > threshold) return threshold_control;
    if (e < -threshold) return -threshold_control;

    static double i = 0;
    double p = Device::ControlTraits::p * e;
    i += Device::ControlTraits::i * e * dt;
    double d = Device::ControlTraits::d * de;

    if (i > limit) i = limit;
    if (i < -limit) i = -limit;

    int power = round(p + i + d);
    if (power > limit) power = limit;
    if (power < -limit) power = -limit;
    return power;
  }

  void apply(int power)
  {
    Device::DeviceTraits::control(power);
  }

  unsigned long time_;
  double filterAngle_;
  double gyroAngle_;
};


