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
	bool initialize(vector<int> &RGB_begin_, vector<int> &RGB_end_);
	void detect(Mat &frame);
	void adjust_colorRange(vector<int> &RGB_begin_new_, vector<int> &RGB_end_new_);
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
	Point2f center;
	float radius=20;
};