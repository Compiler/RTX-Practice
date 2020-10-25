#include "Camera.h"

Camera::Camera(){
    double aspect_ratio = 16.0 / 9.0;
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    _origin = Point3(0, 0, 0);
    _horizontal = Vec3(viewport_width, 0.0, 0.0);
    _vertical = Vec3(0.0, viewport_height, 0.0);
    _lowerLeftCorner = _origin - _horizontal/2 - _vertical/2 - Vec3(0, 0, focal_length);

}


Ray Camera::getRay(double u, double v){
    return Ray(_origin, _lowerLeftCorner  + _horizontal * u + _vertical * v - _origin);

}