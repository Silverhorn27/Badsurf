#include <cstdlib>
#include <cassert>
#include <ctype.h>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <sched.h>

#include "badsurflib/badsurflib.hpp"
#include "badsurflib/device.hpp"
#include "badsurflib/objects_def.hpp"
#include "badsurflib/procedure.hpp"
#include "badsurflib/utils.hpp"

#include "badsurflib/udev/udev.hpp"
#include "badsurflib/udev/device.hpp"
#include "badsurflib/udev/enumerate.hpp"

clockid_t DC_BEST_CLOCK;

DC_Ctx *dc_ctx_global = NULL;

int dc_init(void) {
    int r;
    DC_Ctx *ctx = (DC_Ctx*)calloc(1, sizeof(*ctx));
    if (!ctx)
        return 1;
    dc_ctx_global = ctx;

    // dc_log_set_callback(dc_log_default_func, NULL);
    // dc_log_set_level(DC_LOG_INFO);

    struct timespec dummy;
#ifdef CLOCK_MONOTONIC_RAW
    /* determine best available clock */
    DC_BEST_CLOCK = CLOCK_MONOTONIC_RAW;
    r = clock_gettime(DC_BEST_CLOCK, &dummy);
    if (r) {
        // dc_log(DC_LOG_WARNING, "CLOCK_MONOTONIC_RAW unavailable, using CLOCK_MONOTONIC\n");
        DC_BEST_CLOCK = CLOCK_MONOTONIC;
    }
#else
    DC_BEST_CLOCK = CLOCK_MONOTONIC;
#endif
    r = clock_gettime(DC_BEST_CLOCK, &dummy);
    if (r) {
        // dc_log(DC_LOG_ERROR, "Monotonic POSIX clock unavailable\n");
        return 1;
    }

    dc_realtime_scheduling_enable_with_prio(0);

#define PROCEDURE_REGISTER(x) { \
        extern DC_Procedure x; \
        dc_procedure_register(&x); }
    PROCEDURE_REGISTER(hpa_set);
    PROCEDURE_REGISTER(read_test);
    PROCEDURE_REGISTER(smart_show);
#undef PROCEDURE_REGISTER
    return 0;
}

void dc_finish(void) {
    free(dc_ctx_global);
    dc_ctx_global = NULL;
}

static void dev_list_build(DC_DevList *dc_devlist);
static void dev_list_fill_info(DC_DevList *list);

DC_DevList *dc_dev_list(void) {
    DC_DevList *list = (DC_DevList*)calloc(1, sizeof(*list));
    assert(list);
    list->arr = NULL;
    list->arr_size = 0;
    dev_list_build(list);
    dev_list_fill_info(list);
    return list;
}

void dc_dev_list_free(DC_DevList *list) {
    while (list->arr) {
        DC_Dev *next = list->arr->next;
        free(list->arr);
        list->arr = next;
    }
    free(list);
}

int dc_dev_list_size(DC_DevList *list) {
    return list->arr_size;
}

DC_Dev *dc_dev_list_get_entry(DC_DevList *list, int index) {
    DC_Dev *dev = list->arr;
    while (index > 0) {
        if (!dev)
            return NULL;
        dev = dev->next;
        index--;
    }
    return dev;
}

static void dev_list_build(DC_DevList *dc_devlist) {
    udev::enumerate enu;

    enu.match_subsystem("block");

    auto found_devs = enu.get();
    for (auto &d : found_devs) {
        DC_Dev *dc_dev = (DC_Dev*)calloc(1, sizeof(*dc_dev));
        assert(dc_dev);
        dc_dev->node_path = d.node().c_str();
        dc_dev->model_str = d.property("ID_MODEL").c_str();

        dc_dev->security_on =
            (*(d.property("ID_ATA_FEATURE_SET_SECURITY_ENABLED").c_str()) == '1');
        dc_dev->hpa_enabled =
            (*(d.property("ID_ATA_FEATURE_SET_HPA_ENABLED").c_str()) == '1');

        dc_dev->next = dc_devlist->arr;
        dc_devlist->arr = dc_dev;
        dc_devlist->arr_size++;
    }
}

static void dev_list_fill_info(DC_DevList *list) {
    DC_Dev *dev = list->arr;
    while (dev) {
        memset(dev->identify, 0, IDENTIFY_SIZE);
        dev->ata_capable = !dc_dev_ata_identify((char*)dev->node_path, dev->identify);

        if (dev->ata_capable) {
            // get capacity: u64
            dc_dev_get_capacity((char*)dev->node_path, &dev->capacity);
            // get native_capacity: u64
            dc_dev_get_native_capacity((char*)dev->node_path, &dev->native_capacity);
            // get serial_no: String
            dev->serial_no = (char*)calloc(1, 21);
            dc_ata_ascii_to_c_string(dev->identify + 20, 10, dev->serial_no);
            // get model: String
            dev->model_str = (char*)calloc(1, 41);
            dc_ata_ascii_to_c_string(dev->identify + 54, 20, (char*)dev->model_str);

            // ATA Identify debug output
            // for (int i = 0; i < 512; i++)
            //     fprintf(stderr, "%c", dev->identify[i]);
        }
        // if (!dev->model_str)
        //     dev_modelname_fill(dev);
        // dev_mounted_fill(dev);
        dev = dev->next;
    }
}
