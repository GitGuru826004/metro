#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <utility>
#include <limits>
#include <stdexcept>

// MinHeap class for Dijkstra's algorithm to find shortest path
// Each element is a pair of (distance, vertex_id)
class MinHeap {
private:
    std::vector<std::pair<int, int>> heap; // (distance, vertex_id)
    std::vector<int> positions; // To track position of vertex in heap
    int size;

    // Helper functions for heap operations
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    
    // Fix the min heap property after insertion or extraction
    void heapify(int i);

public:
    MinHeap(int maxSize);
    
    bool isEmpty() const;
    
    // Check if vertex exists in heap
    bool contains(int vertex) const;
    
    // Get the distance of a vertex
    int getDistance(int vertex) const;
    
    // Insert a new vertex or update existing one
    void insert(int vertex, int distance);
    
    // Extract the vertex with minimum distance
    std::pair<int, int> extractMin();
    
    // Decrease the distance value for a vertex
    void decreaseKey(int vertex, int newDistance);
};

#endif // HEAP_H