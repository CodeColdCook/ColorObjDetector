# cam_detector
** 基于opencv的颜色物体实时识别

## 依赖项
** opencv
** jsoncpp（0.y.z分支）

### 编译
cd 013_cam_detec
catkin_make
source devel/setup.bash 
### 运行
* 调整 
	——/013_cam_detec/src/d_d/launch/cam_detec.launch中的参数
	json_add 为 RGB～RGB的参数初始化文件（）
	json_file_add 为 动态参数记录文件（动态参数调整界面的保存打勾即可实时保存）
	~image 为 订阅的视频/图像话题
* 运行
roslaunch d_d cam_detec.launch 
rosrun rqt_reconfigure rqt_reconfigure 
roslaunch usb_cam usb_cam-test.launch 