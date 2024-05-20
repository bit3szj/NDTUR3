#include<ros/ros.h>
#include<geometry_msgs/Pose.h>
#include <cartesian_state_msgs/PoseTwist.h>
#include "szj_demo/AdmStatus.h"
#include "2PDcontrol.cpp"
#define m_debug 0
// #include<cmath>
const double linear_damp=0.0075;
// const double linear_damp=0.075;
const double angular_damp=0.5;
double envPosition = 0.3;
class EnvSim
{
public:
    EnvSim() = default;
    EnvSim(double f) : forceTarget(f), _envForce(0), actual_vel(0),
        currentPos(0), lastPos(0)
    {
        //create a subscriber to subscribe the manipular cartesian state
        m_sub = m_nh.subscribe("cartesian_velocity_position_controller/ee_state",1, &EnvSim::forceCallback, this);
        //create a publisher to publish correct position to manipular controller
        for(uint i = 0; i < 7; ++i){
            desirePosition[i] = currentPosition[i];
        }
        
        sub_desirePos = m_nh.subscribe("/cartesian_velocity_position_controller/command_cart_pos",1,&EnvSim::subDesirePoseCallback, this);
        
        m_pub = m_nh.advertise<geometry_msgs::Pose>("/cartesian_velocity_position_controller/command_cart_pos_correct",2);
        pub_force = m_nh.advertise<geometry_msgs::Pose>("admForce",1);
        pub_admStatus = m_nh.advertise<szj_demo::AdmStatus>("/szj/admStatus",5);
        m_pdControl = new szjspace::PdControl(m_kp, m_kd);
        ros::Duration(1).sleep();
        init_compensate();
        ros::Rate loop_rate(50);
        time_last = ros::Time::now();
        // time_now = ros::Time::now();
        //set the parameter value to the initial value in program
        m_nh.setParam("global_paraForce", forceTarget);
        m_nh.setParam("global_paraEnvK", env_paraK);
        m_nh.setParam("global_paraB", b_para);
        m_nh.setParam("global_paraM", m_para);
        m_nh.setParam("global_paraK", k_para);
        m_nh.setParam("global_paraKp", m_kp);
        m_nh.setParam("global_paraKd", m_kd);
        m_nh.setParam("global_paraPosLim", m_posLim);
        m_nh.setParam("global_paraNegLim", m_negLim);
        m_nh.setParam("global_paraEnvPosFlag", envPosFlag);
        ros::Duration(0.1).sleep();
        double initEnvK = env_paraK;
        fzErr_last = forceTarget - 0;
        while(ros::ok())
        {
            ros::spinOnce();
            time_now = ros::Time::now();
            double desirePos = desirePosition[2];
            // actual_vel = (currentPos - lastPos) / delta_t;
            this->getVel();
            //each loop gets data
            m_nh.getParam("global_paraForce", forceTarget);
            m_nh.getParam("global_paraEnvK", env_paraK);
            m_nh.getParam("global_paraB", b_para);
            m_nh.getParam("global_paraM", m_para);
            m_nh.getParam("global_paraK", k_para);
            m_nh.getParam("global_envKFlag", envKFlag);
            m_nh.getParam("global_paraKd", m_kd);
            m_nh.getParam("global_paraKp", m_kp);
            m_nh.getParam("global_paraPosLim", m_posLim);
            m_nh.getParam("global_paraNegLim", m_negLim);
            m_nh.getParam("global_paraEnvPosFlag", envPosFlag);
            if(envKFlag == 1){
                env_paraK = 20000 * currentPosition[1] + 3000;
                m_nh.setParam("global_paraEnvK", env_paraK);
            }
            if(envPosFlag != 0){
                if(!envTimeFlag){
                    start = ros::Time::now();
                    envTimeFlag = true;
                }
                ros::Time now = ros::Time::now();
                double elapsed = (now - start).toSec();
                if(elapsed <= 4.0){
                    envPosition = 0.3+0.01*sin(0.5*M_PI*(elapsed - 0));
                }
            }else{
                envTimeFlag = false;
                envPosition = 0.3;
            }

            //calculate the current force 
            // _envForce = (0.3 - currentPos) * env_paraK;
            this->getForce();

            geoPubData.position.x = forceTarget;
            geoPubData.position.y = _envForce;
            pub_force.publish(geoPubData);
            #if m_debug
            ROS_INFO_STREAM("b_para : " << b_para);
            ROS_INFO_STREAM("m_para" << m_para);
            ROS_INFO_STREAM("actual_vel : " << actual_vel);
            ROS_INFO_STREAM("minus force : " << abs(_envForce - forceTarget));
            ROS_INFO_STREAM("envforce : " << _envForce);
            ROS_INFO_STREAM("forceTarget : " << forceTarget);
            #endif
            // if(currentPos < 0.3)
            // {
            //     double zdd = 1/m_para*((_envForce - forceTarget) - b_para*actual_vel - k_para * (currentPos - 0.3));
            // }else{
            //     double zdd = 1/m_para*((_envForce - forceTarget) - b_para*actual_vel);
            // }
            delta_t = (time_now - time_last).toSec();
            fzErr_now = _envForce - forceTarget;
            // fzErr_now = forceTarget - _envForce;
            fzErr_dot = (fzErr_now - fzErr_last)/(time_now - time_last).toSec();
            m_pdControl->setParam(m_kp, m_kd);
            m_pdControl->setLimitValue(m_posLim, m_negLim);
            delta_B = m_pdControl->calculate(fzErr_now, fzErr_dot);
            ROS_INFO("deltaB = %f",delta_B);
            m_pdControl->limitDeltaB(delta_B);
            double localB = b_para + delta_B;
            m_nh.setParam("global_paraLocalB", localB);
            // double localB = b_para;
            // double zdd = 1/m_para*((fzErr_now) - localB*(actual_vel-0));
            double zdd = 1/m_para*((fzErr_now) - localB*(actual_vel-0) - k_para*(currentPos - desirePos));

            ROS_INFO_STREAM("zdd : " << zdd);
            commandVel = actual_vel + zdd * delta_t;
            // commandVel = zdd * delta_t + vel_last;
            ROS_INFO("actualVel: %f", actual_vel);
            ROS_INFO_STREAM("commandVel : " << commandVel);
            // commandPos = currentPos + commandVel * delta_t;//这里不可以使用curentPos因为不是直接融合坐标后发送的，是发送补偿量，补偿量与原坐标无关，否则就驴头不对马嘴
            commandPos = commandPos + commandVel * delta_t;
            ROS_INFO("currentPos: %f", currentPos);
            ROS_INFO("delta_t: %f", delta_t);
            
            this->limitPos(commandPos);
            ROS_INFO_STREAM("commandPos : " << commandPos<< "\n");
            m_compensate.position.z = commandPos;
            m_pub.publish(m_compensate);
            #if 0
            if(abs(_envForce - forceTarget) > 0.1){
                // commandVel= -linear_damp*(_envForce - forceTarget);
                // // commandPos = commandVel * double(1.0/25.0);
                // commandPos = commandVel * 0.1;
                if(abs(_envForce - forceTarget) > 5)
                    commandPos = (_envForce - forceTarget) * 1;
                else if(abs(_envForce - forceTarget) > 1)
                    commandPos = (_envForce - forceTarget) * 0.1;
                else
                    commandPos = (_envForce - forceTarget) * 0.02;
                if (commandPos < -0.1 || commandPos >0.1)
                {   
                    double midNum = abs(commandPos);
                    commandPos = (commandPos/(abs(commandPos))) * 0.1;  
                }
                m_compensate.position.z = commandPos;
                m_pub.publish(m_compensate);
                ROS_INFO_STREAM("commandV = " << commandVel << "; commandP = " << commandPos);
                ROS_INFO_STREAM("now_z = " << m_comZ << "; force target = " << forceTarget);
                ROS_INFO_STREAM(m_compensate);
                ROS_INFO_STREAM("_envFoce = " << _envForce << "; commandPos = " << commandPos << "; k = " << _paraK << "\n");
                
            }else{
                m_compensate.position.z = 0;
                m_pub.publish(m_compensate);
                ROS_INFO_STREAM("stop and now z = " << m_comZ <<"force diff = " << _envForce - forceTarget);
            }
            #endif
            lastPos = currentPos;
            szj_demo::AdmStatus pubData_admStatus;
            pubData_admStatus.forceTarget = this->forceTarget;
            pubData_admStatus.forceNow = this->_envForce;
            pub_admStatus.publish(pubData_admStatus);
            time_last = time_now;
            vel_last = actual_vel;
            //sleep for the desired rate
            loop_rate.sleep();
        }
    }
    ~EnvSim();
private:
    double env_paraK = 3000;
    double _envForce;
    double m_comZ;
    double forceTarget;
    double commandVel;
    double commandPos;
    double delta_t = 0.02;
    ros::Time time_last;
    ros::Time time_now;
    double m_para = 10;
    double b_para = 500;
    double k_para = 1;
    double envKFlag = 0;
    double actual_vel = 0;
    double vel_last = 0;
    double currentPos;
    double currentPosition[7];
    double desirePosition[7] = {0};
    double lastPos = 0.3;

