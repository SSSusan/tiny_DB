#include "table.h"

Table::Table()
    :colums_count(0), index_count(0)
{
}

const int Table::get_colums_count()
{
    return colums_count;
}
