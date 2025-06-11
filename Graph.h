#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>
#include <list>

// Forward declaration of MinHeap class
class MinHeap;

// Represents a metro station
class Station {
private:
    std::string name;
    std::string line; // Metro corridor/line color

public:
    Station();
    Station(const std::string& name, const std::string& line);
    
    std::string getName() const;
    std::string getLine() const;
};

// Edge represents connection between two stations
class Edge {
private:
    int destination;
    int distance;

public:
    Edge(int dest, int dist);
    
    int getDestination() const;
    int getDistance() const;
};

// Graph representing the metro network
class Graph {
private:
    int numVertices;
    std::vector<Station> stations;
    std::vector<std::list<Edge>> adjacencyList;
    std::unordered_map<std::string, int> stationIndices; // Maps station names to indices

    // Helper function for Dijkstra's algorithm
    void printPath(const std::vector<int>& parent, int dest, std::vector<int>& path);

public:
    Graph();
    
    // Add a new station to the graph
    void addStation(const std::string& name, const std::string& line);
    
    // Add an edge (connection) between two stations
    void addEdge(const std::string& src, const std::string& dest, int distance);
    
    // Check if a station exists in the graph
    bool hasStation(const std::string& name) const;
    
    // Get the index of a station by name
    int getStationIndex(const std::string& name) const;
    
    // Get the station object by index
    Station getStation(int index) const;
    
    // Get all stations
    std::vector<std::string> getAllStations() const;
    
    // Find shortest path using Dijkstra's algorithm
    std::pair<int, std::vector<int>> dijkstra(int src, int dest);
    
    // Calculate fare based on distance
    int calculateFare(int distance);
    
    // Estimate travel time based on distance and line changes
    int estimateTravelTime(int distance, int changes);
    
    // Find shortest path between two stations by name
    std::pair<int, std::vector<int>> shortestPath(const std::string& srcName, const std::string& destName);
    
    // Print the metro map
    void displayMap() const;
};

#endif // GRAPH_H