#include "camera.h"

Vector2d Camera::camera2pixel ( const Vector3d& p_c )
{
    return Vector2d (
               fx_ * p_c ( 0,0 ) / p_c ( 2,0 ) + cx_,
               fy_ * p_c ( 1,0 ) / p_c ( 2,0 ) + cy_
           );
}

Vector3d Camera::pixel2camera ( const Vector2d& p_p, double depth )
{
    return Vector3d (
               ( p_p ( 0,0 )-cx_ ) *depth/fx_,
               ( p_p ( 1,0 )-cy_ ) *depth/fy_,
               depth
           );
}

void Camera::camera_init ( float fx, float fy, float cx, float cy, float depth_scale )
{
  fx_ = fx;
  fy_ = fy;
  cx_ = cx;
  cy_ = cy;
  depth_scale_ = depth_scale;
}

