#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "badsurflib/badsurflib.hpp"
#include "badsurflib/device.hpp"
#include "badsurflib/smart_parse.hpp"
#include <pthread.h>
#include <cstddef>

#define DC_PROC_FLAG_INVASIVE 1
#define DC_PROC_FLAG_REQUIRES_ATA 2

enum Api {
    Api_eAta,
    Api_ePosix,
};

typedef enum {
    DC_ProcedureOptionType_eInt64,
    DC_ProcedureOptionType_eString,
} DC_ProcedureOptionType;

typedef struct dc_procedure_option {
    const char *name;
    const char *help;
    int offset;
    DC_ProcedureOptionType type;
} DC_ProcedureOption;

typedef struct dc_option_setting {
    const char *name;
    char *value;
} DC_OptionSetting;

struct dc_procedure {
    const char *name;
    const char *display_name;
    const char *help;
    int flags;  // For DC_PROC_FLAG_*
    DC_ProcedureOption *options;
    int options_num;
    size_t priv_data_size;
    int (*suggest_default_value)(DC_Dev *dev, DC_OptionSetting *setting);
    int (*open)(DC_ProcedureCtx *procedure);
    int (*perform)(DC_ProcedureCtx *ctx);
    void (*close)(DC_ProcedureCtx *ctx);
    DC_Procedure *next;
};

int dc_procedure_register(DC_Procedure *procedure);
DC_Procedure *dc_find_procedure(const char *name);
int dc_get_nb_procedures();
DC_Procedure *dc_get_next_procedure(DC_Procedure *prev);
DC_Procedure *dc_get_procedure_by_index(int index);

typedef struct dc_rational {
    u64 num;  // numerator
    u64 den;  // denominator
} DC_Rational;

typedef enum {
    DC_BlockStatus_eOk = 0,
    DC_BlockStatus_eError,    // Generic error condition
    DC_BlockStatus_eTimeout,  // Timeout
    DC_BlockStatus_eUnc,      // Uncorrectable Data Error
    DC_BlockStatus_eIdnf,     // Sector ID Not Found
    DC_BlockStatus_eAbrt,     // Aborted command
    DC_BlockStatus_eAmnf,     // Address Mark Not Found
} DC_BlockStatus;

typedef struct dc_block_report {
    u64 lba;  // block start lba
    u64 sectors_processed;
    u64 blk_access_time; // in mcs
    DC_BlockStatus blk_status;
} DC_BlockReport;

struct dc_procedure_ctx {
    void* priv; // for procedure private context
    DC_Dev *dev; // device which is operated
    DC_Procedure *procedure;
    u64 blk_size;  // set by procedure on .open()
    u64 current_lba;  // updated by procedure on .perform()
    DC_Rational progress;  // updated by procedure on .perform()
    unsigned interrupt : 1; // if set to 1 by frontend, then looped processing must stop
    // TODO interrupt is now meant for loop, think of interrupting blocking perform operation
    unsigned finished : 1; // if 1, then looped processing has finished
    DC_BlockReport report; // updated by procedure on .perform()
    void *user_priv;  // pointer to user interface private data
    smart_out_data smart_attrs;
    struct timespec time_pre, time_post;  // block processing timing
};

int dc_procedure_open(DC_Procedure *procedure, DC_Dev *dev, DC_ProcedureCtx **ctx, DC_OptionSetting options[]);
int dc_procedure_perform(DC_ProcedureCtx *ctx);
void dc_procedure_close(DC_ProcedureCtx *ctx);

typedef int (*ProcedureDetachedLoopCB)(DC_ProcedureCtx *ctx, void *callback_priv);
int dc_procedure_perform_loop(DC_ProcedureCtx *ctx, ProcedureDetachedLoopCB callback, void *callback_priv);
int dc_procedure_perform_loop_detached(DC_ProcedureCtx *ctx, ProcedureDetachedLoopCB callback,
        void *callback_priv, pthread_t *tid
        );

// Functions used internally by procedure implementations for timing
void _dc_proc_time_pre(DC_ProcedureCtx *ctx);
void _dc_proc_time_post(DC_ProcedureCtx *ctx);

#endif // PROCEDURE_H
