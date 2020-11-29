#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

class FlightGraph {
  public:
  FlightGraph();
  //FlightGraph(std::string airportsFilename);
  //FlightGraph(std::string airportsFilename, std::string routesFilename);
  
  private:
  std::vector<std::vector<int>> routes;
  std::vector<std::string> airports;
};