#include "utils.hpp"
#include <string>
#include "uuids.hpp"
#include <iostream>

//https://github.com/OpenBluetoothToolbox/SimpleBLE/blob/main/examples/simpleble/cpp/common/utils.cpp
std::optional<std::size_t> Utils::getUserInputInt(const std::string& line, std::size_t max) {
    std::size_t ret;

    while (!std::cin.eof()) {
        std::cout << line << " (0-" << max << "): ";
        std::cin >> ret;

        if (!std::cin) {
            return {};
        }

        if (ret <= max) {
            return ret;
        }
    }
    return {};
}


bool Utils::is_indoor_trainer(SimpleBLE::Peripheral& device) {
	for (auto& service : device.services()) {
		if (service.uuid() == UUIDs::FITNESS_MACHINE_SERVICE_UUID)
			return true;
	}
	return false;
}

bool Utils::is_heart_rate_monitor(SimpleBLE::Peripheral& device) {
    for (auto& service : device.services()) {
        if (service.uuid() == UUIDs::HEART_RATE_SERVICE_UUID)
            return true;
    }
    return false;
}