#ifndef HEARTRATE_HPP
#define HEARTRATE_HPP

#include "simpleble/SimpleBLE.h"

namespace HeartRate {
    void read_heart_rate_measurement(const SimpleBLE::ByteArray& bytes);
}
#endif