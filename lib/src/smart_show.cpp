#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>

#include "badsurflib/types.hpp"
#include "badsurflib/procedure.hpp"
#include "badsurflib/utils.hpp"

struct smart_show_priv {
};
typedef struct smart_show_priv SmartShowPriv;

/**
 * Represents each column in SMART attributes table
 */
typedef struct smart_attr {
    char *attr_name;
    u8 id;
    int value;
    int worst;
    int threshold;
    bool fail : 1;
    u64 raw;
} smart_attr_t;

/**
 * That's how start of attributes table represented
 * ID# ATTRIBUTE_NAME          FLAGS    VALUE WORST THRESH FAIL RAW_VALUE
 *
 * FLAGS column is unnecessary
 */
static char *smart_text_attrs_start(char *text)
{
    assert(text != NULL);

    char ch = *text;
    for (size_t i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        if (ch == '\n') {
            if (!strncmp(text + i, "ID#", 3)) {
                return text + i + 1;
            }
        }
    }
    return NULL;
}

static void smart_attr_get_line(char *attrs_start)
{
    while (*attrs_start++ != '\n');
}

/**
 * Example attribute row
 *
 * 193 Load_Cycle_Count        -O--CK   148   148   000    -    156729
 */
static smart_attr_t smart_attr_from_line(char *attr_line)
{
    smart_attr_t attr;

    /* get id */
    if (isdigit(attr_line[2])) {
        attr.id = atoi(attr_line);
    }

    /* get attribute name */
    attr_line = &attr_line[4];
    char *name = attr_line;

    while (*attr_line++ != ' ');

    int name_len = attr_line - name - 1;
    attr.attr_name = (char*)malloc(sizeof(char) * (name_len + 1));
    assert(attr.attr_name != NULL);

    strncpy(attr.attr_name, name, name_len);

    /* replace underscores with spaces */
    for (int i = 0; attr.attr_name[i] != '\0'; i++) {
        if (attr.attr_name[i] == '_') {
            attr.attr_name[i] = ' ';
        }
    }

    /* set pointer to start of values and get them */
    while (!isdigit(*attr_line++));
    sscanf(attr_line, "%d%3d%3d", &attr.value, &attr.worst, &attr.threshold);

    /* get fail value */
    attr.fail = (attr_line[18] != '-') ? true : false;

    /* get raw value */
    attr.raw = atoll(&attr_line[23]);

    return attr;
}

static int Open(DC_ProcedureCtx *ctx) {
    char *text = dc_dev_smartctl_text((char*)ctx->dev->node_path, " -A -f brief ");
    if (text) {
        char *attrs_start = smart_text_attrs_start(text);

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

