#include "../include/PDcontrol.h"

szjspace::PdControl::PdControl(double in_kp, double in_kd):
    kp(in_kp),
    kd(in_kd)
{
}

szjspace::PdControl::~PdControl()
{
}

double szjspace::PdControl::calculate(double err, double err_d){
    double u = kp * err + kd * err_d;
    return u;
}

void szjspace::PdControl::limitDeltaB(double &in_deltaB){
    if(in_deltaB > posLimitValue){
        in_deltaB = posLimitValue;
    }
    else if(in_deltaB < negLimitValue){
        in_deltaB = negLimitValue;
    }

}
//set Kp and Kd
void szjspace::PdControl::setParam(double inKp, double inKd){
    this->kd = inKd;
    this->kp = inKp;
}

void szjspace::PdControl::setLimitValue(const double posVel, const double negVel){
    posLimitValue = posVel;
    negLimitValue = negVel;
}