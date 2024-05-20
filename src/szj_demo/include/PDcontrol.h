#ifndef _PDCONTROL_H_
#define _PDCONTROL_H_
namespace szjspace{
class PdControl{

public:
    PdControl(double in_kp, double in_kd);
    ~PdControl();
    double calculate(double err, double err_d);
    void limitDeltaB(double &in_deltaB);
    void setParam(double, double);
    void setLimitValue(const double, const double);


private:
    double kp = 0;
    double kd = 0;
    double posLimitValue = 500;
    double negLimitValue = 0;
};
}
#endif