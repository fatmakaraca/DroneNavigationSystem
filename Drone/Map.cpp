#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() {
    // TODO: Your code here
    // Initialize all distances to a value representing no direct connection
    for(int i = 0; i < MAX_SIZE; ++i){
        for(int j = 0; j < MAX_SIZE; ++j){
            distanceMatrix[i][j] = -1;
        }
    }

    // Initialize all provinces as unvisited
    for(int i = 0; i < MAX_SIZE; i++){
        visited[i] = false;
    }
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    // TODO: Your code here
    // Read each line in the CSV file
    // Read each cell separated by a comma
    // Convert cell to an integer and store in distanceMatrix

    std::ifstream file(filename);
    if (!file) {
        std::cout << "File can not opened!" << std::endl;
        return;
    }

    std::string line;
    int i = 0;
    while(std::getline(file, line)){
        std::stringstream ss(line);
        int j = 0;
        int distance = 0;
        while(ss >> distance){
            distanceMatrix[i][j] = distance;
            if (ss.peek() == ',') {
                ss.ignore();
            }
            j++;
        }
        i++;
    }

    file.close();
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    // TODO: Your code here
    if(getDistance(provinceA, provinceB) <= maxDistance){
        return true;
    }
    return false; 
}

// Marks a province as visited
void Map::markAsVisited(int province) {
    // TODO: Your code here
    visited[province] = true;
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    // TODO: Your code here
    if(visited[province] == true){
        return true;
    }
    return false;
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    // TODO: Your code here
    for(int i = 0; i < MAX_SIZE; i++){
        visited[i] = false;
    }
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    // TODO: Your code here
    int count = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        if(visited[i] == true){
            count++;
        }
    }
    return count;
    return 0;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    // TODO: Your code here
    if(provinceA >= 0 && provinceB >= 0){
        return distanceMatrix[provinceA][provinceB];
    }
    return 0;
}