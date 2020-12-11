#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

template <class Route>
class FlightGraph {
  public:
  struct Airport {
    std::string name, city, country;
    double latitude, longitude;
    std::vector<Route> routes;
  };
  // the only purpose of this class is to populate this map.
  std::unordered_map<int, Airport> airports;

  // adds all keys (openflights ID) to map and initializes airports structs.
  FlightGraph(const std::string & airportsFilename) {
    std::ifstream airportsFile(airportsFilename);
    if (!airportsFile.is_open()) {
      std::cerr << "error: file open failed " << airportsFilename << std::endl;
      exit(1);
    }
    std::string line;
    while (std::getline(airportsFile, line))
    {
      // This is very gross, but the only simple way to parse the file,
      std::stringstream ss(line);
      std::string ID_str, name, city, country, IATA, ICAO, 
                  latitude_str, longitude_str, altitude_str, 
                  timezone_str, DST, tz, type, source;
      
      // reading until I see a comma and storing in a string. 
      // For some values, I read until I see a '"' instead, since there might be commas inside.
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
      

      int ID = stoi(ID_str);
      // Don't need right now, but might be helpful later
      //int altitude = stoi(altitude_str);
      double latitude = stod(latitude_str);
      double longitude = stod(longitude_str);
      
      // add key to map and initialize Airport struct
      airports[ID] = Airport {name, city, country, latitude, longitude, std::vector<Route>()};
    }
    airportsFile.close();
  }
  
  // reads from openflights routes dataset and populates routes vector in each Airport struct
  bool addRoutes(const std::string & routesFilename) {
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

      // much easier parsing here, since there aren't complex names with internal commas or ""
      std::getline(ss, airline, ',');
      std::getline(ss, airlineID_str, ',');
      std::getline(ss, srcAP, ',');
      std::getline(ss, srcAPID_str, ',');
      std::getline(ss, destAP, ',');
      std::getline(ss, destAPID_str, ',');
      std::getline(ss, codeshare, ',');
      std::getline(ss, stops_str, ',');
      std::getline(ss, equip, ',');       // equip denotes planes used. could be useful in determining throughput
      // ignore any route from or to an airport without a defined openflights ID
      if (srcAPID_str != "\\N" && destAPID_str != "\\N") {
        int srcAPID = stoi(srcAPID_str);
        int destAPID = stoi(destAPID_str);
        // not necessary atm, but might be useful in the future
        //int airlineID = stoi(airlineID_str);
        //int stops = stoi(stops_str);

        // do not reference any airports that aren't already on the map.
        if (airports.count(srcAPID) != 0 && airports.count(destAPID) != 0) {
          airports[srcAPID].routes.emplace_back(Route(airports[srcAPID], airports[destAPID], destAPID, 1, "747"));
        }
      }
    }
    return true;
  }
};
