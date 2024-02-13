// VeloSim.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "simpleble/SimpleBLE.h"
#include <vector>
#include <thread>
#include <csignal>

#include "utils/utils.hpp"
#include "utils/uuids.hpp"
#include "services/ftms.hpp"
#include "services/heartrate.hpp"

using namespace std;
using namespace std::chrono_literals;

//https://simpleble.readthedocs.io/en/latest/simpleble/tutorial.html
//https://github.com/OpenBluetoothToolbox/SimpleBLE


void signalHandler(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nCtrl+C detected. Exiting program.\n";
        exit(signal);
    }
}

int main() {
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

        auto adapter_selection = Utils::getUserInputInt("Please select a device:", available_adapters.size() - 1);
        adapter = available_adapters.at(adapter_selection.value());
    }

    std::vector<SimpleBLE::Peripheral> available_devices;

    adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral) {
            std::cout << "Found device: " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
            available_devices.push_back(peripheral);
        });
    
    adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });
    adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });

    adapter.scan_for(5000);
    
    std::cout << "The following devices were found:" << std::endl;
    for (size_t i = 0; i < available_devices.size(); i++) {
        std::cout << "[" << i << "] " << available_devices[i].identifier() << " [" << available_devices[i].address() << "]"
            << std::endl;
    }

    auto device_selection = Utils::getUserInputInt("Please select a device:", available_devices.size()-1);

    SimpleBLE::Peripheral device = available_devices[device_selection.value()];
    device.connect();

    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> uuids;
    for (auto service : device.services()) {
        for (auto characteristic : service.characteristics()) {
            uuids.push_back(std::make_pair(service.uuid(), characteristic.uuid()));
        }
    }

    std::cout << "The following services and characteristics were found:" << std::endl;
    for (size_t i = 0; i < uuids.size(); i++) {
        std::cout << "[" << i << "] " << uuids[i].first << " " << uuids[i].second << std::endl;
    }

    auto service_selection = Utils::getUserInputInt("Please select a characteristic to read", uuids.size() - 1);


    device.notify(uuids[service_selection.value()].first, uuids[service_selection.value()].second, [&](SimpleBLE::ByteArray bytes) {
        std::cout << "Received: ";
        if(Utils::is_indoor_trainer(device))
            FTMS::read_indoor_bike_data(bytes);
        if (Utils::is_heart_rate_monitor(device))
            HeartRate::read_heart_rate_measurement(bytes);
        });

    signal(SIGINT, signalHandler);
    while (true) {
        std::this_thread::sleep_for(20s);
    }

    device.unsubscribe(uuids[service_selection.value()].first, uuids[service_selection.value()].second);

    device.disconnect();
    return 0;
}
