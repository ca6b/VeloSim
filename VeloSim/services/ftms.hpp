#ifndef FTMS_HPP
#define FTMS_HPP

#include "simpleble/SimpleBLE.h"
#include <string>

namespace FTMS {

    void read_indoor_bike_data(const SimpleBLE::ByteArray& bytes);
}
#endif

//bool more_data = (flags & 0x01) == 0x01;
//bool average_speed_present = (flags & 0x02) == 0x02;
//bool instantaneous_cadence_present = (flags & 0x04) == 0x04;
//bool average_cadence_present = (flags & 0x08) == 0x08;
//bool total_distance_present = (flags & 0x10) == 0x10;
//bool resistance_level_present = (flags & 0x20) == 0x20;
//bool instantaneous_power_present = (flags & 0x40) == 0x40;
//bool average_power_present = (flags & 0x80) == 0x80;

//std::cout << "More Data: " << (more_data ? "Yes" : "No") << std::endl;
//std::cout << "Average Speed Present: " << (average_speed_present ? "Yes" : "No") << std::endl;
//std::cout << "Cadence Present: " << (instantaneous_cadence_present ? "Yes" : "No") << std::endl;
//std::cout << "Average Cadence Present: " << (average_cadence_present ? "Yes" : "No") << std::endl;
//std::cout << "Total Distance Present: " << (total_distance_present ? "Yes" : "No") << std::endl;
//std::cout << "Resistance Level Present: " << (resistance_level_present ? "Yes" : "No") << std::endl;
//std::cout << "Power Present: " << (instantaneous_power_present ? "Yes" : "No") << std::endl;
//std::cout << "Average Power Present: " << (average_power_present ? "Yes" : "No") << std::endl;