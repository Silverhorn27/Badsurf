#ifndef SMARTPARSE_HPP
#define SMARTPARSE_HPP

#include "badsurflib/types.hpp"


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
char *smart_text_attrs_start(char *text);

void smart_attr_get_line(char *attrs_start);

/**
 * Example attribute row
 *
 * 193 Load_Cycle_Count        -O--CK   148   148   000    -    156729
 */
smart_attr_t smart_attr_from_line(char *attr_line);


#endif // SMARTPARSE_HPP
