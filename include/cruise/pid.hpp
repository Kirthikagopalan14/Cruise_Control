#pragma once

namespace cruise{
    struct pid_Config {
        double kp = 1000;
        double ki = 150;
        double kd = 0;
        double d_filter_s = 0.1;
        double u_min = -5000;
        double u_max = 4000;
        bool anti_windup = true;
    };

    class PID{
        private:
            pid_Config pid_params_;
            double integral_ = 0.0;
            double previous_meas_ = 0.0;
            double d_filtered_ = 0.0;
            double last_output_ = 0.0;
            bool first_call_ = true;
        public:
            PID(pid_Config pidParams = pid_Config{});
            // Update the engine force after every dt_s seconds
            double update(double ref, double meas, double dt_s);

            double integral() const {return integral_;}
    };
}