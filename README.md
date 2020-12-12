# Final Project | wkolcan2, guoyang2, bwl3, skavi2

[Goals](docs/GOALS.pdf)  
[Contract](docs/CONTRACT_skavi2.pdf)

## Build and Usage

### Dijkstra's Algorithm
 In terminal: 
 
    module unload llvm/6.0.1 
    module load gcc/9.2.0 
 
 1. Make the file in the root directory `make Dijkstra`
 2. Run the executable: `./bin/Dijkstra`

The default arguments are "data/airports.dat" for airport data, "data/routes/dat" for route data, "ORD" for origin, and "EMD" for destination.  
To change these arguments use the following flags:

    -a Airport File  
    -r Route File  
    -o Origin airport (IATA Code)  
    -d Destination airport (IATA Code)  
 
 Example Syntax: Find shortest path from O'Hare (ORD) to JFK Airport (JFK)
 
    ./bin/Dijkstra -o ORD -d JFK
 
 
 
### PageRank Algorithm
 In terminal:
 
    module unload llvm/6.0.1
    module load gcc/9.2.0
 
  1. Make the file in the root directory `make Portrank`
  2. Run the executable `./bin/PortRank`
  
  The default arguments are "data/airports.dat" for airport data and "data/routes/dat".
  To change these arguments use the following flags.
  
     -a Airport File
     -r Route File
     
  Example Syntax: Want to go from O'Hare (ORD) to JFK Airport (JFK)
  
     ./bin/PortRank -a data/airports_sample.dat -r data/routes_sample.dat
