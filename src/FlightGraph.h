#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

class FlightGraph {
  public:
  struct Airport {
    std::string name, city, country;
    double latitude, longitude;
    std::vector<std::pair<double, int>> routes;
  };

  FlightGraph(const std::string & airportsFilename);
  
  bool addRoutes(const std::string & routesFilename, 
    double (*weightFunc)(const Airport&, const Airport&, int, const std::string&));
  
  bool addRoutes(const std::string & routesFilename) {
    return addRoutes(routesFilename, 
      // default weight function just returns 0
      [](const FlightGraph::Airport & a1, const FlightGraph::Airport & a2, int stops, const std::string & equip){return 0.0;});
  }
  
  std::unordered_map<int, Airport> airports;
};
