"""
@Description : None
@Copied from : Henrychur
@Time : 2023/1/17 
"""
import cv2
import numpy as np
import glob

#recale images, otherwise it would take quite a long time 
def rescaleImg(img, scale=1):
    width = int(img.shape[1]*scale)
    height = int(img.shape[0]*scale)
    dimensions = (width, height)
    return cv2.resize(img, dimensions, interpolation=cv2.INTER_AREA)
# -------------------------------------------- #
# 设置寻找亚像素⻆点的参数
# 采⽤的停⽌准则是最⼤循环次数30和最⼤误差容限0.001
# -------------------------------------------- #
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001) # 阈值
# -------------------------------------------- #
# 棋盘格模板规格
# 代表⻓宽⻆点的个数，注意棋盘格的顶点不被算⼊其中
# -------------------------------------------- #
w = 8
h = 11
# -------------------------------------------- #
# 世界坐标系中的棋盘格点
# 例如(0,0,0), (1,0,0), (2,0,0) ....,(8,5,0)
# 去掉Z坐标，记为⼆维矩阵
# -------------------------------------------- #
objp = np.zeros((w*h,3), np.float32)
objp[:,:2] = np.mgrid[0:w,0:h].T.reshape(-1,2)
objp = objp*30.0 # 棋盘格每个ceil的边⻓ 18.1 mm //30.0mm
# -------------------------------------------- #
# 储存棋盘格⻆点的世界坐标和图像坐标对
# -------------------------------------------- #
objpoints = [] # 在世界坐标系中的三维点
imgpoints = [] # 在图像平⾯的⼆维点

# img = cv2.imread('/home/kael/Documents/pyfiles/calibration/chessImg/6cee87da3b667bf1056761e96f38d2d.jpg')
# # img = rescaleImg(img)
# gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# cv2.imshow('g', gray)
# cv2.waitKey(0)

images = glob.glob('./saveImg_k/*.png') # 图像路径
cnt = 0
i = 0
for fname in images:
    i += 1
    img = cv2.imread(fname)
    img = rescaleImg(img)
    # 获取画⾯中⼼点
    # 获取图像的⻓宽
    h1, w1 = img.shape[0], img.shape[1]
    # print(h1, w1) #t
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    print(gray.shape[0], gray.shape[1]) #t
    u, v = img.shape[:2]
    # 找到棋盘格⻆点
    ret, corners = cv2.findChessboardCorners(gray, (w,h),None)
    if ret ==True:
        print("-1")
    else:
        print("-0")
    # 如果找到⾜够点对，将其存储起来
    if ret == True:
        print("cnt: \t", cnt)
        cnt = cnt + 1
        # 在原⻆点的基础上寻找亚像素⻆点
        cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
        #追加进⼊世界三维点和平⾯⼆维点中
        objpoints.append(objp)
        imgpoints.append(corners)
        # 将⻆点在图像上显⽰
        cv2.drawChessboardCorners(img, (w,h), corners, ret)
        cv2.namedWindow('findCorners', cv2.WINDOW_NORMAL)
        cv2.resizeWindow('findCorners', 640, 480)
        cv2.imshow('findCorners',img)
        cv2.imwrite('./res_k/findCorners'+str(i)+'.png', img)
        cv2.waitKey(200)
        if cnt > 100:
        # 太多的图⽚会导致计算缓慢，所以最⼤计算100张图⽚的
            break
cv2.destroyAllWindows()
print('正在计算')
#标定
ret, mtx, dist, rvecs, tvecs = \
    cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
print("ret:",ret )
print("mtx:\n",mtx) # 内参数矩阵
print("dist畸变值:\n",dist) # 畸变系数 distortion cofficients = (k_1
print("rvecs旋转（向量）外参:\n",rvecs) # 旋转向量
print("tvecs平移（向量）外参:\n",tvecs) # 平移向量
newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (u, v), 0, (u, v))
print('newcameramtx外参',newcameramtx)

cv2.destroyAllWindows()
