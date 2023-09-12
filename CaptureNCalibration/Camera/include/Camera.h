/*
 * @Copyright: CS of BIT
 * @author: 王占坤
 * @File name: 
 * @Version: 
 * @Date: 2019-09-27 19:52:54 +0800
 * @LastEditTime: 2021-04-02 07:20:15
 * @LastEditors: Please set LastEditors
 * @description: 
 */
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "header.h"
// #include "GxIAPI.h"

class Camera
{
protected:
    string cam_name;
    int64_t m_roi_width;       ///< 感兴趣区域宽
    int64_t m_roi_height;      ///< 感兴趣区域高
    int64_t m_roi_offset_x;      ///< 水平偏移量设置     //8 //320
    int64_t m_roi_offset_y;      ///< 竖直偏移量设置     //6 //272
    double m_exposure_time; ///< 曝光时间     识别数字时为2000
    int64_t m_gain;            ///< 增益       识别数字时为850,分区赛用的500，复活赛用的200
    bool is_colorful;          //是否支持彩色
    bool is_opened;
    string device_id;//相机标识, 工业相机是设备号，虚拟相机可以以文件名作为标识


public:
    Camera(string camera_name):cam_name(camera_name), is_opened(false){}
    ~Camera(){}

protected:
    /**
     * @author: 王占坤
     * @description: 对相机的每一帧图像进行配置
     * @param: int64_t width  图像横向大小
     * @param: int54_t height 图像纵向大小
     * @param: int offset_x 截取图像的偏置
     * @param: int offset_y  截取图像的偏置
     * @param: double expotime 曝光时间
     * @param: int64_t gain
     * @return: void
     */

public:
    inline void configFrame(int64_t width,
                    int64_t height,
                    int offset_x,
                    int offset_y ,
                    double expotime,
                    int64_t gain)
    {
        m_roi_width = width;
        m_roi_height = height;
        m_roi_offset_x = offset_x;
        m_roi_offset_y = offset_y;
        m_exposure_time = expotime;
        m_gain = gain;
        return;
    }
    virtual int open() = 0;//打开相机

    virtual int close() = 0;//关闭相机
    
    virtual Mat getFrame() = 0;//获取相机图片

    inline bool isOpen() const
    {
        return is_opened;
    }
    virtual inline string cameraID() const
    {
        return device_id;
    }

    virtual int changeCamConfig(const CamConfigInfo& info) {return 0;}
};

#endif