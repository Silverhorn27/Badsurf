#ifndef SCSI_H
#define SCSI_H

#include <unistd.h>
#include <scsi/sg.h>

#include "badsurflib/ata.hpp"
#include "badsurflib/types.hpp"
#include "badsurflib/procedure.hpp"

typedef struct scsi_command {
    sg_io_hdr_t io_hdr;  // Helper struct used with ioctl(SG_IO), has some output members
    u8 scsi_cmd[16];  // Command buffer
    u8 sense_buf[32];  // Output diagnostic info from device
} ScsiCommand;

#define ERROR_BIT_AMNF  1
#define ERROR_BIT_NM    2
#define ERROR_BIT_ABRT  4
#define ERROR_BIT_MCR   8
#define ERROR_BIT_IDNF  16
#define ERROR_BIT_MC    32
#define ERROR_BIT_UNC   64
#define ERROR_BIT_NA1   128

#define STATUS_BIT_ERR   1
#define STATUS_BIT_NA3   2
#define STATUS_BIT_NA2   4
#define STATUS_BIT_DRQ   8
#define STATUS_BIT_NA1   16
#define STATUS_BIT_DF    32
#define STATUS_BIT_DRDY  64
#define STATUS_BIT_BSY   128

typedef struct scsi_ata_return_descriptor {
    u8 descriptor[14];
    u8 error;
    u8 status;
    u64 lba;
} ScsiAtaReturnDescriptor;

void prepare_scsi_command_from_ata(ScsiCommand *scsi_cmd, AtaCommand *ata_cmd);

void fill_scsi_ata_return_descriptor(ScsiAtaReturnDescriptor *scsi_ata_ret, ScsiCommand *scsi_cmd);

int get_sense_key_from_sense_buffer(u8 *buf);

DC_BlockStatus scsi_ata_check_return_status(ScsiCommand *scsi_command);

#endif  // SCSI_H
