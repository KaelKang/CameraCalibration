/*
 * @Copyright: CS of BIT
 * @author: 王占坤
 * @File name: 
 * @Version: 
 * @Date: 2019-09-27 19:54:06 +0800
 * @LastEditTime: 2022-05-17 20:07:26
 * @LastEditors: song 578875856@qq.com
 * @description: 
 */
#include "GxCamera.h"

void GetErrorString(GX_STATUS error_status){
    char *error_info = NULL;
    size_t size = 0;
    GX_STATUS status = GX_STATUS_SUCCESS;

    // 获取错误描述信息长度
    status = GXGetLastError(&error_status, NULL, &size);
    if (status != GX_STATUS_SUCCESS)
    {
        cout << "<GXGetLastError call fail>" << endl;
        return;
    }

    error_info = new char[size];
    if (error_info == NULL)
    {
        printf("<Failed to allocate memory>\n");
        return;
    }

    // 获取错误信息描述
    status = GXGetLastError(&error_status, error_info, &size);
    if (status != GX_STATUS_SUCCESS)
    {
        cout << "<GXGetLastError call fail>" << endl;
        return;
    }
    else
    {
        printf("%s\n", (char *)error_info);
    }

    // 释放资源
    if (error_info != NULL)
    {
        delete[] error_info;
        error_info = NULL;
    }
}


GxCamera::GxCamera(string no_cam) : Camera(no_cam)
{
}

GxCamera::GxCamera(string no_cam, 
                int64_t width,
                int64_t height,
                int offset_x,
                int offset_y ,
                double expotime,
                double gain) : Camera(no_cam)
{
    configFrame(width, height, offset_x, offset_y, expotime, gain);
}

GxCamera::~GxCamera()
{
    if(is_opened)
        this->close();
    free(g_frame_data.pImgBuf);
    // free(open_param.pszContent);
}

inline
void GxCamera::__init()
{
    this->camera_handle = nullptr;

    //初始化库
    status = GXInitLib();
    if(status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
    }
    this->is_opened = false;
    cout << "GxCamera::GxCamera Successfully" << endl;
}

inline
int GxCamera::open()
{
    __init();

    cout << "GxCamera::open" << endl;
    camera_num = countNumberOfCameras();
    if (camera_num == -1)
        return -1;
    
    cout << "GxCamera::countNumberOfCameras  Successful\n" << "number of cameras: " << camera_num << endl;
    if (camera_num <= 0)
    {
        printf("<No device>\n");
        status = GXCloseLib();
        cout << "<Closed Device>" << endl;
        return -1;
    }

    this->m_device_base_info = new GX_DEVICE_BASE_INFO[this->camera_num];
    size_t tmp_size = this->camera_num * sizeof(GX_DEVICE_BASE_INFO);
    // Get all device baseinfo
    status = GXGetAllDeviceBaseInfo(this->m_device_base_info, &tmp_size);

    if (openCamera() == -1)
        return -1;



    if(getDevieceId() == -1)
        return -1;
    

    if(__config() == -1)
        return -1;

    if (setDeviceToContinuouslyAcquiredImage() == -1)
        return -1;
        
    #ifdef USE_TRIGGER
    if (setTRiggerSwitchToOn() == -1)
        return -1;
    #else
    if (setTRiggerSwitchToOff() == -1)
        return -1;
    #endif

    __start();
    return 0;
}
inline
int GxCamera::getDevieceId()
{
    size_t nSize = 0;
    //首 先 获 取 字 符 串 允 许 的 最 大 长 度(此 长 度 包 含 结 束 符 ’\0’)
    status = GXGetStringMaxLength(this->camera_handle, GX_STRING_DEVICE_VENDOR_NAME, &nSize);
    //根 据 获 取 的 长 度 申 请 内 存
    char *pszText = new char[nSize];
    status = GXGetString(this->camera_handle, GX_STRING_DEVICE_SERIAL_NUMBER, pszText, &nSize);
    if(status!=GX_STATUS_SUCCESS)
        return -1;
    this->device_id =string(pszText);

    cout<<"device_id="<<device_id<<endl;

    return 0;
}
inline
int GxCamera::__config()
{
    setORI();

    cout << "width = " << m_roi_width << '\t' << "height = " << m_roi_height << endl;
    cout << "expotime = " << m_exposure_time << '\t' << "gain = " << m_gain << endl;
    // 查询当前相机是否支持GX_ENUM_PIXEL_COLOR_FILTER
    status = GXIsImplemented(camera_handle, GX_ENUM_PIXEL_COLOR_FILTER, &is_colorful);
    //支持彩色图像
    if (is_colorful)
    {
        cout << "GxCamera::configFrame    支持彩色" << endl;
        status = GXGetEnum(camera_handle, GX_ENUM_PIXEL_COLOR_FILTER, &m_pixel_color);
        source_image_directly_from_camera.create(m_roi_height, m_roi_width, CV_8UC3);
        m_rgb_image = new char[m_roi_height * m_roi_width * 3];
    }
    else
    {
        cout << "GxCamera::configFrame    不支持彩色" << endl;
        source_image_directly_from_camera.create(m_roi_height, m_roi_width, CV_8UC1);
    }

    int ret = mallocForSourceImage();

    if (ret != 0)
    {
        printf("<Failed to prepare for acquire image>\n");
        status = GXCloseDevice(camera_handle);
        if (camera_handle != NULL)
        {
            camera_handle = NULL;
        }
        status = GXCloseLib();
        return -1;
    }
    return 0;
}


