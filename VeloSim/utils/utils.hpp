#ifndef UTILS_HPP
#define UTILS_HPP

#include "simpleble/SimpleBLE.h"
#include <string>

namespace Utils {
	std::optional<std::size_t> getUserInputInt(const std::string& line, std::size_t max);
	bool is_indoor_trainer(SimpleBLE::Peripheral& device);
	bool is_heart_rate_monitor(SimpleBLE::Peripheral& device);
}

#endif