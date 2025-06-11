#include "Heap.h"
#include <algorithm>

// Constructor
MinHeap::MinHeap(int maxSize) : size(0) {
    positions.resize(maxSize, -1);
}

// Helper functions
int MinHeap::parent(int i) { 
    return (i - 1) / 2; 
}

int MinHeap::leftChild(int i) { 
    return 2 * i + 1; 
}

int MinHeap::rightChild(int i) { 
    return 2 * i + 2; 
}

// Check if heap is empty
bool MinHeap::isEmpty() const {
    return size == 0;
}

// Check if vertex exists in heap
bool MinHeap::contains(int vertex) const {
    return vertex >= 0 && vertex < static_cast<int>(positions.size()) && positions[vertex] != -1;
}

// Get the distance of a vertex
int MinHeap::getDistance(int vertex) const {
    if (!contains(vertex)) {
        return std::numeric_limits<int>::max();
    }
    return heap[positions[vertex]].first;
}

// Fix the min heap property after insertion or extraction
void MinHeap::heapify(int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);
    
    if (left < size && heap[left].first < heap[smallest].first)
        smallest = left;
        
    if (right < size && heap[right].first < heap[smallest].first)
        smallest = right;
        
    if (smallest != i) {
        // Swap elements
        std::swap(heap[i], heap[smallest]);
        
        // Update positions in position vector
        positions[heap[i].second] = i;
        positions[heap[smallest].second] = smallest;
        
        // Recursively heapify the affected sub-tree
        heapify(smallest);
    }
}

// Insert a new vertex or update existing one
void MinHeap::insert(int vertex, int distance) {
    if (contains(vertex)) {
        // Update key value of existing vertex
        int i = positions[vertex];
        heap[i].first = distance;
        
        // Fix the min heap property if needed
        while (i > 0 && heap[i].first < heap[parent(i)].first) {
            // Swap with parent
            std::swap(heap[i], heap[parent(i)]);
            
            // Update positions
            positions[heap[i].second] = i;
            positions[heap[parent(i)].second] = parent(i);
            
            // Move up to parent
            i = parent(i);
        }
    } else {
        // Insert new vertex
        heap.push_back(std::make_pair(distance, vertex));
        positions[vertex] = size;
        size++;
        
        // Fix the min heap property
        int i = size - 1;
        while (i > 0 && heap[i].first < heap[parent(i)].first) {
            // Swap with parent
            std::swap(heap[i], heap[parent(i)]);
            
            // Update positions
            positions[heap[i].second] = i;
            positions[heap[parent(i)].second] = parent(i);
            
            // Move up to parent
            i = parent(i);
        }
    }
}

// Extract the vertex with minimum distance
std::pair<int, int> MinHeap::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    
    // Store the root (minimum) element
    std::pair<int, int> root = heap[0];
    
    // Replace root with last element and remove last element
    heap[0] = heap[size - 1];
    positions[heap[0].second] = 0;
    positions[root.second] = -1;
    size--;
    heap.pop_back();
    
    // Fix the min heap property
    if (size > 0) {
        heapify(0);
    }
    
    return root;
}

// Decrease the distance value for a vertex
void MinHeap::decreaseKey(int vertex, int newDistance) {
    if (!contains(vertex)) {
        throw std::runtime_error("Vertex not in heap");
    }
    
    int i = positions[vertex];
    
    // Update distance value
    if (newDistance > heap[i].first) {
        throw std::runtime_error("New distance is greater than current distance");
    }
    
    heap[i].first = newDistance;
    
    // Fix the min heap property if needed
    while (i > 0 && heap[i].first < heap[parent(i)].first) {
        // Swap with parent
        std::swap(heap[i], heap[parent(i)]);
        
        // Update positions
        positions[heap[i].second] = i;
        positions[heap[parent(i)].second] = parent(i);
        
        // Move up to parent
        i = parent(i);
    }
}