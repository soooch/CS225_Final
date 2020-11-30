#include <math.h>
#include "FlighGraph.h"
#define _USE_MATH_DEFINES //Compatability for older systems
#define EARTH_RADIUS 6371
using namespace std;

double distance_weight(Airport c1, Airport c2){
    double lat1 = c1.latitude * M_PI/180; //Convert from degrees to radians for Trig functions
    double lat2 = c2.latitude * M_PI/180; 
    double deltaLat = (c2.latitude-c1.latitude) * M_PI/180; 
    double deltaLong = (c2.longitude-c1.longitude) * M_PI/180;
    
    double a = pow(sin(deltaLat/2), 2) + cos(lat1)*cos(lat2)*pow(sin(deltaLong/2), 2); //Calculating Haversine
    double b = 2 * atan2(sqrt(a), sqrt(1-a)); //Haversine Formula for Great Circle Distance
    return b * EARTH_RADIUS; //Multiplied by earth radius to get distance in kilometers
}

