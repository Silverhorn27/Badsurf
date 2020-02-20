#ifndef ATA_H
#define ATA_H

#include "badsurflib/types.hpp"
#include <linux/hdreg.h>

typedef struct ata_command {
    ide_task_request_t task;
    // This struct is not suitable for HDIO_ commands which involve data transfer to userspace.
    // Because you need buffer right below `task`.
} AtaCommand;

void prepare_ata_command(AtaCommand *cmd_buffer, int cmd, u64 lba, int size_in_sectors);

#endif  // ATA_H
