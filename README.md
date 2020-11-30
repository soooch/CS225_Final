# Final Project | wkolcan2, guoyang2, bwl3, skavi2

[Goals](docs/GOALS.pdf)  
[Contract](docs/CONTRACT_skavi2.pdf)

## Potential functions to implement

### General Use
 * Convert OpenFlight data into internal representation. Probably directly to graph.
   * This is now more or less done. Might need slight tweaks.

### Dijkstra's Algorithm
 * Create graph with distance/time edges.
   * Calculate distance/time based on provided location data
   * Need a function that calculates route time and/or distance (edge weight) from coordinates, num. of stops, and airplane type.
 * Actually run Dijkstra's
   * Potentially choose to prioritize time or distance

### PageRank Algorithm
 * Create graph with "bandwidth" edges (number of routes in between).
 * Actually run PageRank
   * Learn how to actually run Pagerank
