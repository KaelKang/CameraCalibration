"""
@Description :   调用大恒相机API采集照片并保存
@Author      :   kael
@Time        :   2023/3/26 16:44:39
"""
import gxipy as gx
import cv2 as cv

def main():
    print("")
    print("Initializing......")
    print("")

    #savepath
    save_path = "./saveImg_k/"
    numOfPicture = 0
     
    # 创建设备管理器
    device_manager = gx.DeviceManager()
    dev_num, dev_info_list = device_manager.update_device_list()
    # if dev_num is 0:
    if dev_num == 0:    
        print("Number of enumerated devices is 0")
        return

    # 打开设备，创建设备句柄
    cam = device_manager.open_device_by_index(1)

    # 连续触发模式
    cam.TriggerMode.set(gx.GxSwitchEntry.OFF)

    # 设置曝光
    cam.ExposureTime.set(9000.0)

    # 设置自动白平衡
    cam.BalanceWhiteAuto.set(1)

    # 设置增益
    cam.Gain.set(22.0)

    # 设置图像增强
    if cam.GammaParam.is_readable():
        gamma_value = cam.GammaParam.get()
        gamma_lut = gx.Utility.get_gamma_lut(gamma_value)
    else:
        gamma_lut = None
    if cam.ContrastParam.is_readable():
        contrast_value = cam.ContrastParam.get()
        contrast_lut = gx.Utility.get_contrast_lut(contrast_value)
    else:
        contrast_lut = None
    if cam.ColorCorrectionParam.is_readable():
        color_correction_param = cam.ColorCorrectionParam.get()
    else:
        color_correction_param = 0

    #### set resolution
    cam.Width.set(1280)
    cam.Height.set(1024)
    # cam.Width.set(660)
    # cam.Height.set(104)

    # 启动相机，开始捕捉
    cam.stream_on()

    img_num = 100000
    for i in range(img_num):
        # 获取原始图像
        raw_image = cam.data_stream[0].get_image()
        if raw_image is None:
            print("Getting image failed.")
            continue

        # 获取RGB图像
        rgb_image = raw_image.convert("RGB")
        if rgb_image is None:
            continue

        # 图像增强
        rgb_image.image_improvement(color_correction_param, contrast_lut, gamma_lut)

        # 将图像转化为rgb的numpy
        rgb = rgb_image.get_numpy_array()
        if rgb is None:
            continue

        # 将图像转化为bgr的numpy
        bgr = rgb[..., ::-1]
        # ----------------------start do something here--------------------- #
        cv.imshow("src", bgr)
  
        keyvalue = cv.waitKey(40)

        if(keyvalue == ord('r')):
            cv.imwrite(save_path + str(numOfPicture) + '.png', bgr)
            numOfPicture += 1
            print(numOfPicture)

        if(numOfPicture >= 100):
             cam.stream_off()
             cam.close_device()

        # ----------------------end do something here--------------------- #

    # cam.stream_off()
    # cam.close_device()

if __name__ == "__main__":
    main()
