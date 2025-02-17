#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>

#include "badsurflib/types.hpp"
#include "badsurflib/procedure.hpp"

/**
 * Execute bash command thru popen()
 * and store full output to dynamic buffer that must be free()d
 */
char *cmd_output(char *command_line);

/*
 * Enable realtime scheduling for calling thread
 *
 * @param prio: 0 for min, 1 for max
 * @return 0 on success
 */
int dc_realtime_scheduling_enable_with_prio(int prio);

char *dc_dev_smartctl_text(char *dev_fs_path, char *options);

char *commaprint(u64 n, char *retbuf, size_t bufsize);

int procedure_perform_until_interrupt(DC_ProcedureCtx *actctx,
        ProcedureDetachedLoopCB callback, void *callback_priv);

int dc_dev_get_capacity(char *dev_fs_path, u64 *capacity);
int dc_dev_get_max_lba(char *dev_fs_path, u64 *max_lba);

int dc_dev_get_native_capacity(char *dev_fs_path, u64 *capacity);
int dc_dev_get_native_max_lba(char *dev_fs_path, u64 *max_lba);

// Difference is unit of capacity
int dc_dev_set_max_capacity(char *dev_fs_path, u64 capacity);
int dc_dev_set_max_lba(char *dev_fs_path, u64 lba);

int dc_dev_ata_capable(char *dev_fs_path);
int dc_dev_ata_identify(char *dev_fs_path, byte identify[]);

void dc_ata_ascii_to_c_string(byte *ata_ascii_string, unsigned int ata_length_in_words, char *dst);

#endif // UTILS_H
