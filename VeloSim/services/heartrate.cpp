#include "heartrate.hpp"

#include <iomanip>
#include <iostream>
#include <bitset>


void HeartRate::read_heart_rate_measurement(const SimpleBLE::ByteArray& bytes)
{
    std::bitset<8> flags;
    uint8_t heart_rate_measurement_8;
    uint16_t heart_rate_measurement_16;
    uint16_t energy_expended;
    uint16_t* rr_interval;

    std::cout << "Received Byte Array: ";
    for (const auto& byte : bytes) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;
    flags = std::bitset<8>(bytes[0]);
    std::cout << "Flags: 0x" << std::hex << std::setfill('0') << std::setw(2) << flags << std::dec << std::endl;
    std::cout << "Flags (Binary): " << flags << std::endl;

    //Lecture des champs selon les flags
    //https://www.bluetooth.com/specifications/specs/heart-rate-service-1-0/
    
    size_t offset = 1;
    //Heart rate measurement resolution is 8 bits if bit_0 == 0 else 16 bits
    if (!flags.test(0)) {
        heart_rate_measurement_8 = static_cast<uint8_t>(bytes[offset]);
        std::cout << "HR_8: " << static_cast<int>(heart_rate_measurement_8) << " bpm" << std::endl;

        offset += 1;
    }
    else {
        heart_rate_measurement_16 = static_cast<uint16_t>(bytes[offset + 1] << 8 | bytes[offset]);
        std::cout << "HR_16: " << heart_rate_measurement_16 << " bpm" << std::endl;
        offset += 2;
    }

    if (!flags.test(1)) {
        std::cout << "No sensor contact detected!" << std::endl;
    }

    if (flags.test(2)) {
        std::cout << "Sensor contact supported!" << std::endl;
    }

    if (flags.test(3)) {
        energy_expended = static_cast<uint16_t>(bytes[offset + 1] << 8 | bytes[offset]);
        std::cout << "HR_16: " << energy_expended << " joule" << std::endl;
        offset += 2;
    }

    if (flags.test(4)) {
        
    }
    //flags[5-7] reserved for future use

    std::cout << std::endl;
}
