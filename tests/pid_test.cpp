#include <gtest/gtest.h>
#include "../include/cruise/pid.hpp"

using cruise::PID;
using cruise::pid_Config;

// change all the config to off and no limits. change only what a test needs.
pid_Config plain(){
    pid_Config c;
    c.kd = 0.0;
    c.kp = 0.0;
    c.ki = 0.0;
    c.u_max = 1e9;
    c.u_min = -1e9;
    return c;
}

TEST(PID, ProportionalOnly){
    pid_Config p = plain();
    p.kp = 800.0;

    PID PControl(p);
    EXPECT_NEAR(PControl.update(20, 15, 0.01), 4000, 1e-9);
}

TEST(PID, OutputIsCut){
    pid_Config p = plain();
    p.kp = 800.0;
    p.u_min = -5000.0;
    p.u_max = 4000;

    PID PControlTrim1(p);
    EXPECT_NEAR(PControlTrim1.update(20, 0, 0.01), 4000, 1e-9);

    PID PControlTrim2(p);
    EXPECT_NEAR(PControlTrim2.update(0, 20, 0.01), -5000, 1e-9);
}

TEST(PID, IntegralGrows){

    pid_Config p = plain();
    p.ki = 80.0;

    PID IntegralGrows(p);
    double u = 0.0;
    for(int i = 0; i <= 100; ++i)
    {
        u = IntegralGrows.update(2, 0, 0.01);
    }
    EXPECT_NEAR(u, 160, 1e-9);
}

TEST(PID, AntiWindupStopsMemoryA){

    pid_Config p = plain();
    p.kp = 800.0;
    p.ki = 80.0;
    p.u_max = 4000;
    p.u_min = -5000;
    p.anti_windup = true;

    PID AntiWindupStopsMemory(p);
    for(int i = 1; i <= 1000; ++i)
    {
        AntiWindupStopsMemory.update(20, 0, 0.01);
    }
    EXPECT_NEAR(AntiWindupStopsMemory.integral(), 0, 1e-6);
}

TEST(PID, AntiWindupStopsMemoryB){

    pid_Config p = plain();
    p.kp = 800.0;
    p.ki = 80.0;
    p.u_max = 4000;
    p.u_min = -5000;
    p.anti_windup = false;

    PID AntiWindupStopsMemoryB(p);
    for(int i = 1; i <= 1000; ++i)
    {
        AntiWindupStopsMemoryB.update(20, 0, 0.01);
    }
    EXPECT_NEAR(AntiWindupStopsMemoryB.integral(), 16000, 1e-6);
}


TEST(PID, DerivativeNoKickA){

    pid_Config p = plain();
    p.kd = 100.0;
    PID DerivativeNoKick(p);
    double u = 0.0;
    for(int i = 1; i <= 10; ++i)
    {
        u = DerivativeNoKick.update(0, 0, 0.01);
    }
    EXPECT_NEAR(u, 0, 1e-9);
    u = 0.0;
    for(int i = 1; i <= 10; ++i)
    {
        u = DerivativeNoKick.update(20, 0, 0.01);
    }
    EXPECT_NEAR(u, 0, 1e-9);
}

TEST(PID, DerivativeNoKickB){

    pid_Config p = plain();
    p.kd = 100.0;
    PID DerivativeNoKickB(p);
    double u = 0.0;
    for(int i = 1; i <= 200; ++i)
    {
        u = DerivativeNoKickB.update(0, i*0.01, 0.01);
    }
    EXPECT_NEAR(u, -100, 1e-2);
}

TEST(PID, ZeroTimeStep){

    pid_Config p = plain();
    p.kp = 800.0;

    PID ZeroTimeStep(p);
    double u = 0.0;
    u = ZeroTimeStep.update(20, 15, 0.01);
    EXPECT_NEAR(u, 4000, 0);
    u = ZeroTimeStep.update(20, 0, 0.0);
    EXPECT_NEAR(u, 4000, 0);
}