    //
    double envPosFlag = 0;
    bool envTimeFlag = false;
    ros::Time start;


    ros::Subscriber m_sub;
    ros::Subscriber sub_desirePos;
    ros::Publisher m_pub;
    ros::Publisher pub_force;
    ros::Publisher pub_admStatus;
    ros::NodeHandle m_nh;
    geometry_msgs::Pose m_compensate;
    geometry_msgs::Pose geoPubData;
    double delta_B=0;
    double m_kd = -0.5, m_kp = 30;
    double m_posLim = 500, m_negLim = -450;
    szjspace::PdControl *m_pdControl;
    double fzErr_last = 0, fzErr_now = 0, fzErr_dot=0;


private:
    void forceCallback(cartesian_state_msgs::PoseTwistConstPtr msg);
    void subDesirePoseCallback(cartesian_state_msgs::PoseTwistConstPtr msg);
    void init_compensate();
    void limitPos(double&);
    void getForce();
    void getVel();

};

inline void EnvSim::init_compensate(){
    m_compensate.position.x = 0;
    m_compensate.position.y = 0;
    m_compensate.position.z = 0;
    m_compensate.orientation.x = 0;
    m_compensate.orientation.y = 0;
    m_compensate.orientation.z = 0;
    m_compensate.orientation.w = 1;
}

