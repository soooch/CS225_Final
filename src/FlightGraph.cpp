#include "FlightGraph.h"

template <class Route>
FlightGraph<Route>::FlightGraph(const std::string & airportsFilename) {
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
    double latitude, longitude;

    ID = stoi(ID_str);
    // Don't need right now, but might be helpful later
    //altitude = stoi(altitude_str);
    latitude = stod(latitude_str);
    longitude = stod(longitude_str);
    
    // your IDE may show this is an error. It is not, this is a valid assignment
    airports[ID] = Airport {name, city, country, latitude, longitude, std::vector<Route>()};
  }

  airportsFile.close();
}

template <class Route>
bool FlightGraph<Route>::addRoutes(const std::string & routesFilename) {
  std::ifstream routesFile(routesFilename);
  if (!routesFile.is_open()) {
    std::cerr << "error: file open failed " << routesFilename << std::endl;
    return false;
  }
  std::string line;
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
    std::getline(ss, equip, ',');       // equip denotes planes used. could be useful in determining throughput
    if (srcAPID_str != "\\N" && destAPID_str != "\\N") {
      int srcAPID = stoi(srcAPID_str);
      int destAPID = stoi(destAPID_str);
      // not necessary atm, but might be useful in the future
      //int airlineID = stoi(airlineID_str);
      //int stops = stoi(stops_str);

      // if not already added airports, don't add to graph
      if (airports.count(srcAPID) != 0 && airports.count(destAPID) != 0) {
        airports[srcAPID].routes.push_back(Route(airports[srcAPID], airports[destAPID], destAPID, 1, "747"));
      }
    }
  }
  return true;
}