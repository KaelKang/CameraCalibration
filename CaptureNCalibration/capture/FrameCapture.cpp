/*
 * @Copyright:
 * @author: 
 * @File name: Calibration
 * @Version: v1.0
 * @Date: 2023.5
 * @LastEditTime: 
 * @LastEditors: 
 * @description: 
 */
#include <iostream>

#include "../Camera/include/GxCamera.h"

int main(){
    const std::string save_path = "/home/rm/Desktop/CaptureNCalibration/saveImg_k/";
    int numOfPicture = 0;
    int key_value;
    const long long total = 60;

    cv::Mat p_source;
    GxCamera cam("1", 1280, 1024, 0, 0, 9000, 16);
    // if(!(cam.open() == 0 ) ){
    //     std::cout << "Camera open failed." << std::endl;
    // }
    // cam.close();
    if(!(cam.open() == 0 ) ){
        std::cout << "Camera open failed." << std::endl;
        
        return 0;
    }

    std::cout << "cam open success" << std::endl;



    while(true ){
        Camera& camera = cam;

        p_source = camera.getFrame();

        cv::imshow("rsc", p_source);
        // waitKey(1);

        key_value = cv::waitKey(40);
        // cout << "keyin:" << key_value << endl;

// -- ascii of "r" is 114 -- 
        if(key_value == 114 ){
            cout << "num:" << numOfPicture << endl;
            numOfPicture++;
            bool check  = cv::imwrite(save_path + std::to_string(numOfPicture) + ".png", p_source);
            // cout << "check " << check <<endl;
        }

        if(numOfPicture >= total ){
            cout << "break:" << numOfPicture << endl;

            break;
        }
    }

    cout << "ok " << endl;
    cam.close();

    return 0;
}