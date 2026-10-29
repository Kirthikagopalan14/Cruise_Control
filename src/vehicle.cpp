#include "../include/cruise/vehicle.hpp"
#include <cmath>

namespace cruise
{
    Vehicle::Vehicle(VehicleParams params, VehicleState state) : params_(params), state_(state) {}

    void Vehicle::step(double drive_force_cmd_n, double slope_rad, double dt_s)
    {
        const VehicleParams &p = params_;
        const double speed = state_.speed_mps;
        const double force = state_.drive_force_n;
        // 1. air drag (formula 1)
        const double air_drag = 0.5 * params_.air_density * params_.cd_a_m2 * speed * std::abs(speed);

        // 2. tyre drag (formula 2). Use: (speed > 0) - (speed < 0) for the sign.
        double tyre_drag = 0;
        if (speed > 0)
        {
            tyre_drag = params_.mass_kg * params_.gravity * params_.crr;
        }
        else if (speed < 0)
        {
            tyre_drag = -(params_.mass_kg * params_.gravity * params_.crr);
        }

        // 3. slope force (formula 3)
        const double slope_force = params_.mass_kg * params_.gravity * sin(slope_rad);

        // 4. acceleration (formula 4)
        const double acceleration = (drive_force_cmd_n - air_drag - tyre_drag - slope_force) / params_.mass_kg;

        // 5. engine force rate (formula 5)
        const double force_rate = (drive_force_cmd_n - force) / params_.drive_lag_s; // TODO

        // 6. new speed = old speed + acceleration * dt
        state_.speed_mps = speed + acceleration * dt_s;

        // 7. new engine force = old engine force + force_rate * dt
        state_.drive_force_n = force + force_rate * dt_s;
    }
}