EnvSim::~EnvSim(){
    delete m_pdControl;
}


void EnvSim::forceCallback(cartesian_state_msgs::PoseTwistConstPtr msg)
{
    currentPos = msg->pose.position.z;
    currentPosition[0] = msg->pose.position.x;
    currentPosition[1] = msg->pose.position.y;
    currentPosition[2] = msg->pose.position.z;
    currentPosition[3] = msg->pose.orientation.x;
    currentPosition[4] = msg->pose.orientation.y;
    currentPosition[5] = msg->pose.orientation.z;
    currentPosition[5] = msg->pose.orientation.w;
    
    // 更新上一次的位置

    #if 0
    ROS_INFO("now vel = %lf\n", actual_vel);
    #endif
}

void EnvSim::subDesirePoseCallback(cartesian_state_msgs::PoseTwistConstPtr msg)
{

    desirePosition[0] = msg->pose.position.x;
    desirePosition[1] = msg->pose.position.y;
    desirePosition[2] = msg->pose.position.z;
    desirePosition[3] = msg->pose.orientation.x;
    desirePosition[4] = msg->pose.orientation.y;
    desirePosition[5] = msg->pose.orientation.z;
    desirePosition[5] = msg->pose.orientation.w;

}

inline void EnvSim::limitPos(double &pos){
    if(abs(pos) < 1e-4) pos = 0;
    else if(pos > 0.1) pos = 0.1;
    else if(pos < -0.1) pos = -0.1;
    else;
}

inline void EnvSim::getForce(){
    
    if(currentPos > envPosition) _envForce = 0;
    else {
            _envForce = (envPosition - currentPos) * env_paraK;
    }

        

}
//use the data you get from subscribing to the topic ee_state to calculate the velocity
inline void EnvSim::getVel(){
    if(abs(currentPos - lastPos) < 0.001) actual_vel = 0;
    else actual_vel = (currentPos - lastPos) / delta_t;
}

int main(int argc, char**argv)
{
    //init the ros node
    ros::init(argc, argv, "env_simulation");
    EnvSim envSim(30);
    //create a rate object
    return 0;
}