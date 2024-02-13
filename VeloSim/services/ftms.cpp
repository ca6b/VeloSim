
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
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte & 0xff) << " ";
    }
    std::cout << std::dec << std::endl;
    flags = std::bitset<16>((bytes[1] << 8) | bytes[0]);
    std::cout << "Flags (Binary): " << flags << std::endl;

    //Lecture des flags pour determiner quels champs sont presents
    //https://www.bluetooth.com/specifications/specs/fitness-machine-service-1-0/

    if (bytes.size() == 8) {

        size_t offset = 2;
        //Instant Speed is present if bit 0 is set to 0. All other fields present if flag set to 1
        if (!flags.test(0)) {
            //Units: 1/100 kph
            memcpy(&instantaneous_speed, &bytes[offset], sizeof(uint16_t));
            std::cout << "Instantaneous Speed: " << instantaneous_speed / 100 << " kph" << std::endl;
            offset += 2;
        }

        if (flags.test(1)) {
            //Units: 1/100 kph
            memcpy(&average_speed, &bytes[offset], sizeof(uint16_t));
            std::cout << "Average Speed: " << average_speed / 100 << " kph" << std::endl;
            offset += 2;
        }
        if (flags.test(2)) {
            //Units: 1/2 RPM
            memcpy(&instantaneous_cadence, &bytes[offset], sizeof(uint16_t));
            std::cout << "Instantaneous Cadence: " << instantaneous_cadence / 2 << " RPM" << std::endl;
            offset += 2;
        }
        if (flags.test(3)) {
            //Units: 1/2 RPM
            memcpy(&average_cadence, &bytes[offset], sizeof(uint16_t));
            std::cout << "Average Cadence: " << average_cadence / 2 << " RPM" << std::endl;
            offset += 2;
        }
        if (flags.test(4)) {
            //Units: Metre
            //FTMS spec: Total distance is a uint24.
            memcpy(&total_distance, &bytes[offset], sizeof(uint32_t));
            std::cout << "Total Distance: " << total_distance << " metres" << std::endl;
            offset += 4;
        }
        if (flags.test(5)) {
            //Unit is 1
            memcpy(&resistance_level, &bytes[offset], sizeof(uint8_t));
            std::cout << "Resistance Level: " << resistance_level << " units" << std::endl;
            offset += 1;
        }
        if (flags.test(6)) {
            //Units: Watts
            memcpy(&instantaneous_power, &bytes[offset], sizeof(int16_t));
            std::cout << "Instantaneous Power: " << instantaneous_power << " Watts" << std::endl;
            offset += 2;
        }
        if (flags.test(7)) {
            //Units: Watts
            memcpy(&average_power, &bytes[offset], sizeof(int16_t));
            std::cout << "Average Power: " << average_power << " Watts" << std::endl;
            offset += 2;
        }
        if (flags.test(8)) {
            //Units: Kcal
            memcpy(&total_energy, &bytes[offset], sizeof(uint16_t));
            std::cout << "Total Energy: " << total_energy << " cal" << std::endl;
            offset += 2;
            memcpy(&energy_per_hour, &bytes[offset], sizeof(uint16_t));
            std::cout << "Energy per Hour: " << energy_per_hour << " cal" << std::endl;
            offset += 2;
            memcpy(&energy_per_minute, &bytes[offset], sizeof(uint8_t));
            std::cout << "Energy per Minute: " << energy_per_minute << " cal" << std::endl;
            offset += 1;
        }
        if (flags.test(9)) {
            //Units: BPM
            memcpy(&heart_rate, &bytes[offset], sizeof(int8_t));
            std::cout << "Heart Rate: " << heart_rate << " bpm" << std::endl;
            offset += 1;
        }
        if (flags.test(10)) {
            //Units: 1/10 metabolic equivalent
            memcpy(&metabolic_equivalent, &bytes[offset], sizeof(int8_t));
            std::cout << "Instantaneous Power: " << metabolic_equivalent / 10 << " metabolic equivalent" << std::endl;
            offset += 1;
        }
        if (flags.test(11)) {
            //Units: second
            memcpy(&elapsed_time, &bytes[offset], sizeof(uint16_t));
            std::cout << "Elapsed Time: " << elapsed_time << " seconds" << std::endl;
            offset += 2;
        }
        if (flags.test(12)) {
            //Units: second
            memcpy(&remaining_time, &bytes[offset], sizeof(uint16_t));
            std::cout << "Remaining Time: " << remaining_time << " seconds" << std::endl;
            //offset += 2; Remaining fields are reserved for future use
        }
    }
    std::cout << std::endl;
}