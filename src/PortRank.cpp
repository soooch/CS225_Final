#include "FlightGraph.h"
#include <iostream>

int main(int argc, char * argv[]) {
  // TODO: use argument, check for correct syntax
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
  
  FlightGraph fg(airports, routes);
  
  // outputs a full list of routes to stdout in form:
  // Example Airport has routes to:
  // Airport of Example, Another Airport, Example Airport North, 
  // just for debug, should be deleted or commented out at some point
  for (const auto & airport : fg.airports) {
    std::cout << airport.second.name << " has routes to:" << std::endl;
    for (const auto dest : airport.second.routes) {
      std::cout << fg.airports[dest].name << ", ";
    }
    std::cout << std::endl << std::endl;
  }

  return 0;
}