#ifndef FTMS_HPP
#define FTMS_HPP

#include "simpleble/SimpleBLE.h"
#include <string>

namespace FTMS {
    void read_indoor_bike_data(const SimpleBLE::ByteArray& bytes);
}
#endif