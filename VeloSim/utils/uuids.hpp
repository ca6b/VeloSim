#ifndef UUIDS_HPP
#define UUIDS_HPP

namespace UUIDs {
	//https://www.bluetooth.com/wp-content/uploads/Files/Specification/HTML/Assigned_Numbers/out/en/Assigned_Numbers.pdf?v=1707000142462
	
	constexpr char FITNESS_MACHINE_SERVICE_UUID[] = "00001826-0000-1000-8000-00805f9b34fb";
	constexpr char CYCLING_POWER_MEASUREMENT_CHARACTERISTIC[] = "00002ad2-0000-1000-8000-00805f9b34fb";

	constexpr char HEART_RATE_SERVICE_UUID[] = "0000180d-0000-1000-8000-00805f9b34fb";
	constexpr char HEART_RATE_MEASUREMENT[] = "00002a37-0000-1000-8000-00805f9b34fb";
}

#endif