/**
     * @author: 王占坤
     * @description: 关闭相机
     * @param: 
     * @return: 
     * @throw: 
     */
inline int GxCamera::close()
{
    is_opened = false;
    //为停止采集做准备
    GX_STATUS status = GX_STATUS_SUCCESS;
    // uint32_t ret = 0;

    //发送停采命令
    status = GXSendCommand(camera_handle, GX_COMMAND_ACQUISITION_STOP);
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        return status;
    }

    //关闭设备
    status = GXCloseDevice(camera_handle);
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        if (camera_handle != NULL)
        {
            camera_handle = NULL;
        }
        status = GXCloseLib();
        return 0;
    }
    //释放库
    else
        status = GXCloseLib();

    return 0;
}

/**
     * @author: 王占坤
     * @description: 向相机发送开始获取图像命令
     * @param: 
     * @return: 
     * @throw: 
     */
int GxCamera::__start()
{
    cout << "GxCamera::start    GxCamera_handle:  " << camera_handle << endl;

        cout << "expotime = " << m_exposure_time << '\t' << "gain = " << m_gain << endl;

    status = GXSendCommand(camera_handle, GX_COMMAND_ACQUISITION_START);
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        return -1;
    }
    cout << "GxCamera::start    Success to start camera" << endl;

    return 0;
}

/**
     * @author: 王占坤
     * @description: 获取图像
     * @param: 
     * @return: Mat
     * @throw: 
     */
inline Mat GxCamera::getFrame()
{
    // cout << "GxCamera::getFrame Enter" << endl;

    if (g_frame_data.pImgBuf == NULL)
    {
        cout << "GxCamera::getFrame g_frame_data.pImgBuf == NULL" << endl;
    }
    status = GXGetImage(camera_handle, &g_frame_data, 10000);
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        exit(0);
    }
    else
    {
        if (g_frame_data.nStatus == GX_FRAME_STATUS_SUCCESS)
        {
            // printf("<Successful acquisition : Width: %d Height: %d >\n", g_frame_data.nWidth, g_frame_data.nHeight);
            if (is_colorful)
            {
                Mat tmp(m_roi_height, m_roi_width, CV_8UC3);
                DxRaw8toRGB24(g_frame_data.pImgBuf, tmp.data, g_frame_data.nWidth, g_frame_data.nHeight,
                              RAW2RGB_NEIGHBOUR, DX_PIXEL_COLOR_FILTER(BAYERBG), false);
                source_image_directly_from_camera = tmp;
            }
            else
            {
                Mat tmp(m_roi_height, m_roi_width, CV_8UC1);
                memcpy(tmp.data, g_frame_data.pImgBuf, g_frame_data.nHeight * g_frame_data.nWidth);
                source_image_directly_from_camera = tmp;
            }
        }
    }

    return source_image_directly_from_camera;
}

inline
int GxCamera::countNumberOfCameras()
{
    //获取枚举设备个数
    status = GXUpdateDeviceList(&camera_num, 1000);//最后一个参数是超时时间
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        status = GXCloseLib();
        return -1;
    }
    return camera_num;
}

