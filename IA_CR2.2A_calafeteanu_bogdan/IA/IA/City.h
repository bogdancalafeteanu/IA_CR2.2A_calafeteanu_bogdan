#pragma once
#include <iostream>
#include <string>

using namespace std;

const int MAX_CITIES = 13; // Maximum number of cities

class City {
private:
    string name; // Name of the city
    int id; // Unique identifier for the city

public:
    // Default constructor
    City() : name("NULL"), id(0) {}

    // Parameterized constructor
    City(string name, int id) : name(name), id(id) {}

    // Getter function to retrieve the name of the city
    string getName() const {
        return this->name;
    }

    // Getter function to retrieve the unique identifier of the city
    int getId() const {
        return this->id;
    }
};
