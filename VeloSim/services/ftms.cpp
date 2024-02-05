
#include <bitset>
#include <iostream>
#include "ftms.hpp"
#include <iomanip>

void FTMS::read_indoor_bike_data(const SimpleBLE::ByteArray& bytes) {

    uint8_t flags = bytes[0];
    std::cout << "Flags: 0x" << std::hex << std::setfill('0') << std::setw(2) << (uint32_t)flags << std::dec << std::endl;

    //Lecture des flags pour determiner quels champs sont presents
    //https://www.bluetooth.com/specifications/specs/fitness-machine-service-1-0/
    bool more_data = (flags & 0x01) == 0x01;
    bool average_speed_present = (flags & 0x02) == 0x02;
    bool instantaneous_cadence_present = (flags & 0x04) == 0x04;
    bool average_cadence_present = (flags & 0x08) == 0x08;
    bool total_distance_present = (flags & 0x10) == 0x10;
    bool resistance_level_present = (flags & 0x20) == 0x20;
    bool instantaneous_power_present = (flags & 0x40) == 0x40;
    bool average_power_present = (flags & 0x80) == 0x80;

    std::cout << "More Data: " << (more_data ? "Yes" : "No") << std::endl;
    std::cout << "Average Speed Present: " << (average_speed_present ? "Yes" : "No") << std::endl;
    std::cout << "Cadence Present: " << (instantaneous_cadence_present ? "Yes" : "No") << std::endl;
    std::cout << "Average Cadence Present: " << (average_cadence_present ? "Yes" : "No") << std::endl;
    std::cout << "Total Distance Present: " << (total_distance_present ? "Yes" : "No") << std::endl;
    std::cout << "Resistance Level Present: " << (resistance_level_present ? "Yes" : "No") << std::endl;
    std::cout << "Power Present: " << (instantaneous_power_present ? "Yes" : "No") << std::endl;
    std::cout << "Average Power Present: " << (average_power_present ? "Yes" : "No") << std::endl;

     // Lecture du champ instantaneous power
    if (instantaneous_power_present && bytes.size() >= 3) {
        uint16_t instantaneous_power = (bytes[7] << 8) | bytes[6];
        std::cout << "Instantaneous Power: " << instantaneous_power << " Watts" << std::endl;
    }
    else {
        std::cout << "Instantaneous Power: Not Present" << std::endl;
    }


    std::cout << std::endl;
}