#include "FlightGraph.h"
#include <iostream>

FlightGraph::FlightGraph(std::string airportsFilename, std::string routesFilename) {
  std::ifstream airportFile(airportsFilename);
  if (!airportFile.is_open()) {
    std::cerr << "error: file open failed " << airportsFilename << std::endl;
    exit(1);
  }
  std::string line;
  while (std::getline(airportFile, line))
  {
    std::stringstream ss(line);
    std::string ID_str, name, city, country, IATA, ICAO, 
                latitude_str, longitude_str, altitude_str, 
                timezone_str, DST, tz, type, source, temp;
    
    std::getline(ss, ID_str, ',');
    ss.ignore(2, '"');
    std::getline(ss, name, '"');
    ss.ignore(256, ',');
    ss.ignore(2, '"');
    std::getline(ss, city, '"');
    ss.ignore(256, ',');
    ss.ignore(2, '"');
    std::getline(ss, country, '"');
    ss.ignore(256, ',');
    std::getline(ss, IATA, ',');
    std::getline(ss, ICAO, ',');
    std::getline(ss, latitude_str, ',');
    std::getline(ss, longitude_str, ',');
    std::getline(ss, altitude_str, ',');
    std::getline(ss, timezone_str, ',');
    ss.ignore(2, '"');
    std::getline(ss, DST, '"');
    ss.ignore(256, ',');
    ss.ignore(2, '"');
    std::getline(ss, tz, '"');
    ss.ignore(256, ',');
    ss.ignore(2, '"');
    std::getline(ss, type, '"');
    ss.ignore(256, ',');
    ss.ignore(2, '"');
    std::getline(ss, source, '"');
    ss.ignore(256, ',');
    
    std::cout << ID_str << " " << name << " " << latitude_str << " " << longitude_str << std::endl;

    int ID, altitude, timezone;
    float latitude, longitude;

    ID = stoi(ID_str);
    altitude = stoi(altitude_str);
    latitude = stod(latitude_str);
    longitude = stod(longitude_str);

  }
}

//FlightGraph::FlightGraph(std::string airportsFilename) {

//}
