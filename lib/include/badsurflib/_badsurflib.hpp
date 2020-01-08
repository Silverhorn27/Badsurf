#ifndef BADSURFLIB_H
#define BADSURFLIB_H

#include <ctime>

#include <vector>

#include "badsurflib/objects_def.hpp"
#include "badsurflib/device.hpp"
#include "badsurflib/procedure.hpp"

extern clockid_t DC_BEST_CLOCK;

// this should not be accessed from applications, for internal usage only
struct dc_ctx {
    std::vector<DC_Procedure> procedures;
};

extern DC_Ctx *dc_ctx_global;

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
std::vector<DC_Dev> *dc_dev_vec(void);

#endif // BADSURFLIB_H
