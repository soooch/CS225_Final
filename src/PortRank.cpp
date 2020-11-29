#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char * argv[]) {
  // TODO: use argument, check for correct syntax
  std::string airports = "../data/airports_sample.dat";
  std::string routes = "../data/routes_sample.dat";

  std::ifstream airportFile(argv[1]);
  if (!airportFile.is_open()) {
    std::cerr << "error: file open failed " << argv[1] << ".\n";
    return 1;
  }
  int ID, latitude, longitude, altitude, timezone;
  std::string name, city, country, IATA, ICAO, DST, tz, type, source;
  char c;
  while (airportFile >> ID >> c >> name >> c >> city >> c >> 
         country >> c >> IATA >> c >> ICAO >> c >> latitude >> c >> 
         longitude >> c >> altitude >> c >> timezone >> c >> 
         DST >> c >> tz >> c >> type >> c >> source)
  {
    std::cout << ID << " " << name << std::endl;
  }

  return 0;
}