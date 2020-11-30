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
    std::vector<int> routes;
  };

  FlightGraph(std::string airportsFilename, std::string routesFilename);
  
  std::unordered_map<int, Airport> airports;
};
