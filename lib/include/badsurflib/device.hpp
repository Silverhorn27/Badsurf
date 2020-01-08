#ifndef DEVICE_H
#define DEVICE_H

#include "badsurflib/types.hpp"
#include "badsurflib/objects_def.hpp"
#include "badsurflib/udev/device.hpp"

#define IDENTIFY_SIZE  512

struct dc_dev {
    char* syspath;
    char* serial_no;
    const char* node_path;
    const char* model_str;
    byte identify[IDENTIFY_SIZE];
    unsigned hpa_enabled : 1;
    unsigned security_on : 1;
    unsigned ata_capable : 1;
    u64 capacity;
    u64 native_capacity;
    DC_Dev *next;
};

#endif // DEVICE_H
