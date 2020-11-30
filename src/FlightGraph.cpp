#include "FlightGraph.h"
#include <iostream>

FlightGraph::FlightGraph(std::string airportsFilename, std::string routesFilename) {
  std::ifstream airportsFile(airportsFilename);
  if (!airportsFile.is_open()) {
    std::cerr << "error: file open failed " << airportsFilename << std::endl;
    exit(1);
  }
  std::string line;
  while (std::getline(airportsFile, line))
  {
    std::stringstream ss(line);
    std::string ID_str, name, city, country, IATA, ICAO, 
                latitude_str, longitude_str, altitude_str, 
                timezone_str, DST, tz, type, source;
    
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
    
    int ID;//, altitude, timezone;
    //float latitude, longitude;

    ID = stoi(ID_str);
    //altitude = stoi(altitude_str);
    //latitude = stod(latitude_str);
    //longitude = stod(longitude_str);
    airports[ID] = Airport {name, city, country};
  }

  airportsFile.close();

  std::ifstream routesFile(routesFilename);
  if (!routesFile.is_open()) {
    std::cerr << "error: file open failed " << routesFilename << std::endl;
    exit(1);
  }
  while (std::getline(routesFile, line)) {
    std::stringstream ss(line);
    std::string airline, airlineID_str, srcAP, srcAPID_str, 
                destAP, destAPID_str, codeshare, stops_str, equip;

    std::getline(ss, airline, ',');
    std::getline(ss, airlineID_str, ',');
    std::getline(ss, srcAP, ',');
    std::getline(ss, srcAPID_str, ',');
    std::getline(ss, destAP, ',');
    std::getline(ss, destAPID_str, ',');
    std::getline(ss, codeshare, ',');
    std::getline(ss, stops_str, ',');
    std::getline(ss, equip, ',');
    if (srcAPID_str != "\\N" && destAPID_str != "\\N") {
      int srcAPID, destAPID;//, airlineID, stops;
      srcAPID = stoi(srcAPID_str);
      destAPID = stoi(destAPID_str);
      //airlineID = stoi(airlineID_str);
      //stops = stoi(stops_str);

      //std::cout << airports[srcAPID].name << " -> " << airports[destAPID].name << std::endl;

      routes[srcAPID].push_back(destAPID);
    }

    
  }

}

//FlightGraph::FlightGraph(std::string airportsFilename) {

//}
