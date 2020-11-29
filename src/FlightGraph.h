#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

class FlightGraph {
  public:
  FlightGraph(std::string airportsFilename, std::string routesFilename);
  
  private:
  std::vector<std::vector<int>> routes;
  std::vector<std::string> airports;
};