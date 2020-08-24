#include <tracker.h>

void Tracker::set_camera(Mat camera_matrix)
{
	//fx = camera_matrix(0,1);
	//fy = camera_matrix(1,1);
	//cx = camera_matrix(0,2);
	//cy = camera_matrix(1,2);
	/*
	cout << "Track is in set_camera1..." << endl;
	cout << camera_matrix << endl;
	fx = camera_matrix.at<double>(0,1);
	fy = camera_matrix.at<double>(1,1);
	cx = camera_matrix.at<double>(0,2);
	cy = camera_matrix.at<double>(1,2);
	*/
	fx = 901.7541988495958;
	fy = 899.7469627965778;
	cx = 486.1647201640165;
	cy = 271.5305991116423;
	cout << fx << endl;
	
	depth_scale = 1;
	cout << "Track is in set_camera..." << endl;
	pcamera = new Camera();
	pcamera->camera_init(fx, fy, cx, cy, depth_scale);
	cout << "camera is ok ..." << endl;
}

void Tracker::track(Point2f center, float r, float R) //, Point3f p_w
{
	double Z = R * fx / r;
	Vector2d p_p;
	p_p(0,0) = center.x;
	p_p(1,0) = center.y;
	Vector3d p_c = pcamera->pixel2camera(p_p, Z);
	p_w.x = p_c(0,0);
	p_w.y = p_c(1,0);
	p_w.z = p_c(2,0);
}