#include "TSP.h"  // Include the header file that defines the TSP, City, and Graph classes
#include <chrono>
#include <iostream>

using namespace std;

int main() {

    // Define the names of Romanian cities
    string cityNames[MAX_CITIES] = {
        "Bucuresti", "Cluj-Napoca", "Timisoara", "Iasi", "Constanta", "Brasov",
        "Galati", "Craiova", "Ploiesti", "Oradea", "Braila", "Arad", "Pitesti"
    };

    // Create the list of cities with their respective names and IDs
    City* cities = new City[MAX_CITIES];
    for (int i = 0; i < MAX_CITIES; ++i) {
        cities[i] = City(cityNames[i], i);
    }

    // Create the graph with a predefined number of cities (MAX_CITIES)
    Graph graph(MAX_CITIES);

    // Define the distances between each pair of cities
    int distances[MAX_CITIES][MAX_CITIES] = {
        {0, 499, 514, 428, 225, 150, 309, 234, 348, 469, 312, 504, 362},
        {499, 0, 451, 323, 631, 272, 368, 571, 155, 300, 324, 535, 221},
        {514, 451, 0, 573, 778, 465, 465, 556, 598, 146, 501, 199, 349},
        {428, 323, 573, 0, 808, 215, 305, 336, 270, 476, 358, 488, 289},
        {225, 631, 778, 808, 0, 491, 440, 232, 306, 750, 480, 771, 587},
        {150, 272, 465, 215, 491, 0, 232, 254, 176, 375, 167, 309, 209},
        {309, 368, 465, 305, 440, 232, 0, 363, 369, 522, 145, 163, 101},
        {234, 571, 556, 336, 232, 254, 363, 0, 436, 701, 238, 413, 131},
        {348, 155, 598, 270, 306, 176, 369, 436, 0, 464, 225, 364, 113},
        {469, 300, 146, 476, 750, 375, 522, 701, 464, 0, 608, 61, 435},
        {312, 324, 501, 358, 480, 167, 145, 238, 225, 608, 0, 388, 204},
        {504, 535, 199, 488, 771, 309, 163, 413, 364, 61, 388, 0, 484},
        {362, 221, 349, 289, 587, 209, 101, 131, 113, 435, 204, 484, 0}
    };

    // Add the distances to the graph
    for (int i = 0; i < MAX_CITIES; ++i) {
        for (int j = 0; j < MAX_CITIES; ++j) {
            if (i != j) {
                graph.addDistance(i, j, distances[i][j]);
            }
        }
    }

    // Create the TSP object with the graph, number of cities, and list of cities
    TSP tsp(graph, MAX_CITIES, cities);

    // Measure the execution time for Depth-First Search
    auto start_dfs = chrono::high_resolution_clock::now();
    tsp.depthFirstSearch(0);
    auto end_dfs = chrono::high_resolution_clock::now();
    auto elapsed_dfs = chrono::duration_cast<chrono::milliseconds>(end_dfs - start_dfs);
    cout << "Depth-First Search Time: " << elapsed_dfs.count() << " ms" << endl;

    // Measure the execution time for Uniform Cost Search
    auto start_ucs = chrono::high_resolution_clock::now();
    tsp.uniformCostSearch(0);
    auto end_ucs = chrono::high_resolution_clock::now();
    auto elapsed_ucs = chrono::duration_cast<chrono::milliseconds>(end_ucs - start_ucs);
    cout << "Uniform Cost Search Time: " << elapsed_ucs.count() << " ms" << endl;

    // Measure the execution time for A* Search
    auto start_astar = chrono::high_resolution_clock::now();
    tsp.aStarSearch(0);
    auto end_astar = chrono::high_resolution_clock::now();
    auto elapsed_astar = chrono::duration_cast<chrono::milliseconds>(end_astar - start_astar);
    cout << "A* Search Time: " << elapsed_astar.count() << " ms" << endl;

    // Free the memory allocated for the cities array
    delete[] cities;

    return 0;
}
