#include "FlightGraph.h"
#include <math.h>
#include <queue>

template <class NodeData, class Route>
double distance_weight(const typename FlightGraph<NodeData, Route>::Airport & c1, const typename FlightGraph<NodeData, Route>::Airport & c2, const int stops, const std::string & equip) {
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

  class NodeData {
    public:
    bool visited;
    double dist;
    NodeData() : visited(false), dist(std::numeric_limits<double>::infinity()) {}
  };

  class Route
  {
    public:
    double weight;
    int dest;
    Route(const FlightGraph<NodeData, Route>::Airport & origin, const FlightGraph<NodeData, Route>::Airport & dest, int destID, int stops, const std::string & equip) : dest(destID) {
      weight = distance_weight<NodeData, Route>(origin, dest, stops, equip);
    }
  };

  FlightGraph<NodeData, Route> fg(airports);
  fg.addRoutes(routes);
  

  int originID = 1613; // Vienna International Airport
  int destID = 205; // Faro Airport

  std::queue<FlightGraph<NodeData, Route>::Airport&> priorityQueue;

  fg.airports[originID].data.dist = 0.0;
  priorityQueue.push(fg.airports[originID]);

  std::cout << fg.airports[originID].name << std::endl;
  for (const Route & route : fg.airports[originID].routes) {
    std::cout << fg.airports[route.dest].name << " is " << route.weight << " km away" << std::endl;
  }

  return 0;
}
