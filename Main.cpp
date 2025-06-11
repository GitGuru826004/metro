#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include "Graph.h"

// Helper function to clear the screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Helper function to display the main menu
void displayMenu() {
    std::cout << "\n========== DELHI METRO APP ==========\n";
    std::cout << "1. List All Stations\n";
    std::cout << "2. Show Metro Map\n";
    std::cout << "3. Get Shortest Route & Fare\n";
    std::cout << "4. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter your choice: ";
}

// Helper function to get user input with validation
template <typename T>
T getInput(const std::string& prompt) {
    T value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. " << prompt;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Main application class
class DelhiMetroApp {
private:
    Graph metroGraph;

    // Initialize the metro graph with stations and connections
    void initializeMetroNetwork() {
        // Add stations with their lines
        metroGraph.addStation("Rajiv Chowk", "Blue & Yellow Line");
        metroGraph.addStation("Kashmere Gate", "Red & Yellow Line");
        metroGraph.addStation("Central Secretariat", "Yellow & Violet Line");
        metroGraph.addStation("Mandi House", "Blue & Violet Line");
        metroGraph.addStation("Yamuna Bank", "Blue Line");
        metroGraph.addStation("Inderlok", "Red & Green Line");
        metroGraph.addStation("Kirti Nagar", "Blue & Green Line");
        metroGraph.addStation("Welcome", "Red & Pink Line");
        metroGraph.addStation("Netaji Subhash Place", "Pink & Red Line");
        metroGraph.addStation("Azadpur", "Yellow & Pink Line");
        metroGraph.addStation("Dhaula Kuan", "Orange Line");
        metroGraph.addStation("New Delhi", "Yellow & Orange Line");
        metroGraph.addStation("Dwarka Sector 21", "Blue & Orange Line");
        metroGraph.addStation("Botanical Garden", "Blue & Magenta Line");
        metroGraph.addStation("Janakpuri West", "Blue & Magenta Line");
        metroGraph.addStation("Lajpat Nagar", "Violet & Pink Line");
        metroGraph.addStation("Mayur Vihar Phase-1", "Blue & Pink Line");
        metroGraph.addStation("Anand Vihar", "Blue & Pink Line");
        metroGraph.addStation("Saket", "Yellow Line");
        metroGraph.addStation("Chandni Chowk", "Yellow Line");
        
        // Add connections between stations (with distances in km)
        // Blue Line connections
        metroGraph.addEdge("Rajiv Chowk", "Mandi House", 2);
        metroGraph.addEdge("Mandi House", "Yamuna Bank", 6);
        metroGraph.addEdge("Rajiv Chowk", "Kirti Nagar", 7);
        metroGraph.addEdge("Kirti Nagar", "Janakpuri West", 9);
        metroGraph.addEdge("Yamuna Bank", "Anand Vihar", 8);
        metroGraph.addEdge("Botanical Garden", "Janakpuri West", 38);
        metroGraph.addEdge("Yamuna Bank", "Mayur Vihar Phase-1", 3);
        
        // Yellow Line connections
        metroGraph.addEdge("Rajiv Chowk", "Central Secretariat", 3);
        metroGraph.addEdge("Central Secretariat", "Saket", 10);
        metroGraph.addEdge("Rajiv Chowk", "New Delhi", 1);
        metroGraph.addEdge("New Delhi", "Chandni Chowk", 2);
        metroGraph.addEdge("Chandni Chowk", "Kashmere Gate", 2);
        metroGraph.addEdge("Kashmere Gate", "Azadpur", 8);
        
        // Red Line connections
        metroGraph.addEdge("Kashmere Gate", "Inderlok", 7);
        metroGraph.addEdge("Inderlok", "Netaji Subhash Place", 5);
        metroGraph.addEdge("Kashmere Gate", "Welcome", 5);
        
        // Green Line connections
        metroGraph.addEdge("Inderlok", "Kirti Nagar", 8);
        
        // Violet Line connections
        metroGraph.addEdge("Central Secretariat", "Mandi House", 2);
        metroGraph.addEdge("Mandi House", "Lajpat Nagar", 6);
        
        // Orange Line (Airport Express) connections
        metroGraph.addEdge("New Delhi", "Dhaula Kuan", 7);
        metroGraph.addEdge("Dhaula Kuan", "Dwarka Sector 21", 15);
        
        // Pink Line connections
        metroGraph.addEdge("Azadpur", "Netaji Subhash Place", 4);
        metroGraph.addEdge("Netaji Subhash Place", "Welcome", 12);
        metroGraph.addEdge("Welcome", "Anand Vihar", 10);
        metroGraph.addEdge("Anand Vihar", "Mayur Vihar Phase-1", 6);
        metroGraph.addEdge("Mayur Vihar Phase-1", "Lajpat Nagar", 10);
        
        // Magenta Line connections - Fixed duplicate
        // metroGraph.addEdge("Botanical Garden", "Janakpuri West", 38); // Already added above
    }

public:
    DelhiMetroApp() {
        // Initialize the metro network with stations and connections
        initializeMetroNetwork();
    }

    // Display all stations in the network
    void displayAllStations() {
        std::vector<std::string> stations = metroGraph.getAllStations();
        
        clearScreen();
        std::cout << "\n========== ALL METRO STATIONS ==========\n";
        for (size_t i = 0; i < stations.size(); i++) {
            std::cout << i + 1 << ". " << stations[i] << "\n";
        }
        std::cout << "======================================\n";
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Display metro map
    void showMetroMap() {
        clearScreen();
        metroGraph.displayMap();
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Get the shortest route and fare between two stations
    void getRouteAndFare() {
        clearScreen();
        std::cout << "\n========== GET ROUTE & FARE ==========\n";
        
        // Get source station
        std::string sourceStation = getStringInput("Enter source station: ");
        if (!metroGraph.hasStation(sourceStation)) {
            std::cout << "Source station not found!\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return;
        }
        
        // Get destination station
        std::string destStation = getStringInput("Enter destination station: ");
        if (!metroGraph.hasStation(destStation)) {
            std::cout << "Destination station not found!\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return;
        }
        
        // Find shortest path
        auto result = metroGraph.shortestPath(sourceStation, destStation);
        int totalDistance = result.first;
        std::vector<int> path = result.second;
        
        // Display results
        if (totalDistance == -1 || path.empty()) {
            std::cout << "No path found between " << sourceStation << " and " << destStation << "\n";
        } else {
            int fare = metroGraph.calculateFare(totalDistance);
            
            // Simplified line change counting (basic heuristic)
            int lineChanges = 0;
            if (path.size() > 2) {
                // For simplicity, estimate line changes based on path length
                // This is a rough approximation since complex line change detection
                // would require more sophisticated logic
                lineChanges = static_cast<int>(path.size() / 4); // Rough estimate
            }
            
            // Estimate travel time
            int travelTime = metroGraph.estimateTravelTime(totalDistance, lineChanges);
            
            std::cout << "\n========== ROUTE DETAILS ==========\n";
            std::cout << "Source: " << sourceStation << "\n";
            std::cout << "Destination: " << destStation << "\n";
            std::cout << "Total Distance: " << totalDistance << " km\n";
            std::cout << "Total Fare: Rs " << fare << "\n";
            std::cout << "Estimated Travel Time: " << travelTime << " minutes\n";
            std::cout << "Estimated Line Changes: " << lineChanges << "\n";
            
            std::cout << "\n========== SHORTEST PATH ==========\n";
            std::cout << "Start at: " << metroGraph.getStation(path[0]).getName() 
                      << " (" << metroGraph.getStation(path[0]).getLine() << ")\n";
            
            for (size_t i = 1; i < path.size(); i++) {
                Station currentStation = metroGraph.getStation(path[i]);
                
                std::cout << "-> " << currentStation.getName() 
                          << " (" << currentStation.getLine() << ")\n";
            }
            std::cout << "====================================\n";
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Run the application
    void run() {
        int choice;
        bool running = true;
        
        while (running) {
            clearScreen();
            displayMenu();
            choice = getInput<int>("");
            
            switch (choice) {
                case 1:
                    displayAllStations();
                    break;
                case 2:
                    showMetroMap();
                    break;
                case 3:
                    getRouteAndFare();
                    break;
                case 4:
                    running = false;
                    break;
                default:
                    std::cout << "Invalid choice. Press Enter to continue...";
                    std::cin.get();
            }
        }
        
        std::cout << "\nThank you for using Delhi Metro App!\n";
    }
};

int main() {
    DelhiMetroApp app;
    app.run();
    return 0;
}