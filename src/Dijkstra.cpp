#include "FlightGraph.h"
#include <math.h>
using namespace std;

template <class Route>
double distance_weight(const typename FlightGraph<Route>::Airport & c1, const typename FlightGraph<Route>::Airport & c2, const int stops, const std::string & equip) {
    double lat1 = c1.latitude * M_PI/180; //Convert from degrees toradians for Trig functions
    double lat2 = c2.latitude * M_PI/180; 
    double deltaLat = (c2.latitude-c1.latitude) * M_PI/180; 
    double deltaLong = (c2.longitude-c1.longitude) * M_PI/180;
    
    double a = pow(sin(deltaLat/2), 2) + cos(lat1)*cos(lat2)*pow(sin(deltaLong/2), 2); //Calculating Haversine
    double b = 2 * atan2(sqrt(a), sqrt(1-a)); //Haversine Formula for Great Circle Distance
    return b * 6371; //Multiplied by earth radius to get distance in kilometers
}

int main(int argc, char * argv[]) {
  std::string airports = "data/airports.dat";
  std::string routes = "data/routes.dat";

  for (int i = 1; i < argc; i++) {
    if (std::string("-a").compare(argv[i]) == 0) {
      if (++i < argc) {
        airports = argv[i];
      }
    }
    else if (std::string("-r").compare(argv[i]) == 0) {
      if (++i < argc) {
        routes = argv[i];
      }
    }
  }

  std::cout << "Using " << airports << " for airports file and " << routes << " for routes file." << std::endl;

  class Route
  {
    public:
    double weight;
    int dest;
    bool visited;
    double dist;
    Route(const FlightGraph<Route>::Airport & origin, const FlightGraph<Route>::Airport & dest, int destID, int stops, const std::string & equip) : dest(destID), visited(false), dist(std::numeric_limits<double>::infinity()) {
      weight = distance_weight<Route>(origin, dest, stops, equip);
    }
  };

  FlightGraph<Route> fg(airports);
  fg.addRoutes(routes);
  

  int APID = 1613;
  std::cout << fg.airports[APID].name << std::endl;
  for (const Route & route : fg.airports[APID].routes) {
    std::cout << fg.airports[route.dest].name << " is " << route.weight << " km away" << std::endl;
  }

  return 0;
}
