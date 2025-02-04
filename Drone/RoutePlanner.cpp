#include "RoutePlanner.h"
#include <iostream>
#include <fstream>

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {

    // TO DO:
    // Load map data from file
    // Mark all provinces as unvisited initially
    map.loadDistanceData(distance_data);
    
    // Load priority provinces
    loadPriorityProvinces(priority_data);
    // Load restricted provinces
    loadWeatherRestrictedProvinces(restricted_data);
    stack = Stack();
    queue = Queue();
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    // TODO: Your code here
    numPriorityProvinces = 0;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int province;
    while (file >> province && numPriorityProvinces < MAX_PRIORITY_PROVINCES) {
        priorityProvinces[numPriorityProvinces++] = province;  
    }

    file.close();
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    // TODO: Your code here
    numWeatherRestrictedProvinces = 0;
     std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int province;
    while (file >> province && numWeatherRestrictedProvinces < MAX_WEATHER_RESTRICTED_PROVINCES) {
        weatherRestrictedProvinces[numWeatherRestrictedProvinces++] = province;  
    }

    file.close();
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    // TODO: Your code here
    for(int i = 0; i < numPriorityProvinces; ++i){
        if(province == priorityProvinces[i]){
            return true;
        }
    }
    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    // TODO: Your code here
    for(int i = 0; i < numWeatherRestrictedProvinces; ++i){
        if(province == weatherRestrictedProvinces[i]){
            return true;
        }
    }
    return false;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    // TODO: Your code here
    exploreFromProvince(startingCity);
    int prev_city = startingCity;

    while(isExplorationComplete() == false){
        if(queue.isEmpty()==false){
            int province = queue.dequeue();

            int distance = map.distanceMatrix[province][prev_city];
        
            if(distance == -1 || distance > maxDistance){
                
                continue;
            }

            bool isVisited = map.visited[province];

            if(isVisited==true){
                continue;
            }

            bool isWeatherRestrictedProvince = isWeatherRestricted(province);

            if(isWeatherRestrictedProvince == true){
                std::cout << "Province " << cities[province] << " is weather-restricted. Skipping." << std::endl;
                continue;
            }
            
            exploreFromProvince(province);
            prev_city = province;
            totalDistanceCovered += distance;
        }
        else{
            backtrack();
        }
    }

    displayResults();
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    // TODO: Your code here 
    map.markAsVisited(province);
    route.push_back(province);

    stack.push(province);
    
    enqueueNeighbors(province);
    
}

void RoutePlanner::enqueueNeighbors(int province) {
    // TO DO: Enqueue priority & non-priority neighbors to the queue according to given constraints
    for(int i = 0; i < 81; ++i){
        int distance = map.distanceMatrix[province][i];
        
        if(distance == -1 || distance > maxDistance){
            
            continue;
        }

        bool is_priority_province = isPriorityProvince(i);

        if(is_priority_province == false){
            queue.enqueue(i);
        }
        else{
            queue.enqueuePriority(i);
        }

    }
}

void RoutePlanner::backtrack() {
    // If you reach a dead-end province 
    // TODO: Your code here
    if(stack.isEmpty() == false){
        stack.pop();
    }
}

bool RoutePlanner::isExplorationComplete() const {
    // TODO: Your code here
    if(stack.isEmpty() == true && queue.isEmpty() == true){
        return true;
    }
    return false;
}

void RoutePlanner::displayResults() const {
    // TODO: Your code here
    // Display "Journey Completed!" message
    std::cout << "---------------------------" <<std::endl;
    std::cout<<"Journey Completed!"<<std::endl;
    std::cout << "---------------------------" <<std::endl;
    // Display the total number of provinces visited
    std::cout<<"Total Number of Provinces Visited: "<<route.size()<<std::endl;
    // Display the total distance covered
    std::cout << "Total Distance Covered: "<<totalDistanceCovered<<" km" <<std::endl;
    // Display the route in the order visited
    std::cout << "Route Taken:" <<std::endl;
    for (size_t i = 0; i < route.size(); ++i) {
        int province= route[i];
        std::cout << cities[province];
        if (i != route.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
    // Priority Province Summary
    std::cout<<"Priority Provinces Status:"<<std::endl;
    int count = 0;
    for(int i = 0; i < numPriorityProvinces; ++i){
        int province = priorityProvinces[i];
        bool is_visited = map.visited[province];
        if(is_visited==true){
            count++;
            std::cout<<"- " << cities[province] <<" (Visited)"<<std::endl;
        }else{
            std::cout<<"- " << cities[province] <<" (Not Visited)"<<std::endl;
        }
    }
    std::cout << std::endl;

    std::cout<<"Total Priority Provinces Visited: "<< count <<" out of "<<numPriorityProvinces <<std::endl;
    if(count==numPriorityProvinces){
        std::cout<<"Success: All priority provinces were visited."<<std::endl;
    }else{
        std::cout<<"Warning: Not all priority provinces were visited."<<std::endl;
    }


}


