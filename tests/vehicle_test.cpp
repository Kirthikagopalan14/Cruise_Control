#include <gtest/gtest.h>
#include <cmath>
#include "../include/cruise/vehicle.hpp"


using cruise::Vehicle;
using cruise::VehicleParams;
using cruise::VehicleState;

TEST(Vehicle, TyreDragOnly) {
    VehicleParams p;
    p.cd_a_m2 = 0.0;

    VehicleState initial_state;
    initial_state.speed_mps = 20.0;
    initial_state.drive_force_n = 0.0;

    Vehicle car{p, initial_state};

    for (int i = 0; i < 1000; ++i) {
        car.step(0.0, 0.0, 0.01);
    }

    EXPECT_NEAR(car.state().speed_mps, 18.8228, 1e-9);
}

TEST(Vehicle, EngineLag){
    VehicleParams p;
    p.cd_a_m2 = 0.0;
    p.crr = 0.0;

    Vehicle car(p, VehicleState{0.0, 0.0});

    for(int i = 0; i < 100; ++i){
        car.step(1000.0, 0.0, 0.01);
    }

    EXPECT_NEAR(car.state().drive_force_n, 1000.0 * (1.0 - std::exp(-1.0 / 0.3)), 5.0);
}

TEST(Vehicle, TopSpeed){
    VehicleParams p;

    Vehicle car(p, VehicleState{10.0, 0.0});

    for(int i = 0; i < 60000; ++i){
        car.step(1500.0, 0.0, 0.01);
    }

    EXPECT_NEAR(car.state().speed_mps, std::sqrt(2.0 * (1500.0 - 1500.0 * 9.81 * 0.012) / (1.225 * 0.7)), 1e-3);
}