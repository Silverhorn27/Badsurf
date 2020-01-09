#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cassert>

#include "badsurflib/smart_parse.hpp"
#include "badsurflib/types.hpp"


char *smart_text_attrs_start(char *text)
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

void smart_attr_get_line(char *attrs_start)
{
    while (*attrs_start++ != '\n');
}

/**
 * Example attribute row
 *
 * 193 Load_Cycle_Count        -O--CK   148   148   000    -    156729
 */
smart_attr_t smart_attr_from_line(char *attr_line)
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
