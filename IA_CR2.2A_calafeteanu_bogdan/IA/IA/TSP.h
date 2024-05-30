#pragma once
#include "Graph.h"
#include "PriorityQueue.h"
#include <iostream>

using namespace std;

// Definition of the TSP (Traveling Salesman Problem) class
class TSP {
public:
    Graph graph;        // Graph object representing the cities and distances
    int numCities;      // Number of cities in the problem
    City* cities;       // Array of City objects
    int bestPath[MAX_CITIES + 1];  // Array to store the best path found
    int bestCost;       // Variable to store the cost of the best path

    // Constructor to initialize the TSP object with a graph, number of cities, and an array of cities
    TSP(Graph g, int numCities, City* c) : graph(g), numCities(numCities) {
        cities = new City[numCities];  // Allocate memory for the cities array
        for (int i = 0; i < numCities; ++i) {
            cities[i] = c[i];  // Copy the cities from the input array to the cities member variable
        }
    }

    // Destructor to clean up dynamically allocated memory
    ~TSP() {
        delete[] cities;
    }

    // Public methods for different search algorithms
    void depthFirstSearch(int start);
    void uniformCostSearch(int start);
    void aStarSearch(int start);

private:
    // Private helper method for depth-first search (DFS)
    void dfs(int current, bool visited[], int path[], int& pathIndex, int& bestCost, int bestPath[], int currentCost);
    PriorityQueue pq;  // Priority queue used for uniform cost search and A* search
    // Private helper method for the heuristic function used in A* search
    int heuristic(int path[], int pathLength, int nextCity);
};
