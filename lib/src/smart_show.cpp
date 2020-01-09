#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>

#include "badsurflib/smart_parse.hpp"
#include "badsurflib/types.hpp"
#include "badsurflib/procedure.hpp"
#include "badsurflib/utils.hpp"

struct smart_show_priv {
    std::vector<smart_attr_t> v_attrs;
    u8 n_attrs;
};
typedef struct smart_show_priv SmartShowPriv;

/**
 * Represents each column in SMART attributes table
 */

static int Open(DC_ProcedureCtx *ctx) {
    char *text = dc_dev_smartctl_text((char*)ctx->dev->node_path, " -A -f brief ");
    SmartShowPriv *priv = (SmartShowPriv*)ctx->priv;

    if (text) {
        std::vector<smart_attr_t> attrs;
        u8 n_attrs = smart_attrs_from_text(attrs, text);

        priv->v_attrs = attrs;
        priv->n_attrs = n_attrs;

        free(text);
        return 0;
    } else {
        // dc_log(DC_LOG_ERROR, "%s", "Getting SMART attributes failed");
        return 1;
    }
}

static void Close(DC_ProcedureCtx *ctx) {
    (void)ctx;
}

DC_Procedure smart_show = {
    .name = "smart_show",
    .display_name = "Show SMART attributes",
    .flags = DC_PROC_FLAG_REQUIRES_ATA,
    .priv_data_size = sizeof(SmartShowPriv),
    .open = Open,
    .close = Close,
};

