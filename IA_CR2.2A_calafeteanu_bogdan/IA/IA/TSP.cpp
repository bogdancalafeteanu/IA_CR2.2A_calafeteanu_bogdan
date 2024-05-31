#include "TSP.h"
#include <cstring>


// Depth-first search implementation
void TSP::dfs(int current, bool visited[], int path[], int& pathIndex, int& bestCost, int bestPath[], int currentCost) {
    visited[current] = true; // Mark the current city as visited
    path[pathIndex++] = current; // Add the current city to the path

    // Check if all cities have been visited
    if (pathIndex == graph.numCities) {
        // Complete the cycle by adding the distance back to the starting city
        currentCost += graph.getDistance(current, path[0]);
        // Update the best path and cost if the current path is better
        if (currentCost < bestCost) {
            bestCost = currentCost;
            for (int i = 0; i < pathIndex; i++) {
                bestPath[i] = path[i];
            }
            bestPath[pathIndex] = path[0];
        }
    }
    else {
        // Recur for all the cities that are not yet visited
        for (int i = 0; i < graph.numCities; i++) {
            if (!visited[i] && graph.getDistance(current, i) != INT_MAX) {
                dfs(i, visited, path, pathIndex, bestCost, bestPath, currentCost + graph.getDistance(current, i));
            }
        }
    }

    // Backtrack: Unmark the current city and remove it from the path
    visited[current] = false;
    --pathIndex;
}

// Depth-first search method
void TSP::depthFirstSearch(int start) {
    bool* visited = new bool[graph.numCities];
    memset(visited, false, sizeof(bool) * graph.numCities);

    int* path = new int[graph.numCities + 1];
    int* bestPath = new int[graph.numCities + 1];

    int pathIndex = 0;
    int bestCost = INT_MAX;

    // Initialize pathIndex to 0 before calling dfs
    pathIndex = 0;

    // Call dfs with the starting city 'start'
    dfs(start, visited, path, pathIndex, bestCost, bestPath, 0);

    // Output the result
    cout << "DFS Result: ";
    for (int i = 0; i <= graph.numCities; i++) {
        cout << cities[bestPath[i]].getName() << "("<<cities[bestPath[i]].getId()<<") ";
    }
    cout << "Cost: " << bestCost << endl;

    // Free dynamically allocated memory
    delete[] visited;
    delete[] path;
    delete[] bestPath;
}

// Uniform Cost Search method
void TSP::uniformCostSearch(int start) {
    // Initialize the start node
    PriorityQueue::Node startNode;
    startNode.path[0] = start;
    startNode.cost = 0;
    startNode.pathLength = 1;

    // Push the start node into the priority queue
    pq.push(startNode);

    int bestCost = INT_MAX;
    int bestPath[MAX_CITIES + 1];

    // Loop until there are nodes to explore
    while (!pq.empty()) {
        PriorityQueue::Node currentNode = pq.pop();

        // Check if all cities have been visited
        if (currentNode.pathLength == graph.numCities) {
            int totalCost = currentNode.cost + graph.getDistance(currentNode.path[currentNode.pathLength - 1], start);
            // Update the best path and cost if the current path is better
            if (totalCost < bestCost) {
                bestCost = totalCost;
                for (int i = 0; i < currentNode.pathLength; i++) {
                    bestPath[i] = currentNode.path[i];
                }
                bestPath[currentNode.pathLength] = start;
            }
            continue;
        }

        // Explore the next city for each unvisited city
        for (int i = 0; i < graph.numCities; i++) {
            bool visited = false;
            for (int j = 0; j < currentNode.pathLength; j++) {
                if (currentNode.path[j] == i) {
                    visited = true;
                    break;
                }
            }

            // If the city is not visited and there is a path to it
            if (!visited && graph.getDistance(currentNode.path[currentNode.pathLength - 1], i) != INT_MAX) {
                PriorityQueue::Node newNode;
                for (int j = 0; j < currentNode.pathLength; ++j) {
                    newNode.path[j] = currentNode.path[j];
                }
                newNode.path[currentNode.pathLength] = i;
                newNode.cost = currentNode.cost + graph.getDistance(currentNode.path[currentNode.pathLength - 1], i);
                newNode.pathLength = currentNode.pathLength + 1;

                // Push the new node into the priority queue
                pq.push(newNode);
            }
        }
    }

    // Output the result
    cout << "UCS Result: ";
    for (int i = 0; i <= graph.numCities; ++i) {
        cout << cities[bestPath[i]].getName() << "("<<cities[bestPath[i]].getId()<<") ";
    }
    cout << "Cost: " << bestCost << endl;
}


int TSP::heuristic(int path[], int pathLength, int nextCity) {
    // Heuristic: use the minimum distance to the next unvisited city
    int minDist = INT_MAX;

    for (int i = 0; i < graph.numCities; ++i) {
        bool visited = false;

        // Check if the city is already visited
        for (int j = 0; j < pathLength; ++j) {
            if (path[j] == i) {
                visited = true;
                break;
            }
        }

        // If the city is not visited, consider it for the heuristic
        if (!visited) {
            int dist = graph.getDistance(nextCity, i);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    return (minDist == INT_MAX) ? 0 : minDist; // Return 0 if no unvisited cities are found
}

void TSP::aStarSearch(int start) {
    PriorityQueue::Node startNode;
    memset(startNode.path, -1, sizeof(startNode.path)); // Initialize with invalid city
    startNode.path[0] = start;
    startNode.cost = 0;
    startNode.pathLength = 1;
    pq.push(startNode);

    int bestCost = INT_MAX;
    int bestPath[MAX_CITIES + 1] = { -1 }; // Initialize bestPath with an invalid city

    while (!pq.empty()) {
        PriorityQueue::Node currentNode = pq.pop();

        if (currentNode.pathLength == graph.numCities) {
            int totalCost = currentNode.cost + graph.getDistance(currentNode.path[currentNode.pathLength - 1], start);
            if (totalCost < bestCost) {
                bestCost = totalCost;
                for (int i = 0; i < currentNode.pathLength; ++i) {
                    bestPath[i] = currentNode.path[i];
                }
                bestPath[currentNode.pathLength] = start;
            }
            continue;
        }

        for (int i = 0; i < graph.numCities; ++i) {
            bool visited = false;
            for (int j = 0; j < currentNode.pathLength; ++j) {
                if (currentNode.path[j] == i) {
                    visited = true;
                    break;
                }
            }

            if (!visited && graph.getDistance(currentNode.path[currentNode.pathLength - 1], i) != INT_MAX) {
                PriorityQueue::Node newNode;
                for (int j = 0; j < currentNode.pathLength; ++j) {
                    newNode.path[j] = currentNode.path[j];
                }
                newNode.path[currentNode.pathLength] = i;
                newNode.cost = currentNode.cost + graph.getDistance(currentNode.path[currentNode.pathLength - 1], i);
                newNode.pathLength = currentNode.pathLength + 1;

                // Calculate total cost with heuristic
                int heuristicCost = newNode.cost + heuristic(newNode.path, newNode.pathLength, i);
                pq.push(newNode);
            }
        }
    }

    cout << "A* Result: ";
    for (int i = 0; i <= graph.numCities; ++i) {
        if (bestPath[i] != -1) { // Only print valid cities
            cout << cities[bestPath[i]].getName() << "("<<cities[bestPath[i]].getId()<<")"<<" ";
        }
    }
    cout << bestCost<<endl;
}
