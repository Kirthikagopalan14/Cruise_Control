#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <vector>

#include "cruise/pid.hpp"
#include "cruise/vehicle.hpp"

TEST(ClosedLoop, MeetsSpec) {
  cruise::pid_Config config;
  cruise::PID pid(config);
  cruise::Vehicle car;
  const double dt = 0.01;

  double peak_speed = 0.0;
  double worst_error_15_30 = 0.0;   // largest |speed - 20| for t in [15, 30]
  double worst_error_40_45 = 0.0;   // largest |speed - 20| for t in [40, 45]
  bool force_in_range = true;

  for (int i = 0; i < 4500; ++i) {  // 45 seconds
    const double t = i * dt;
    const double slope = (t < 30.0) ? 0.0 : std::atan(0.03);
    const double cmd = pid.update(20.0, car.state().speed_mps, dt);
    car.step(cmd, slope, dt);
    const double speed = car.state().speed_mps;

    peak_speed = std::max(peak_speed, speed);
    if (t >= 15.0 && t <= 30.0)
      worst_error_15_30 = std::max(worst_error_15_30, std::abs(speed - 20.0));
    if (t >= 40.0 && t <= 45.0)
      worst_error_40_45 = std::max(worst_error_40_45, std::abs(speed - 20.0));
    if (cmd < config.u_min || cmd > config.u_max) force_in_range = false;
  }

  EXPECT_LE(peak_speed, 21.0);          // rule 1: overshoot at most 1 m/s (5 percent)
  EXPECT_LE(worst_error_15_30, 0.4);    // rule 2: close to 20 before the hill
  EXPECT_LE(worst_error_40_45, 0.4);    // rule 3: recovered after the hill
  EXPECT_TRUE(force_in_range);          // rule 4: never asks for impossible force
}