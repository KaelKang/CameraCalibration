/*
 * @Author: your name
 * @Date: 2022-03-12 10:29:06
 * @LastEditTime: 2022-03-27 21:58:07
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /ComputerVision/Share/Camera/include/GxCamera.h
 */
#ifndef __GX_CAMERA_H__
#define __GX_CAMERA_H__

#include "Camera.h"


class GxCamera : public Camera
{
private:
    GX_OPEN_PARAM open_param;
    GX_STATUS status;

    uint32_t camera_num;//记录共连接了几个相机
    int64_t m_pixel_color = 0; ///< Bayer格式
    bool g_get_image = false;  ///< 采集线程是否结束的标志：true 运行；false 退出
    Mat source_image_directly_from_camera;
    char *m_rgb_image = NULL;
    GX_FRAME_DATA g_frame_data = {0}; ///< 采集图像参数
    void* camera_handle = NULL; ///< 相机句柄

public:
    GX_DEVICE_BASE_INFO* m_device_base_info;
    GxCamera(string camera_name, 
                int64_t width,
                int64_t height,
                int offset_x,
                int offset_y ,
                double expotime,
                double gain);

private:
    void __init();
    /**
     * @brief 计数大恒工业相机的数量
     * @return -1，出错；否则返回值为大于等于0的自然数
    */
    int countNumberOfCameras();
    int openCamera();
    int setDeviceToContinuouslyAcquiredImage();
    int setTRiggerSwitchToOff();
    int setTRiggerSwitchToOn();
    int setORI();
    int mallocForSourceImage();
    int __config();
    int __start();
    int getDevieceId();


public:
    GxCamera(string camera_num);
    ~GxCamera();
    /**
     * @author: 王占坤
     * @description: 打开相机
     * @param: 
     * @return: -1无法打开，0打开成功
     * @throw: 
     */
    int open();

    Mat getFrame();
    int close();

    int changeCamConfig(const CamConfigInfo& info) override;

};


#endif