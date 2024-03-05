#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>


void newBus(std::unordered_map<std::string, std::vector<std::string>>& busList,
            std::map<std::string, std::vector<std::string>>& stopList){
    std::string busNumber = "";
    int stopCount = 0;
    std::cin    >> busNumber
                >> stopCount;

    auto& stops = busList[busNumber];

    for(int i = 0; i < stopCount; i++){
        std::string busStop = "";
        std::cin >> busStop;

        auto & buses = stopList[busStop];

        buses.emplace_back(busNumber);
        stops.emplace_back(std::move(busStop));
    }
}

void busesForStop(std::unordered_map<std::string, std::vector<std::string>>& busList,
                    std::map<std::string, std::vector<std::string>>& stopList){
                        
    std::string busStop;
    std::cin >> busStop;
    bool found = false;
    
    for(const auto& [bus, stops] : busList){
        for(auto stop : stops){
            if(stop == busStop){
                std::cout   << bus
                            << " ";
                found = true;
                break;
            }
        }
    }
    if(!found){
        std::cout << "No stop";
    }
    std::cout << std::endl;
}

void stopForBus(std::unordered_map<std::string, std::vector<std::string>>& busList){
    std::string bus;
    std::cin >> bus;
    auto it = busList.find(bus);
    if(it == busList.end()){
        std::cout << "No bus" << std::endl;
        return;
    }

    const auto& stops = it -> second;
    for(const auto& stop : stops){
        std::cout << "Stop " << stop << ":";
        bool hasIntercgange = false;
        for(const auto& [otherBus, otherStops] : busList){
            if(otherBus != bus){
                for(const auto& otherStop : otherStops){
                    if(otherStop == stop){
                        std::cout << " " << otherBus;
                        hasIntercgange = true;
                        break;
                    }
                }
            }
        }
        if(!hasIntercgange)
            std::cout << " no interchange";
        std::cout << std::endl;
    }
}

void allBuses(std::unordered_map<std::string, std::vector<std::string>>& busList){
    if(busList.empty()){
        std::cout << "No buses" << std::endl;
        return;
    }

    std::vector<std::string> reversBusList;

    for (const auto& [bus, stops] : busList) {
        reversBusList.push_back(bus);
    }

    for (auto bus = reversBusList.rbegin(); bus != reversBusList.rend(); ++bus) {
        std::cout << "Bus " << *bus << ":";
        for (const auto& stop : busList[*bus]) {
            std::cout << " " << stop;
        }
        std::cout << std::endl;
    }
}

int main(){
    
    std::unordered_map<std::string, std::vector<std::string>> busList;
    std::map<std::string, std::vector<std::string>> stopList;
    int q = 0;
    std::cin >> q;

    for(int i = 0; i <= q; i++){
        std::string command;
        std::cin.ignore();
        std::cin >> command;
        if(command == "NEW_BUS")
            newBus(busList, stopList);
        else if(command == "BUSES_FOR_STOP")
            busesForStop(busList, stopList);
        else if(command == "STOPS_FOR_BUS")
            stopForBus(busList);
        else if(command == "ALL_BUSES")
            allBuses(busList);
    }
    return 0;
}