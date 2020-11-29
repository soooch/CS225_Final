#include "FlightGraph.h"
#include <iostream>

int main(int argc, char * argv[]) {
  // TODO: use argument, check for correct syntax
  std::string airports = "data/airports_sample.dat";
  std::string routes = "data/routes_sample.dat";
  
  FlightGraph fg(airports, routes);

  return 0;
}