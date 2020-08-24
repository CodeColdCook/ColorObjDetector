

// 1 像素点到空间点
// 2 恢复尺度

#include <iostream>
#include <opencv2/opencv.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>
using Eigen::Vector2d;
using Eigen::Vector3d;

#include <camera.h>

using namespace cv;
using namespace std;

class Tracker
{
public:
	Point3f p_w;
	void set_camera(Mat camera_matrix);
	void track(Point2f center, float r, float R); // , Point3f p_w
private:
	Camera* pcamera;
	float   fx, fy, cx, cy, depth_scale;
};