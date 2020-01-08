#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cassert>

#include "badsurflib/procedure.hpp"
#include "badsurflib/utils.hpp"

#define _FILE_OFFSET_BITS 64

struct hpa_set_priv {
    int64_t max_lba;
};
typedef struct hpa_set_priv HpaSetPriv;

static int SuggestDefaultValue(DC_Dev *dev, DC_OptionSetting *setting) {
    if (!strcmp(setting->name, "max_lba")) {
        int64_t native_max_lba = dev->native_capacity / 512 - 1;  // TODO Request via ATA
        char *str;
        int r = asprintf(&str, "%ld", native_max_lba);
        assert(r != -1);
        setting->value = str;
    } else {
        return 1;
    }
    return 0;
}

static int Open(DC_ProcedureCtx *ctx) {
    HpaSetPriv *priv = (HpaSetPriv*)ctx->priv;

    dc_dev_set_max_lba((char*)ctx->dev->node_path, ctx->dev->native_capacity / 512 - 1);
    int ret = dc_dev_set_max_lba((char*)ctx->dev->node_path, priv->max_lba);
    //if (ret)
        // dc_log(DC_LOG_ERROR, "Command SET MAX ADDRESS EXT failed");
    return 0;
}

static void Close(DC_ProcedureCtx *ctx) {
    (void)ctx;
}

static DC_ProcedureOption options[] = {
    { "max_lba", "set maximum reachable LBA", offsetof(HpaSetPriv, max_lba), DC_ProcedureOptionType_eInt64 },
    { NULL }
};

DC_Procedure hpa_set = {
    .name = "hpa_set",
    .display_name = "Setup Host Protected Area",
    .help = "Sets maximum reachable LBA",
    .flags = DC_PROC_FLAG_INVASIVE | DC_PROC_FLAG_REQUIRES_ATA,
    .options = (DC_ProcedureOption*)options,
    .priv_data_size = sizeof(HpaSetPriv),
    .suggest_default_value = SuggestDefaultValue,
    .open = Open,
    .close = Close,
};

