#pragma once

namespace cruise{

    struct VehicleParams
    {
        double mass_kg = 1500;         // kg
        double cd_a_m2 = 0.7;     // m^2
        double crr = 0.012; // Const
        double air_density = 1.225;
        double drive_lag_s = 0.3;
        double gravity = 9.81;
    };
    struct VehicleState{
        double speed_mps = 0.0;
        double drive_force_n = 0.0;
    };

    class Vehicle
    {
        private:
            VehicleParams params_;
            VehicleState state_;
        public:
            Vehicle(VehicleParams params = VehicleParams{}, VehicleState state = VehicleState{});

            void step(double drive_force_cmd_n, double slope_rad, double dt_s);

            const VehicleState& state() const{
                return state_;
            }

            const VehicleParams& params() const{
                return params_;
            }
        
    };


}