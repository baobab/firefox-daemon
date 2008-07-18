#ifndef TNMATH_H

#   define TNMATH_H

#   include "tnos/tnos.h"

#   ifdef __cplusplus
        extern "C" {
#   endif

#   define TN_PI            3.14159265358979323846

#   define tndeg2rad(d)     ((TN_PI/180.0)*d)
#   define tnrad2deg(d)     ((180.0/TN_PI)*d)

    extern double great_circle_distance(double lat1,
                                        double lon1,
                                        double lat2,
                                        double lon2);

    extern double great_circle_distance_b(double lat1,
                                          double lon1,
                                          double lat2,
                                          double lon2);

    extern double great_circle_course(double lat1,
                                      double lon1,
                                      double lat2,
                                      double lon2);

                                        

#   ifdef __cplusplus
        }
#   endif

#endif

