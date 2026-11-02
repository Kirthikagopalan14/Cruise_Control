#include "../include/cruise/pid.hpp"
#include <algorithm>

namespace cruise{
    PID::PID(pid_Config pidParams):pid_params_(pidParams){}

    double PID::update(double ref, double meas, double dt_s){
        const pid_Config& c = pid_params_;

        // At 0th time instance -> do nothing.
        if(dt_s <= 0){return last_output_;}

        // Error calculation
        const double err = ref - meas;

        // For Derivative calculation, first call check is necessary
        // and remember the speed so D starts at zero.
        if(first_call_){
            previous_meas_ = meas;
            d_filtered_ = 0.0;
            first_call_ = false;
        }

        // Filtering Derivative of the speed
        const double d_raw = -(meas - previous_meas_) / dt_s;

        // Using low pass filter to smooth the Derivative action
        d_filtered_ = d_filtered_ + dt_s / (c.d_filter_s + dt_s) * (d_raw - d_filtered_);

        // Remember previous meas
        previous_meas_ = meas;

        // Calculate raw u before clamping
        const double u = c.kp * err + integral_ + c.kd * d_filtered_;

        // Clamp the output to u_min and u_max
        const double u_clamp = std::clamp(u, c.u_min, c.u_max);

        // Anti-windup rule: The output is "pushing further" if it is above u_max 
        // while the error is positive, or below u_min while the error is negative.
        const bool pushing_further = (u > c.u_max && err > 0.0) || (u < c.u_min && err < 0.0);

        if(!c.anti_windup || !pushing_further){
            // Calculate integral part
            integral_ = integral_ + c.ki * err * dt_s;
        }
        
        last_output_ = u_clamp;
        return u_clamp;
    }
}