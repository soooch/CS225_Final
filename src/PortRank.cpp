#include "FlightGraph.h"
#include <iostream>

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
  class Route {
    public:
    int dest;
    
    Route(const FlightGraph<Route>::Airport & origin, const FlightGraph<Route>::Airport & dest, int destID, int stops, const std::string & equip) : dest(destID) {}
  };

  FlightGraph<Route> fg(airports);
  fg.addRoutes(routes);
  
  std::vector<double> adjMat(fg.airports.size() * fg.airports.size(), 0.0);
  
  for (size_t i = 0; i < fg.airports.size(); i++) {
    const auto & routes = fg.airports[i].routes;
    std::vector<int> noDupRoutes;
    noDupRoutes.reserve(routes.size());
    std::transform(routes.cbegin(), routes.cend(), std::back_inserter(noDupRoutes), 
                   [](Route r) -> int { return r.dest; });
    std::sort(noDupRoutes.begin(), noDupRoutes.end());
    noDupRoutes.erase(std::unique(noDupRoutes.begin(), noDupRoutes.end()), noDupRoutes.end());

    for (int dest : noDupRoutes) {
      adjMat[i * fg.airports.size() + dest] = 1.0 / noDupRoutes.size();
    }
  }

  std::cout << std::endl;
  for (size_t i = 0; i < fg.airports.size(); i++) {
    for (size_t j = 0; j < fg.airports.size(); j++) {
      std::cout << std::setprecision(4) << std::fixed << adjMat[i * fg.airports.size() + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (size_t i = 0; i < fg.airports.size(); i++) {
    std::cout << i << ": " << fg.airports[i].name << std::endl;
  }

  return 0;
}