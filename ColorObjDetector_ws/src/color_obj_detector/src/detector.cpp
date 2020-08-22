#include <detector.h>

bool Detector::initialize(vector<int> &RGB_begin_, vector<int> &RGB_end_)
{
	RGB_begin = RGB_begin_;
	RGB_end = RGB_end_;
	change_colorRange = false;
	detect_finished = false;
	kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	return true;
}

void Detector::adjust_colorRange(vector<int> &RGB_begin_new_, vector<int> &RGB_end_new_)
{
	change_colorRange = true;
	RGB_begin_new = RGB_begin_new_;
	RGB_end_new = RGB_end_new_;
}

void Detector::detect(Mat &frame)
{
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("output", CV_WINDOW_AUTOSIZE);	
	if(change_colorRange)
	{
		RGB_begin = RGB_begin_new;
		RGB_end = RGB_end_new;
		change_colorRange = false;
	}
	inRange(frame, Scalar(RGB_begin[0],RGB_begin[1],RGB_begin[2]), Scalar(RGB_end[0],RGB_end[1],RGB_end[2]), dst);
	morphologyEx(dst,dst,MORPH_OPEN,kernel);
	morphologyEx(dst,dst,MORPH_OPEN,kernel);
	findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0,0));
	if (contours.size() > 0)
	{
		double maxArea=0;
		for (int i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area > maxArea)
			{
				maxArea = area;
				rect = boundingRect(contours[i]);
				minEnclosingCircle(contours[i], center, radius);
			}
		}
	}

	if((int)radius > 10)
		circle(frame, Point(center.x,center.y), (int)radius, Scalar(0,255,0), 2);
	imshow("input", frame);
	imshow("output", dst);

	//waitKey(150);

}