#include "FlightGraph.h"
#include <iostream>

FlightGraph::FlightGraph() {
  std::ifstream airportFile("../data/airports_sample.dat");
  int ID, latitude, longitude, altitude, timezone;
  std::string name, city, country, IATA, ICAO, DST, tz, type, source;
  char c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13;
  while (airportFile >> ID >> c1 >> name >> c2 >> city >> c3 >> 
         country >> c4 >> IATA >> c5 >> ICAO >> c6 >> latitude >> c7 >> 
         longitude >> c8 >> altitude >> c9 >> timezone >> c10 >> 
         DST >> c11 >> tz >> c12 >> type >> c13 >> source
         && c1 == ',' && c2 == ',' && c3 == ',' && c4 == ',' 
         && c5 == ',' && c6 == ',' && c7 == ',' && c8 == ',' 
         && c9 == ',' && c10 == ',' && c11 == ',' && c12 == ',' && c13 == ',' ) 
  {
    std::cout << ID << " " << name << std::endl;
  }
  routes = std::vector<std::vector<int>>();
  airports = std::vector<std::string>();

}

//FlightGraph::FlightGraph(std::string airportsFilename) {

//}
