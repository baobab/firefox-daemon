#include "tnclib/tncmath.h"
#include <math.h>

double tnsqr(double a)
{
    return(a*a);
}

double great_circle_distance(double lat1,double lon1,double lat2,double lon2)
{
    double distance;

    distance=2*asin(sqrt(tnsqr(sin((lat1-lat2)/2)) + 
                 cos(lat1)*cos(lat2)*tnsqr(sin((lon1-lon2)/2))));
    return(distance*6371.0);
}

double great_circle_distance_b(double lat1,double lon1,double lat2,double lon2)
{
    double distance;

    distance=acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2));
    return(distance*6371.0);
}

double great_circle_course(double lat1,double lon1,double lat2,double lon2)
{
/*
    double d=2*asin(sqrt(tnsqr(sin((lat1-lat2)/2)) + 
                 cos(lat1)*cos(lat2)*tnsqr(sin((lon1-lon2)/2))));
    return(sin(lon2-lon1)<0.0
        ?acos((sin(lat2)-sin(lat1)*cos(d))/(sin(d)*cos(lat1)))
        :(2*TN_PI)-acos((sin(lat2)-sin(lat1)*cos(d))/(sin(d)*cos(lat1))));
*/
    double y=sin(lon1-lon2)*cos(lat2);
    double x=cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lon1-lon2);

    x=atan2(y,x);
    return(fmod((2*TN_PI)-x,2*TN_PI));
}


