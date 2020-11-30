#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

class FlightGraph {
  private:
  struct Airport {
    std::string name, city, country;
  };

  public:
  FlightGraph(std::string airportsFilename, std::string routesFilename);
  
  private:
  std::unordered_map<int, std::vector<int>> routes;
  std::unordered_map<int, Airport> airports;
};