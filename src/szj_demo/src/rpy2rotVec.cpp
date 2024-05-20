#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

// 定义一个函数，用于将rpy角转换为旋转矩阵
Eigen::Matrix3d rpy2rot(double roll, double pitch, double yaw)
{
  // 定义旋转矩阵的三个基本旋转
  Eigen::Matrix3d Rx, Ry, Rz;
  Rx << 1, 0, 0,
        0, cos(roll), -sin(roll),
        0, sin(roll), cos(roll);
  Ry << cos(pitch), 0, sin(pitch),
        0, 1, 0,
        -sin(pitch), 0, cos(pitch);
  Rz << cos(yaw), -sin(yaw), 0,
        sin(yaw), cos(yaw), 0,
        0, 0, 1;
  // 返回绕z-y-x轴的旋转矩阵
  return Rz * Ry * Rx;
}

// 定义一个函数，用于将旋转矩阵转换为旋转矢量
Eigen::Vector3d rot2vec(Eigen::Matrix3d R)
{
  // 定义旋转矢量的角度和轴
  double angle, x, y, z;
  // 计算旋转角度
  angle = acos((R.trace() - 1) / 2);
  // 判断旋转角度是否为0或180度
  if (angle == 0)
  {
    // 如果旋转角度为0，返回零向量
    return Eigen::Vector3d::Zero();
  }
  else if (angle == M_PI)
  {
    // 如果旋转角度为180度，需要特殊处理
    // 找到旋转矩阵对角线上最大的元素
    int max_index = 0;
    double max_value = R(0, 0);
    for (int i = 1; i < 3; i++)
    {
      if (R(i, i) > max_value)
      {
        max_index = i;
        max_value = R(i, i);
      }
    }
    // 根据最大的元素，计算旋转轴的分量
    switch (max_index)
    {
    case 0:
      x = sqrt((R(0, 0) + 1) / 2);
      y = R(0, 1) / (2 * x);
      z = R(0, 2) / (2 * x);
      break;
    case 1:
      y = sqrt((R(1, 1) + 1) / 2);
      x = R(1, 0) / (2 * y);
      z = R(1, 2) / (2 * y);
      break;
    case 2:
      z = sqrt((R(2, 2) + 1) / 2);
      x = R(2, 0) / (2 * z);
      y = R(2, 1) / (2 * z);
      break;
    }
  }
  else
  {
    // 如果旋转角度不为0或180度，按照正常公式计算旋转轴的分量
    x = (R(2, 1) - R(1, 2)) / (2 * sin(angle));
    y = (R(0, 2) - R(2, 0)) / (2 * sin(angle));
    z = (R(1, 0) - R(0, 1)) / (2 * sin(angle));
  }
  // 返回旋转矢量，其方向为旋转轴，长度为旋转角度
  return angle * Eigen::Vector3d(x, y, z);
}

int main()
{
  // 定义一个rpy角，单位为弧度
  double roll = -2.671;
  double pitch =0.503;
  double yaw = 2.730;

  // 调用函数，将rpy角转换为旋转矩阵
  Eigen::Matrix3d R = rpy2rot(roll, pitch, yaw);

  // 调用函数，将旋转矩阵转换为旋转矢量
  Eigen::Vector3d v = rot2vec(R);

  // 打印结果
  std::cout << "The rotation matrix is:\n"
            << R << std::endl;
  std::cout << "The rotation vector is:\n"
            << v << std::endl;

  return 0;
}