inline
int GxCamera::openCamera()
{
    status = GXOpenDeviceByIndex(std::stoi(this->cam_name), &this->camera_handle);
    cout << "GxCamera::openCamera   camera_handle: " << camera_handle << endl;
    GetErrorString(status);
    if (status != GX_STATUS_SUCCESS)
    {
        printf("GxCamera::openCamera    Failed to open camera.\n");
        status = GXCloseLib();
        return -1;
    }
    else
    {
        printf("GxCamera::openCamera    Success to open camera.\n");
    }
    this->is_opened = true;
    return 0;
}


/**
 * @author: 王占坤
 * @description: 设置采集模式为连续采集
 * @param: 
 * @return: 
 * @throw: 
 */
inline int GxCamera::setDeviceToContinuouslyAcquiredImage()
{
    //设置采集模式为连续采集
    status = GXSetEnum(camera_handle, GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
    // status = GXSetEnum(camera_handle, GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_SINGLE_FRAME);
    if (status != GX_STATUS_SUCCESS)
    {
        cout << "here" << endl;
        close();
        return -1;
    }
    return 0;
}

inline int GxCamera::setTRiggerSwitchToOff()
{
    //设置触发开关为OFF
    status = GXSetEnum(camera_handle, GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_OFF);
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        status = GXCloseDevice(camera_handle);
        if (camera_handle != NULL)
        {
            camera_handle = NULL;
        }
        status = GXCloseLib();
        return -1;
    }

    return 0;
}

inline int GxCamera::setTRiggerSwitchToOn()
{
    //设置触发开关为ON
    status = GXSetEnum(camera_handle, GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON);
    // auto ss = GXSetFloat(camera_handle,GX_FLOAT_TRIGGER_DELAY,5);
    GXSetEnum(camera_handle,GX_ENUM_TRIGGER_SOURCE,GX_TRIGGER_SOURCE_LINE3);
    // cout << ss<<endl;
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        status = GXCloseDevice(camera_handle);
        if (camera_handle != NULL)
        {
            camera_handle = NULL;
        }
        status = GXCloseLib();
        return -1;
    }

    return 0;
}

/**
 * @author: 王占坤
 * @description: 设置感兴趣区域
 * @param: 
 * @return: 
 * @throw: 
 */
inline int GxCamera::setORI()
{
    //设置roi区域，设置时相机必须时停采状态
    status = GXSetInt(camera_handle, GX_INT_WIDTH, m_roi_width);
    status = GXSetInt(camera_handle, GX_INT_HEIGHT, m_roi_height);
    status = GXSetInt(camera_handle, GX_INT_OFFSET_X, m_roi_offset_x);
    status = GXSetInt(camera_handle, GX_INT_OFFSET_Y, m_roi_offset_y);
    status = GXSetEnum(camera_handle,GX_ENUM_BALANCE_WHITE_AUTO, GX_BALANCE_WHITE_AUTO_CONTINUOUS);
    status = GXSetFloat(camera_handle, GX_FLOAT_EXPOSURE_TIME, m_exposure_time);
    status = GXSetFloat(camera_handle, GX_FLOAT_GAIN, m_gain);
    return 0;
}


inline int GxCamera::mallocForSourceImage()
{
    GX_STATUS status = GX_STATUS_SUCCESS;
    int64_t payload_size = 0;

    status = GXGetInt(camera_handle, GX_INT_PAYLOAD_SIZE, &payload_size);
    cout << "payload_size = " << payload_size << endl;
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        return status;
    }

    g_frame_data.pImgBuf = malloc(payload_size);
    if (g_frame_data.pImgBuf == NULL)
    {
        printf("<Failed to allot memory>\n");
        return 0;
    }

    return 0;
}

int GxCamera::changeCamConfig(const CamConfigInfo& info)
{
    is_opened = false;
    GX_STATUS status = GX_STATUS_SUCCESS;

    //发送停采命令
    status = GXSendCommand(camera_handle, GX_COMMAND_ACQUISITION_STOP);
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        return status;
    } 

    configFrame(
        info.width,
        info.height,
        info.offset_x,
        info.offset_y,
        info.expotime,
        info.gain
    );
    setORI();

    status = __start();
    if (status != GX_STATUS_SUCCESS)
    {
        GetErrorString(status);
        return status;
    } 

    is_opened = true;
    return status;
}

