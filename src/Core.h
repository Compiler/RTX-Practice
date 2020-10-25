#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>


// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
constexpr double _INFINITY_ = std::numeric_limits<double>::infinity();
constexpr double _PI_ = 3.1415926535897932385;

// Utility Functions
inline double degreesToRadians(double degrees) {
    return degrees * _PI_ / 180.0;
}

// Common Headers
#include <maths/Ray.h>
#include <maths/Vec3.h>

#endif