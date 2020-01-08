#ifndef BADSURFLIB_HPP
#define BADSURFLIB_HPP

#include <ctime>

#include "badsurflib/objects_def.hpp"
#include "badsurflib/device.hpp"
#include "badsurflib/procedure.hpp"


extern clockid_t DC_BEST_CLOCK;

// this should not be accessed from applications, for internal usage only
struct dc_ctx {
    DC_Procedure *procedure_list;
    int nb_procedures;
};

extern DC_Ctx *dc_ctx_global;

struct dc_dev_list {
    DC_Dev *arr;
    int arr_size;
};

/**
 * This func initializes underlying libraries,
 * internal structures connectivity object, and so on.
 * Call this once at app beginning
 * And store returned pointer for further use of lib.
 */
int dc_init(void);
void dc_finish(void);

/**
 * Return array of testable block devices
 */
DC_DevList *dc_dev_list(void);
void dc_dev_list_free(DC_DevList *list);
int dc_dev_list_size(DC_DevList *list);
DC_Dev *dc_dev_list_get_entry(DC_DevList *list, int index);

#endif // BADSURFLIB_HPP
