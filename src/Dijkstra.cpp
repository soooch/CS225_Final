#include "FlightGraph.h"
#include <math.h>
#include <queue>

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
  int originID = 3830; // Chicago O'Hare International Airport
  int destID = 3990; // Emerald Airport


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
    else if (std::string("-s").compare(argv[i]) == 0) {
      if (++i < argc) {
        originID = std::stoi(argv[i]);
      }
    }
    else if (std::string("-e").compare(argv[i]) == 0) {
      if (++i < argc) {
        destID = std::stoi(argv[i]);
      }
    }
  }

  std::cout << "Using " << airports << " for airports file and " << routes << " for routes file." << std::endl;

  class Route
  {
    public:
    double weight;
    int dest;
    Route(const FlightGraph<Route>::Airport & origin, const FlightGraph<Route>::Airport & dest, int destID, int stops, const std::string & equip) : dest(destID) {
      weight = distance_weight<Route>(origin, dest, stops, equip);
    }
  };

  FlightGraph<Route> fg(airports);
  fg.addRoutes(routes);
  
  std::cout << "Finding shortest path from " << fg.airports[originID].name << " to " << fg.airports[destID].name << std::endl;
  
  struct NodeData {
    bool visited;
    double dist;
    int prev;
    NodeData() : visited(false), dist(std::numeric_limits<double>::infinity()), prev(-1) {}
    bool operator<(const NodeData & rhs) const {
      return this->dist < rhs.dist;
    }
  };
  
  std::unordered_map<int, NodeData> nodes(fg.airports.size());
  for (const auto & [ID, Airport] : fg.airports) {
    nodes[ID] = NodeData();
  }

  auto cmp = [nodes](int lhs, int rhs){return nodes.at(rhs) < nodes.at(lhs);};
  std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

  nodes[originID].dist = 0.0;
  pq.push(originID);

  while (!pq.empty()) {
    const int ID = pq.top();
    NodeData & node = nodes[ID];
    pq.pop();

    if (ID == destID) break;
    if (node.visited) continue;

    for (const Route & route : fg.airports[ID].routes) {
      if (nodes[route.dest].visited) continue;
      const double altDist = node.dist + route.weight;
      if (altDist < nodes[route.dest].dist) {
        nodes[route.dest].dist = altDist;
        nodes[route.dest].prev = ID;
        pq.push(route.dest);
      }
    }
    node.visited = true;
  }

  if (nodes[destID].prev == -1) {
    std::cout << "No route found." << std::endl;
    return 0;
  }
  std::vector<int> path;
  for (int ID = destID; ID != -1; ID = nodes[ID].prev) {
    path.push_back(ID);
  }

  for (auto ID = path.rbegin(); ID != path.rend(); ++ID) {
    std::cout << fg.airports[*ID].name << " -> ";
  }
  std::cout << "\b\b\b\b    " << std::endl;

  return 0;
}
