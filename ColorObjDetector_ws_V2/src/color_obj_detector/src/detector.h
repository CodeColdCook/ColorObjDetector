#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

class Detector
{
public:
	bool detect_finished;
	bool change_colorRange;
	bool initialize(string camera_matrix_add, vector<int> &RGB_begin_, vector<int> &RGB_end_, Mat camera_matrix_out);
	void detect(Mat &frame, Mat frame_undist, Point2f obj_center, float obj_radius);
	void adjust_colorRange(vector<int> &RGB_begin_new_, vector<int> &RGB_end_new_);

	Point2f center;
	float radius=20;
private:
	vector<int> RGB_begin;
	vector<int> RGB_end;
	vector<int> RGB_begin_new;
	vector<int> RGB_end_new;
	VideoCapture capture;
	Mat dst;
	Mat kernel;
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	Rect rect;
	

	Mat camera_matrix, dist_coeffs;
};