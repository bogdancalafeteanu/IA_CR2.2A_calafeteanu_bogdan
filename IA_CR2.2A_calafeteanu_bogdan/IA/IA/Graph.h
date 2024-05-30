#pragma once
#include "City.h"

class Graph {
public:
    int distances[MAX_CITIES][MAX_CITIES]; // 2D array to store distances between cities
    int numCities; // Number of cities in the graph

    // Constructor: Initializes the graph with maximum distances between cities
    Graph(int n) : numCities(n) {
        // Initialize distances between cities
        for (int i = 0; i < MAX_CITIES; ++i) {
            for (int j = 0; j < MAX_CITIES; ++j) {
                if (i == j) {
                    distances[i][j] = 0; // Distance between a city and itself is zero
                }
                else {
                    distances[i][j] = INT_MAX; // Initialize other distances to maximum value
                }
            }
        }
    }

    // Adds a distance between two cities to the graph
    void addDistance(int city1, int city2, int distance) {
        // Set the distance between city1 and city2
        distances[city1][city2] = distance;
        // Since the graph is undirected, set the distance between city2 and city1 as well
        distances[city2][city1] = distance;
    }

    // Gets the distance between two cities from the graph
    int getDistance(int city1, int city2) const {
        // Return the distance between city1 and city2
        return distances[city1][city2];
    }
};
