
#include <Eigen/Core>
#include <Eigen/Geometry>
using Eigen::Vector2d;
using Eigen::Vector3d;

class Camera
{
public:
    float   fx_, fy_, cx_, cy_, depth_scale_;

    void camera_init ( float fx, float fy, float cx, float cy, float depth_scale );
    
    Vector2d camera2pixel( const Vector3d& p_c );
    Vector3d pixel2camera( const Vector2d& p_p, double depth=1 ); 

};

