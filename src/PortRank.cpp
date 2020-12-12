#include "FlightGraph.h"
#include <execution>
#include <algorithm>
#include <numeric>

int main(int argc, char * argv[]) {
  std::string airports = "data/airports_popular.dat"; // TODO: need to change to normal once done testing
  std::string routes = "data/routes.dat";
  double d = 0.85;

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

  size_t N = fg.airports.size();
  
  std::vector<double> M(N * N, 0.0);
  
  for (size_t j = 0; j < N; j++) {
    const auto & routes = fg.airports[j].routes;
    std::vector<int> noDupRoutes;
    noDupRoutes.reserve(routes.size());
    std::transform(routes.cbegin(), routes.cend(), std::back_inserter(noDupRoutes), 
                   [](Route r) -> int { return r.dest; });
    std::sort(noDupRoutes.begin(), noDupRoutes.end());
    noDupRoutes.erase(std::unique(noDupRoutes.begin(), noDupRoutes.end()), noDupRoutes.end());

    for (int dest : noDupRoutes) {
      M[j * N + dest] = 1.0 / noDupRoutes.size();
    }
  }

  std::vector<double> M_hat(M);
  
  std::for_each(M_hat.begin(), M_hat.end(), [d, N](double val) -> double { return val * d + ((1.0 - d) / N); });
  
  std::vector<double> R(N);
  std::generate(R.begin(), R.end(), [](){return (rand() % 101) / 100;});
  double inv_norm = 1.0 / sqrt(std::inner_product(R.cbegin(), R.cend(), R.cbegin(), 0.0));
  std::for_each(R.begin(), R.end(), [inv_norm](double val) -> double { return val * inv_norm; });

  std::cout << std::endl;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      std::cout << std::setprecision(2) << std::fixed << M[j * N + i] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (size_t i = 0; i < N; i++) {
    std::cout << i << ": " << fg.airports[i].name << std::endl;
  }

  return 0;
}