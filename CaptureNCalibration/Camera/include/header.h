/*
 * @Copyright: CS of BIT
 * @Author: 王占坤
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 10:33:58 +0800
 * @LastEditTime: 2022-05-02 19:12:22
 * @LastEditors: Please set LastEditors
 * @Description: 
 */
#ifndef __HEADER_H__
#define __HEADER_H__
//////////////C/C++//////////////
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>

//////////////Eign/////////////////
#include <eigen3/Eigen/Eigen>

//////////////OpenCV///////////////
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/core/eigen.hpp>

//////////////其他//////////////
#include "GxIAPI.h"
#include "DxImageProc.h"

using namespace cv;
using namespace std;

////////////////////define/////////////////////
// void GetErrorString(GX_STATUS error_status)
// {
//     char *error_info = NULL;
//     size_t size = 0;
//     GX_STATUS status = GX_STATUS_SUCCESS;

//     // 获取错误描述信息长度
//     status = GXGetLastError(&error_status, NULL, &size);
//     if (status != GX_STATUS_SUCCESS)
//     {
//         cout << "<GXGetLastError call fail>" << endl;
//         return;
//     }

//     error_info = new char[size];
//     if (error_info == NULL)
//     {
//         printf("<Failed to allocate memory>\n");
//         return;
//     }

//     // 获取错误信息描述
//     status = GXGetLastError(&error_status, error_info, &size);
//     if (status != GX_STATUS_SUCCESS)
//     {
//          cout << "<GXGetLastError call fail>" << endl;
//         return;
//     }
//     else
//     {
//         printf("%s\n", (char *)error_info);
//     }

//     // 释放资源
//     if (error_info != NULL)
//     {
//         delete[] error_info;
//         error_info = NULL;
//     }
// }
////////////////////typedef////////////////////

///////////////////自定义数据类型//////////////////

typedef struct CamConfigInfo
{
    int cam_index_in_vec;
    int64_t width;
    int64_t height;
    int offset_x;
    int offset_y;
    double expotime;
    int64_t gain;
    CamConfigInfo(int _camindex, int64_t _width, int64_t _height, int _offsetx, int _offsety, double _expotime, int64_t _gain)
                    : cam_index_in_vec(_camindex), width(_width), height(_height), offset_x(_offsetx), offset_y(_offsety), expotime(_expotime), gain(_gain)
                    {
                        
                    } 

    

}CamConfigInfo;


#endif
