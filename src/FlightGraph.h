#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <functional>

class FlightGraph {
  public:
  struct Airport {
    std::string name, city, country;
    double latitude, longitude;
    std::vector<std::pair<double, int>> routes;
  };

  FlightGraph(std::string airportsFilename);
  
  bool addRoutes(std::string routesFilename, const std::function <double(const Airport&, const Airport&, int, const std::string&)> = [](Airport a, Airport b, int stops, std::string equip){return 1.0;});
  
  std::unordered_map<int, Airport> airports;
};
