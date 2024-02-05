// VeloSim.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "simpleble/SimpleBLE.h"
#include <vector>


using namespace std;

int main()
{
    if (!SimpleBLE::Adapter::bluetooth_enabled()) {
        std::cout << "Bluetooth is disabled." << std::endl;
        return 0;
    }

    std::vector <SimpleBLE::Adapter> available_adapters = SimpleBLE::Adapter::get_adapters();

    if (available_adapters.empty()) {
        std::cout << "No Bluetooth adapter found." << std::endl;
        return 0;
    }

    SimpleBLE::Adapter adapter;
    if (available_adapters.size() == 1) {
        adapter = available_adapters.at(0);
    }
    else {
        std::cout << "Available adapters:" << std::endl;
        for (int i = 0; i < available_adapters.size(); ++i) {
            std::cout << i << ": " << available_adapters.at(i).identifier() << " | " << available_adapters.at(i).address() << std::endl;
        }
        int selection;
        std::cout << "Select an adapter.";
        std::cin >> selection;
        //todo: valider user input

        adapter = available_adapters.at(selection);

    }
    
    return 0;
}
