# 🚇 Delhi Metro Route Planner

A C++ console application that simulates the Delhi Metro network using a graph-based system. The app allows users to:
- Find the **shortest route** between stations
- **Calculate fares** based on distance
- **Visualize station connections** through text-based maps  
All built on real-world metro line logic with interchanges and distances.

---

## 🧠 Project Architecture

```
delhi-metro/
├── Graph.h / Graph.cpp       # Graph structure for stations and connections
├── Heap.h / Heap.cpp         # MinHeap implementation for Dijkstra’s algorithm
├── Main.cpp                  # UI and main control logic
├── metro.exe                 # Compiled executable for Windows
└── README.md                 # Project documentation
```

---

## 🔧 Tech Stack

| Component     | Technology Used      | Description                                      |
|---------------|----------------------|--------------------------------------------------|
| Language       | C++ (STL, OOP)        | Core language using classes, templates, vectors  |
| Algorithm      | Dijkstra’s Algorithm | For shortest path computation                    |
| Data Struct.   | Min Heap             | Optimized priority queue for Dijkstra            |
| Platform       | Console-based (CLI)  | Lightweight, fast, and interactive UI            |
| OS Support     | Windows / Linux      | Cross-platform via standard libraries            |

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/GitGuru826004/delhi-metro.git
cd delhi-metro
```

### 2. Compile the Program

```bash
g++ Main.cpp Graph.cpp Heap.cpp -o metro
```

### 3. Run the Application

```bash
./metro        # For Linux/macOS
metro.exe      # For Windows (or use precompiled binary)
```

---

## 🧪 Features

- 🧑‍🔬 **Shortest Route Finder** between any two metro stations
- 💸 **Fare Calculation** based on total distance
- ⏱️ **Estimated Travel Time** with line-change logic
- 📍 **Station Directory** with line and interchange info
- 🗺️ **Metro Map Visualization** in a text-based format

---

## 🎯 Fare Chart

| Distance (km) | Fare (₹) |
|---------------|----------|
| 0–2           | ₹10      |
| 3–5           | ₹20      |
| 6–12          | ₹30      |
| 13–21         | ₹40      |
| 22–32         | ₹50      |
| >32           | ₹60      |

---

## 👤 Solo Developer

| Name         | Responsibilities                          |
|--------------|--------------------------------------------|
| **Anupam Garg** | C++ Development, Algorithm Design, CLI UI |

---

## 📂 File Breakdown

```
delhi-metro/
├── Main.cpp            # Console UI and user navigation
├── Graph.h / Graph.cpp # Graph structure, shortest path, fare logic
├── Heap.h / Heap.cpp   # Custom MinHeap for Dijkstra's efficiency
└── metro.exe           # Optional Windows binary
```

---

## 📌 Useful Links

- 🔗 GitHub Repository: [https://github.com/GitGuru826004/delhi-metro](https://github.com/GitGuru826004/delhi-metro)

---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).