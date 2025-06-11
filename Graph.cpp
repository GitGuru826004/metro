#include "Graph.h"
#include "Heap.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include <cmath>

// Station class implementation
Station::Station() : name(""), line("") {}

Station::Station(const std::string& name, const std::string& line) 
    : name(name), line(line) {}

std::string Station::getName() const { 
    return name; 
}

std::string Station::getLine() const { 
    return line; 
}

// Edge class implementation
Edge::Edge(int dest, int dist) : destination(dest), distance(dist) {}

int Edge::getDestination() const { 
    return destination; 
}

int Edge::getDistance() const { 
    return distance; 
}

// Graph class implementation
Graph::Graph() : numVertices(0) {}

void Graph::addStation(const std::string& name, const std::string& line) {
    stations.push_back(Station(name, line));
    stationIndices[name] = numVertices;
    adjacencyList.push_back(std::list<Edge>());
    numVertices++;
}

void Graph::addEdge(const std::string& src, const std::string& dest, int distance) {
    // Check if both stations exist
    if (!hasStation(src) || !hasStation(dest)) {
        std::cerr << "Error: One or both stations do not exist: " << src << ", " << dest << std::endl;
        return;
    }
    
    int srcIndex = stationIndices[src];
    int destIndex = stationIndices[dest];
    
    // Add edge in both directions (undirected graph)
    adjacencyList[srcIndex].push_back(Edge(destIndex, distance));
    adjacencyList[destIndex].push_back(Edge(srcIndex, distance));
}

bool Graph::hasStation(const std::string& name) const {
    return stationIndices.find(name) != stationIndices.end();
}

int Graph::getStationIndex(const std::string& name) const {
    auto it = stationIndices.find(name);
    if (it != stationIndices.end()) {
        return it->second;
    }
    return -1; // Station not found
}

Station Graph::getStation(int index) const {
    if (index >= 0 && index < static_cast<int>(stations.size())) {
        return stations[index];
    }
    return Station(); // Return empty station if index is invalid
}

std::vector<std::string> Graph::getAllStations() const {
    std::vector<std::string> stationNames;
    for (const auto& station : stations) {
        stationNames.push_back(station.getName());
    }
    return stationNames;
}

void Graph::printPath(const std::vector<int>& parent, int dest, std::vector<int>& path) {
    if (parent[dest] == -1) {
        path.push_back(dest);
        return;
    }
    printPath(parent, parent[dest], path);
    path.push_back(dest);
}

std::pair<int, std::vector<int>> Graph::dijkstra(int src, int dest) {
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    std::vector<int> parent(numVertices, -1);
    MinHeap minHeap(numVertices);
    
    // Distance of source vertex from itself is 0
    distance[src] = 0;
    minHeap.insert(src, 0);
    
    // Process vertices
    while (!minHeap.isEmpty()) {
        // Extract the vertex with minimum distance
        std::pair<int, int> current = minHeap.extractMin();
        int u = current.second;
        
        // If we reached the destination, we can stop
        if (u == dest) {
            break;
        }
        
        // Update distance value of adjacent vertices
        for (const Edge& edge : adjacencyList[u]) {
            int v = edge.getDestination();
            int weight = edge.getDistance();
            
            // If there is a shorter path to v through u
            if (distance[u] != std::numeric_limits<int>::max() && 
                distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                
                // Update distance in min heap
                if (minHeap.contains(v)) {
                    minHeap.decreaseKey(v, distance[v]);
                } else {
                    minHeap.insert(v, distance[v]);
                }
            }
        }
    }
    
    // Reconstruct path
    std::vector<int> path;
    if (distance[dest] != std::numeric_limits<int>::max()) {
        printPath(parent, dest, path);
    }
    
    return std::make_pair(distance[dest], path);
}

int Graph::calculateFare(int distance) {
    if (distance <= 0) return 0;
    if (distance <= 2) return 10;
    if (distance <= 5) return 20;
    if (distance <= 12) return 30;
    if (distance <= 21) return 40;
    if (distance <= 32) return 50;
    return 60; // for distances > 32 km
}

int Graph::estimateTravelTime(int distance, int changes) {
    // 1 km = 1.5 mins, each interchange adds 2 mins
    return static_cast<int>(std::round(distance * 1.5 + changes * 2));
}

std::pair<int, std::vector<int>> Graph::shortestPath(const std::string& srcName, const std::string& destName) {
    int src = getStationIndex(srcName);
    int dest = getStationIndex(destName);
    
    if (src == -1 || dest == -1) {
        return std::make_pair(-1, std::vector<int>()); // Invalid stations
    }
    
    return dijkstra(src, dest);
}

void Graph::displayMap() const {
    std::cout << "\n===== Delhi Metro Map =====\n";
    for (int i = 0; i < numVertices; i++) {
        const Station& station = stations[i];
        std::cout << "Station: " << station.getName() << " (Line: " << station.getLine() << ")\n";
        std::cout << "  Connected to: ";
        
        for (const Edge& edge : adjacencyList[i]) {
            std::cout << stations[edge.getDestination()].getName() 
                      << " (" << edge.getDistance() << " km) ";
        }
        std::cout << "\n";
    }
    std::cout << "==========================\n";
}