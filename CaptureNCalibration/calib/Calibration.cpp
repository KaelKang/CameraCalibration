/*
 * @Copyright:
 * @author: Kael_Kang
 * @File name: Calibration
 * @Version: v1.0
 * @Date: 2023.5
 * @LastEditTime: 
 * @LastEditors: 
 * @description: 
 */
#include <iostream>
#include <dirent.h>

#include "../Camera/include/GxCamera.h"

/* ------- choose the chessboard configuration ------- */ 
const TermCriteria criteria = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.001 );

const int chess_w = 8;
const int chess_h = 11;
const int cell_w = 30;
const int cell_h = 30;

const string read_path = "/home/rm/Desktop/CaptureNCalibration/saveImg_k";
const string show_res_path = read_path + "/../res_k";
/* ------- end setting the chessboard configuration ------- */ 

// ------- define containers ---------
vector<Point3f > board;

vector<vector<Point3f > > obj_points;
vector<vector<Point2f > > img_points;

vector<string > paths;

// ---------- set template of one chessboard cell ----------
void setBoard(vector<Point3f >& board, int chess_w, int chess_h ){
    for(int i = 0; i < chess_h; i++ ){
        for(int j = 0; j < chess_w; j++ ){
            Point3f pt;
            pt.x = i * cell_w;
            pt.y = j * cell_h;
            pt.z = 0;
            board.push_back(pt);
        }
    }

    return;
}

// ---------- extract files names from a directory ------------
vector<string > getFileNames(const string& dir_name, bool is_subdir = false ){
    DIR* dir_entry;
    struct dirent* dir_path;
    vector<string > file_names;

    if((dir_entry = opendir(dir_name.c_str() ) ) != NULL ){
        while((dir_path = readdir(dir_entry ) ) != NULL ){
            // cout <<  dir_path->d_name <<endl;
            if(strcmp(".", dir_path->d_name ) == 0 || strcmp("..", dir_path->d_name ) == 0 ){
                continue;
            }
            if(dir_path->d_type != DT_DIR ){
                file_names.push_back(dir_name + "/" +dir_path->d_name );
            }
            if(is_subdir && dir_path->d_type == DT_DIR ){
                vector<string > sub_file_names = getFileNames(dir_name + "/" + dir_path->d_name, true );
                file_names.insert(file_names.begin(), sub_file_names.begin(), sub_file_names.end() );
            }
        }
    }
    
    closedir(dir_entry);

    return file_names;
}

int main(){
// -- set necessities -- 
    paths = getFileNames(read_path );
    setBoard(board, chess_w, chess_h );
 
// -- define counters --
    uint cnt = 0;
    uint i = 0;

// -- the size of chessboard images is expected to be identical --
    int img_w;
    int img_h;

// -- calibrating circular -- 
    for(string& path : paths ){
        // cout << path <<endl;
        i++;
        Mat img = imread(path);

        img_w = img.size().width;
        img_h = img.size().height;
        Mat gray;

        cvtColor(img, gray, COLOR_BGR2GRAY );

// -- show each gray image --                    
        // imshow("gray iamge", gray);
        // waitKey(0);
        // if(gray.type()==CV_8UC1 ){
        //     cout << gray.channels() << endl;
        // }

// -- find corners and sub pixels -- 
        vector<Point2f > corners;
        bool ret = findChessboardCorners(
            gray, Size(chess_w, chess_h ), corners , CALIB_CB_ADAPTIVE_THRESH  | CALIB_CB_NORMALIZE_IMAGE 
        );
 
        cout << "is_find - " << ret << endl;

        if(ret ){
            cout << cnt << endl;
            cnt++;

            cornerSubPix(gray, corners, Size(11,  11 ), Size(-1, -1 ), criteria );

            obj_points.push_back(board );
            img_points.push_back(corners );

// -- draw corners -- 
            drawChessboardCorners(img, Size(chess_w, chess_h ), corners, ret );
            // namedWindow("findCorners ", WINDOW_NORMAL );
            // resizeWindow("findCorners ", 640, 480 );

            imshow("findCorners ", img );
            imwrite(show_res_path + "/findCorners_" + to_string(cnt ) + ".png", img );

            waitKey(40);

// -- don't be too many --
            if(cnt > 100 ){
                break;
            }
        }
    }

    destroyAllWindows();

// get final matrix and distcoeffs --
    cout << "Calculating ... ... " << endl;

    Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar(0, 0, 0 ) );
    Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar(0, 0, 0 ) );
    vector<Mat> rvecsMat;
    vector<Mat> tvecsMat;
    double _err = calibrateCamera(
        obj_points, img_points, Size(img_w, img_h ), cameraMatrix, distCoeffs, rvecsMat, tvecsMat //, CV_CALIB_FIX_K3 
    );

// -- copy coeffs into pnp yaml -- 
    cout << cameraMatrix << endl;
    cout << distCoeffs << endl;
     
    return 0;
}







