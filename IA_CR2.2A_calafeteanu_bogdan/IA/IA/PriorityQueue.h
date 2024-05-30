#pragma once

class PriorityQueue {
public:
    // Structure representing a node in the priority queue
    struct Node {
        int path[MAX_CITIES]; // Path to reach this node
        int cost; // Cost associated with this node
        int pathLength; // Length of the path
    };

    // Constructor: Initializes the priority queue
    PriorityQueue() : size(0) {}

    // Pushes a node into the priority queue
    void push(const Node& node) {
        // Check if the priority queue has space
        if (size < MAX_SIZE) {
            heap[size] = node; // Add the node to the heap
            int current = size++;
            // Heapify: Maintain heap property by comparing with parent nodes
            while (current > 0 && heap[current].cost < heap[(current - 1) / 2].cost) {
                // Swap the node with its parent if its cost is less
                swap(heap[current], heap[(current - 1) / 2]);
                current = (current - 1) / 2; // Move to the parent node
            }
        }
    }

    // Removes and returns the node with the minimum cost from the priority queue
    Node pop() {
        Node minNode = heap[0]; // Get the minimum node (root)
        heap[0] = heap[--size]; // Replace the root with the last node
        heapify(0); // Heapify to maintain heap property
        return minNode; // Return the minimum node
    }

    // Checks if the priority queue is empty
    bool empty() const {
        return size == 0; // Return true if size is zero, indicating an empty queue
    }

private:
    static const int MAX_SIZE = 1000; // Maximum size of the priority queue
    Node heap[MAX_SIZE]; // Array to store nodes in the priority queue
    int size; // Current size of the priority queue

    // Adjusts the heap rooted at index i to maintain heap property
    void heapify(int i) {
        int left = 2 * i + 1; // Left child index
        int right = 2 * i + 2; // Right child index
        int smallest = i; // Assume the current node is the smallest

        // Check if left child exists and its cost is less than the current node's cost
        if (left < size && heap[left].cost < heap[smallest].cost) {
            smallest = left; // Update the index of the smallest node
        }

        // Check if right child exists and its cost is less than the current smallest node's cost
        if (right < size && heap[right].cost < heap[smallest].cost) {
            smallest = right; // Update the index of the smallest node
        }

        // If the smallest node is not the current node, swap them and recursively heapify
        if (smallest != i) {
            swap(heap[i], heap[smallest]); // Swap the nodes
            heapify(smallest); // Recursively heapify the subtree
        }
    }
};
