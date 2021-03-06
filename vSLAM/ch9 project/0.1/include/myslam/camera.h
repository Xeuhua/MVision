/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
// 相机模型类
#ifndef CAMERA_H //防止头文件重复引用
#define CAMERA_H//宏定义

#include "myslam/common_include.h"//常用的头文件 放在一起 化繁为简

namespace myslam//命令空间下 防止定义的出其他库里的同名函数
{

// Pinhole RGBD camera model
class Camera//相机模型类
{
public://数据成员设置为共有 可以改成私有 private
    typedef std::shared_ptr<Camera> Ptr;//共享指针 把 智能指针定义成 Camera的指针类型 以后参数传递时  使用Camera::Ptr 类型就可以了
    float   fx_, fy_, cx_, cy_, depth_scale_;  // Camera intrinsics  相机内参数

    Camera();
    Camera ( float fx, float fy, float cx, float cy, float depth_scale=0 ) :
        fx_ ( fx ), fy_ ( fy ), cx_ ( cx ), cy_ ( cy ), depth_scale_ ( depth_scale )
    {}

    // 坐标转换 coordinate transform: world, camera, pixel  
    //使用 Sophus::SE3 类表达相机位姿态(相机外参数)  即转换矩阵
    Vector3d world2camera( const Vector3d& p_w, const SE3& T_c_w );//世界坐标系(3维 ) 到 相机坐标系   输入 世界坐标系坐标p_w 和 T_c_w 转换矩阵
    Vector3d camera2world( const Vector3d& p_c, const SE3& T_c_w ); //相机坐标系 到 世界坐标系            输入 相机坐标系坐标p_c 和 T_c_w 转换矩阵
    Vector2d camera2pixel( const Vector3d& p_c );                                  //相机坐标系 到 图像像素坐标系             使用相机内参数
    Vector3d pixel2camera( const Vector2d& p_p, double depth=1 );    //图像像素坐标系(两维) 到 相机坐标系    使用相机内参数
    Vector3d pixel2world ( const Vector2d& p_p, const SE3& T_c_w, double depth=1 );//图像像素坐标系(两维)   到 世界坐标系pixel2camera2world 
    Vector2d world2pixel ( const Vector3d& p_w, const SE3& T_c_w );   //世界坐标系(三维) 到 图像像素坐标系  world2camera2pixel

};

}
#endif // CAMERA_H
