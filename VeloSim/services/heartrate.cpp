#include "heartrate.hpp"

#include <iomanip>
#include <iostream>


void HeartRate::read_heart_rate_measurement(const SimpleBLE::ByteArray& bytes)
{
    uint8_t flags = bytes[0];
    std::cout << "Flags: 0x" << std::hex << std::setfill('0') << std::setw(2) << (uint32_t)flags << std::dec << std::endl;

    //Lecture des champs selon les flags
    //https://www.bluetooth.com/specifications/specs/heart-rate-service-1-0/
    bool heart_rate_value_format = (flags & 0x01) == 0x01;
    bool sensor_contact_status = (flags & 0x06) >> 1;
    bool energy_expended_status = (flags & 0x08) == 0x08;
    bool rr_interval_present = (flags & 0x10) == 0x10;

    //todo: changer selon format flag
    uint8_t heartRateValue = bytes[1];
    std::cout << "Heart Rate Value: " << static_cast<int>(heartRateValue) << " bpm" << std::endl;

    if (energy_expended_status && bytes.size() >= 4) {
        uint16_t energy_expended_value = (bytes[2] << 8) | bytes[3];
        std::cout << "Energy Expended: " << energy_expended_value << " Joules" << std::endl;
    }

    if (rr_interval_present && bytes.size() >= 6) {
        uint16_t rr_interval_value = (bytes[4] << 8) | bytes[5];
        std::cout << "RR-Interval: " << rr_interval_value << " milliseconds" << std::endl;
    }

    std::cout << std::endl;
}
