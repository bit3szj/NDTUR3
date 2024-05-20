#include<fstream>
#include<Eigen/Eigen>



using namespace Eigen;

typedef Matrix<double, 6, 1> Vector6d;
typedef Matrix<double, 6, 6> Matrix6d;

class ChangeController
{
public:
    ChangeController();
private:
    void csv_debug(std::vector<double> vec, std::string name);



private:
    bool freedrive_mode_request;
    bool admittance_control_request, freedrive_mode_request;
};
