#include "FlightGraph.h"
// #include <execution>
#include <cmath>
#include <algorithm>
#include <numeric>

int main(int argc, char * argv[]) {
  std::string airports = "data/airports.dat"; // TODO: need to change to normal once done testing
  std::string routes = "data/routes.dat";
  std::string iterations_str = "20";
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
    else if (std::string("-i").compare(argv[i]) == 0) {
      if (++i < argc) {
        iterations_str = argv[i];
      }
    }
  }

  int iterations = std::stoi(iterations_str);

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
      M[j + dest * N] = 1.0 / noDupRoutes.size();
    }
  }

  std::vector<double> M_hat(M);
  
  std::for_each(M_hat.begin(), M_hat.end(), [d, N](double & val) { val = val * d + ((1.0 - d) / N); });
  
  std::vector<double> R(N);
  std::generate(R.begin(), R.end(), []() -> double {return (double)(std::rand() % 101) / 100.0;});
  double inv_norm = 1.0 / sqrt(std::inner_product(R.begin(), R.end(), R.begin(), 0.0));
  std::for_each(R.begin(), R.end(), [inv_norm](double & val) { val *= inv_norm; });
  
  for (int iter = 0; iter < iterations; iter++) {
    for (size_t i = 0; i < N; i++) {
      R[i] = std::inner_product(R.cbegin(), R.cend(), M.cbegin() + i * N, 0.0);
    }
  }

  /*
  std::cout << std::endl;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      std::cout << std::setprecision(2) << std::fixed << M[j + i * N] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (size_t i = 0; i < N; i++) {
    std::cout << i << ": " << fg.airports[i].name << std::endl;
  }
  */

  std::cout << std::endl;


  std::vector<std::pair<int, double>> ranks;
  ranks.reserve(N);

  for (size_t i = 0; i < N; i++) {
    ranks.push_back(std::pair((int)i, R[i]));
  }

  std::sort(ranks.begin(), ranks.end(), [](auto lhs, auto rhs){return lhs.second > rhs.second;});
  
  for (auto AP : ranks) {
    std::cout << fg.airports[AP.first].name << ": " << AP.second << std::endl;
  }



  return 0;
}
