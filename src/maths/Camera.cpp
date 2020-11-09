#include "Camera.h"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 verticalUp, double verticalFOV, double aspectRatio, double aperture, double focus_dist, double _time0, double _time1){
    double theta = degreesToRadians(verticalFOV);
    double h = tan(theta/2.0);
    double viewport_height = 2.0 * h;
    double viewport_width = aspectRatio * viewport_height;
    double focal_length = 1.0;

    _origin = Point3(0, 0, 0);
    _horizontal = Vec3(viewport_width, 0.0, 0.0);
    _vertical = Vec3(0.0, viewport_height, 0.0);
    _lowerLeftCorner = _origin - _horizontal/2 - _vertical/2 - Vec3(0, 0, focal_length);

    auto w = unit_vector(lookFrom - lookAt);
    auto u = unit_vector(cross(verticalUp, w));
    auto v = cross(w, u);

    _origin = lookFrom;
    _horizontal = viewport_width * u;
    _vertical = viewport_height * v;
    _lowerLeftCorner = _origin - _horizontal/2 - _vertical/2 - w;

    _horizontal = focus_dist * viewport_width * u;
    _vertical = focus_dist * viewport_height * v;
    _lowerLeftCorner = _origin - _horizontal/2 - _vertical/2 - focus_dist*w;

    _lensRadius = aperture / 2;
    _time0 = _time0;
    _time1 = _time1;
}


Ray Camera::getRay(double u, double v){
    Vec3 rd = _lensRadius * random_in_unit_disk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(_origin + offset, _lowerLeftCorner  + _horizontal * u + _vertical * v - offset, random_double(_time0, _time1));

}