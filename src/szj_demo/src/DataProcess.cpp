#include "../include/DataProcess.h"
DataProcess::DataProcess()
{
    nowCommand_.resize(6);
    nowPos_.resize(6);
    pub_data_ = nh_.advertise<geometry_msgs::Pose>("/szj/endCommand",5);
    sub_pos_ = nh_.subscribe("/szj/endPos",5, &DataProcess::subPosCallback, this);
    ros::Duration(0.1).sleep();
}
DataProcess::~DataProcess()
{
}

void DataProcess::readData(std::string filePath){
    std::ifstream fileHandle;
    fileHandle.open(filePath, std::ios::in);
    if(fileHandle.is_open()){
        std::string line;
        while(std::getline(fileHandle,line)){
            std::stringstream ss(line);
            std::vector<double> row;
            double value = 0;
            while(ss >> value){
                row.push_back(value);
            }
            // std::cout << ss. << std::endl;
            oriData_.push_back(row);
        }
        fileHandle.close();
        std::cout << "size : " << oriData_.size() << "*" << oriData_[0].size() << std::endl;
    }
    else{
        std::cout << "error : cannot open file" << std::endl;
    }
}
void DataProcess::printData(){
    for(int i = 0; i < oriData_.size(); ++i){
        for(int j = 0; j < oriData_[i].size(); ++j){
            std::cout << oriData_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void DataProcess::printQuantData(){
    for(int i = 0; i < quantData_.size(); ++i){
        for(int j = 0; j < quantData_[i].size(); ++j){
            std::cout << quantData_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void DataProcess::rpy2quant(){
    for(int i = 0; i < oriData_.size(); ++i){
        KDL::Rotation ori_pos;
        ori_pos = KDL::Rotation::RPY(oriData_[i][3], oriData_[i][4], oriData_[i][5]);
        double x, y, z, w;
        ori_pos.GetQuaternion(x, y, z, w);
        std::vector<double> new_pos(7);
        for(int j = 0; j < 3; ++j){
            new_pos[j] = oriData_[i][j];
        }
        new_pos[3] = x; new_pos[4] = y; new_pos[5] = z; new_pos[6] = w;
        quantData_.push_back(new_pos);
    }
}

void DataProcess::rpy2rotvec(){
    for(int i = 0; i < oriData_.size(); ++i){
        KDL::Rotation ori_pos;
        ori_pos = KDL::Rotation::RPY(oriData_[i][3], oriData_[i][4], oriData_[i][5]);
        KDL::Vector rotVec = ori_pos.GetRot();
        std::vector<double> new_pos(6);
        for(int j = 0; j < 3; ++j){
            new_pos[j] = oriData_[i][j];
        }
        new_pos[3] = rotVec.data[0]; new_pos[4] = rotVec.data[1]; new_pos[5] = rotVec.data[2];
        rotvecData_.push_back(new_pos);
    }
}

bool DataProcess::calculateDiff(){
    if(pubFlag_ == false){
        double positionTolerance = 1e-4;
        double rotationTolerance = 1e-4;
        // Check position difference
        for (int i = 0; i < 3; ++i) {
            if (std::abs(nowCommand_[i] - nowPos_[i]) > positionTolerance) {
                ROS_INFO_STREAM("now pos: "<< nowPos_[i] <<" nowcommand: "<< nowCommand_[i]);
                ROS_INFO("not reach pose");
                return false;
            }
        }
        // Check rotation difference
        for (int i = 3; i < 6; ++i) {
            if (std::abs(nowCommand_[i] - nowPos_[i]) > rotationTolerance) {
                ROS_INFO("not reach attitude");
                return false;
            }
        }
        ROS_INFO("nowcommand:%lf %lf %lf", nowCommand_[0], nowCommand_[1], nowCommand_[2]);
        ROS_INFO("nowPos:%lf %lf %lf", nowPos_[0], nowPos_[1], nowPos_[2]);
        ROS_INFO("judge reach point");
        pubFlag_ = true;
        return true;
    }
    return false;
}

std::vector<double> DataProcess::quant2rotvec(std::vector<double> quantData){
    KDL::Rotation rotMat = KDL::Rotation::Quaternion(quantData[3], quantData[4], quantData[5], quantData[6]);
    KDL::Vector rotVec = rotMat.GetRot();
    std::vector<double> ret = {quantData[0], quantData[1], quantData[2], rotVec.data[0], rotVec.data[1], rotVec.data[2]};
    return ret;
}


void DataProcess::pubPath(){
    geometry_msgs::Pose pubQuantData;
    pubQuantData.position.x = quantData_[index][0];
    pubQuantData.position.y = quantData_[index][1];
    pubQuantData.position.z = quantData_[index][2];
    pubQuantData.orientation.x = quantData_[index][3];
    pubQuantData.orientation.y = quantData_[index][4];
    pubQuantData.orientation.z = quantData_[index][5];
    pubQuantData.orientation.w = quantData_[index][6];
    nowCommand_ = quant2rotvec(quantData_[index]);
    pub_data_.publish(pubQuantData);
    ROS_INFO_STREAM("PUB NEW DATA" << quantData_[index][0] << " " << quantData_[index][1]<< " "<< quantData_[index][2]);
    ROS_INFO("now index = %d", index);
}

void DataProcess::nextPoint(){
    if(index < quantData_.size() - 1){
        index++;
        nowCommand_ = quant2rotvec(quantData_[index]);
        pubFlag_ = false;
    }
}


/*ros*/
void DataProcess::subPosCallback(geometry_msgs::PoseConstPtr msg){
    KDL::Rotation attitude = KDL::Rotation::Quaternion(msg->orientation.x, msg->orientation.y, msg->orientation.z, msg->orientation.w);
    KDL::Vector attitudeRotvec = attitude.GetRot();
    nowPos_[0] = msg->position.x;
    nowPos_[1] = msg->position.y;
    nowPos_[2] = msg->position.z;
    nowPos_[3] = attitudeRotvec.data[0];
    nowPos_[4] = attitudeRotvec.data[1];
    nowPos_[5] = attitudeRotvec.data[2];
    ROS_INFO("call back");
}