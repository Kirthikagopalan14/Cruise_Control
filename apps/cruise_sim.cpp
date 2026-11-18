#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../include/cruise/pid.hpp"
#include "../include/cruise/vehicle.hpp"
using cruise::Vehicle;
using cruise::VehicleParams;
using cruise::VehicleState;

// Usage: cruise_sim <anti_windup: 1 or 0> <output.csv>
int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "usage: cruise_sim <1 or 0> <output.csv>\n";
    return 1;
  }
  cruise::pid_Config config;
  config.anti_windup = (std::atoi(argv[1]) != 0);
  cruise::PID pid(config);
  cruise::Vehicle car;

  std::ofstream out(argv[2]);
  out << "t_s,ref_mps,speed_mps,force_cmd_n,force_actual_n,slope_rad\n";

  const double dt = 0.01;
  for (int i = 0; i < 6000; ++i) {  // 60 seconds
    const double t = i * dt;
    const double ref = (t < 45.0) ? 20.0 : 25.0;           // target speed
    const double slope = (t < 30.0) ? 0.0 : std::atan(0.03);  // 3 percent hill
    const double cmd = pid.update(ref, car.state().speed_mps, dt);
    car.step(cmd, slope, dt);
    out << t << ',' << ref << ',' << car.state().speed_mps << ',' << cmd << ','
        << car.state().drive_force_n << ',' << slope << '\n';
  }
  return 0;
}