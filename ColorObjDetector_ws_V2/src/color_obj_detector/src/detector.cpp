#include <detector.h>

bool Detector::initialize(string camera_matrix_add, vector<int> &RGB_begin_, vector<int> &RGB_end_, Mat camera_matrix_out)
{
	RGB_begin = RGB_begin_;
	RGB_end = RGB_end_;
	change_colorRange = false;
	detect_finished = false;
	kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	FileStorage fs(camera_matrix_add, cv::FileStorage::READ);
    fs["camera_matrix"] >> camera_matrix;
    fs["distortion_coefficients"] >> dist_coeffs;
    if(!fs.isOpened())
    {
        cout << "camera_matrix file is wrong..." << endl;
        return false;
    }
    cout << "camera_matrix\n" << camera_matrix << endl;
    cout << "\ndist coeffs\n" << dist_coeffs << endl;
    camera_matrix_out = camera_matrix.clone();


	return true;
}

void Detector::adjust_colorRange(vector<int> &RGB_begin_new_, vector<int> &RGB_end_new_)
{
	change_colorRange = true;
	RGB_begin_new = RGB_begin_new_;
	RGB_end_new = RGB_end_new_;
}

void Detector::detect(Mat &frame_dist, Mat frame_undist, Point2f obj_center, float obj_radius)
{
	if (frame_dist.empty()) 
    {
        cout << "frame has something wrong " << endl;
    }
    Mat map1, map2, frame;
    Size imageSize = frame_dist.size();

    //initUndistortRectifyMap(camera_matrix, dist_coeffs, Mat(),
	//	getOptimalNewCameraMatrix(camera_matrix, dist_coeffs, imageSize, 1, imageSize, 0),
	//	imageSize, CV_16SC2, map1, map2);
    //remap(frame_dist, frame_undist, map1, map2, INTER_LINEAR);
    //frame_undist.copyTo(frame);
    frame_dist.copyTo(frame);
    frame_dist.copyTo(frame_undist);

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
	{
		circle(frame, Point(center.x,center.y), (int)radius, Scalar(0,255,0), 2);
		obj_center = center;
		obj_radius = radius;
	}
	imshow("input", frame);
	imshow("output", dst);

	//waitKey(150);

}