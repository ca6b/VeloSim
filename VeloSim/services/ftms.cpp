
#include <bitset>
#include <iostream>
#include "ftms.hpp"
#include <iomanip>


void FTMS::read_indoor_bike_data(const SimpleBLE::ByteArray& bytes) {

    std::bitset<16> flags;
    uint16_t instantaneous_speed;
    uint16_t average_speed;
    uint16_t instantaneous_cadence;
    uint16_t average_cadence;
    uint32_t total_distance;
    uint8_t resistance_level;
    int16_t instantaneous_power;
    int16_t average_power;
    uint16_t total_energy;
    uint16_t energy_per_hour;
    uint8_t energy_per_minute;
    uint8_t heart_rate;
    uint8_t metabolic_equivalent;
    uint16_t elapsed_time;
    uint16_t remaining_time;

    std::cout << "Received Byte Array: ";
    for (const auto& byte : bytes) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;
    flags = std::bitset<16>((bytes[1] << 8) | bytes[0]);
    std::cout << "Flags: 0x" << std::hex << std::setfill('0') << std::setw(4) << flags.to_ulong() << std::dec << std::endl;
    std::cout << "Flags (Binary): " << flags << std::endl;

    //Lecture des flags pour determiner quels champs sont presents
    //https://www.bluetooth.com/specifications/specs/fitness-machine-service-1-0/

    size_t offset = 2;
    //Present if bit 0 of Flags field is set to 0
    if (!flags.test(0)) {
        instantaneous_speed = static_cast<uint16_t>(bytes[offset+1] << 8 | bytes[offset]);
        std::cout << "Instantaneous Speed: " << instantaneous_speed / 100 << " kph" << std::endl;
        offset += 2;
    }
    if (flags.test(1)) {
        average_speed = bytes[offset + 1] << 8 | bytes[offset];
        offset += 2;
    }
    if (flags.test(2)) {
        instantaneous_cadence = static_cast<uint16_t>(bytes[offset + 1] << 8 | bytes[offset]);
        std::cout << "Instantaneous Cadence: " << instantaneous_cadence/2 << " RPM" << std::endl;
        offset += 2;
    }
    if (flags.test(6)) {
        instantaneous_power = static_cast<int16_t>(bytes[offset + 1] << 8 | bytes[offset]);
        std::cout << "Instantaneous Power: " << instantaneous_power << " Watts" << std::endl;

    }    

    std::cout << std::endl;
}