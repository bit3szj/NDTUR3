    #include<kdl/jntarray.hpp>
    #include<ros/ros.h>
    class PIDController
    {
        public:
            // Constructor with PID gains
            PIDController(double kp, double ki, double kd, double max, double min):
            kp_(kp), ki_(ki), kd_(kd), last_time_(ros::Time::now()), output_max_(max), output_min_(min)
            {
                // Initialize the error, integral and derivative terms
                error_.resize(6); // Assuming 6 joints
                error_.data.setZero();
                integral_.resize(6);
                integral_.data.setZero();
                derivative_.resize(6);
                derivative_.data.setZero();
                error_prev_.resize(6);
                error_prev_.data.setZero();
            }

            // Destructor
            ~PIDController()
            {
            }

            // Compute the control command based on the current and desired joint velocities
            KDL::JntArray computeCommand(const KDL::JntArray& q_curr, const KDL::JntArray& q_des)
            {
                ros::Time now_time_ = ros::Time::now();
                double dt_ = (now_time_ - last_time_).toSec();
                last_time_ = now_time_;
                // Compute the error
                KDL::Subtract(q_des, q_curr, error_);

                // Update the integral term
                KDL::Add(integral_, error_, integral_);

                // Compute the derivative term
                KDL::Subtract(error_, error_prev_, derivative_);
                KDL::Divide(derivative_, dt_, derivative_);

                // Store the previous error
                error_prev_ = error_;

                // Compute the proportional, integral and derivative terms
                KDL::JntArray P_term(6);
                KDL::Multiply(error_, kp_, P_term);
                KDL::JntArray I_term(6);
                KDL::Multiply(integral_, ki_, I_term);
                KDL::JntArray D_term(6);

                //integral limit
                for(unsigned int i =0; i < I_term.rows(); ++i){
                    if(I_term(i) > output_max_){
                        I_term(i) = output_max_;
                    }else if(I_term(i) < output_min_){
                        I_term(i) = output_min_;
                    }
                }
                KDL::Multiply(derivative_, kd_, D_term);

                // Compute the control command
                KDL::JntArray command(6);
                KDL::Add(P_term, I_term, command);
                KDL::Add(command, D_term, command);


                // Return the control command
                return command;
            }

        private:
            // PID gains
            double kp_;
            double ki_;
            double kd_;
            ros::Time last_time_;
            double output_max_;
            double output_min_;

            // Error, integral and derivative terms
            KDL::JntArray error_;
            KDL::JntArray error_prev_;
            KDL::JntArray integral_;
            KDL::JntArray derivative_;

    };

