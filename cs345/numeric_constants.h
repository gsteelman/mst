#ifndef NUMERIC_CONSTANTS_H
#define NUMERIC_CONSTANTS_H

#define _PI 3.14159265358979323846264338327950288419716939937
#define _E  2.71828183

#define _DEG_PER_CIRCLE 360.0
#define _RAD_PER_CIRCLE (2.0 * _PI)

#define _RAD_PER_DEG (_PI / 180.0)
#define _DEG_PER_RAD (180.0 / _PI)
#define DegToRad( a ) a * _RAD_PER_DEG
#define RadToDeg( a ) a * _DEG_PER_RAD

#endif
