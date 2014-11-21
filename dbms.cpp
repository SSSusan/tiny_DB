#include "dbms.h"
#include <string>   // using std::string

using namespace std;

DBMS::DBMS()
    :is_bind(false), table_name("NULL")
{
}

DBMS::DBMS( const string &_table_name )
    :is_bind(true), table_name(_table_name),
      table(_table_name)
{
}

DBMS::~DBMS()
{
}

bool DBMS::bind( const char *_table_name )
{
    string _table_name_s = _table_name;
    return bind( _table_name_s );
}

bool DBMS::bind( const string &_table_name )
{
    if ( is_bind )
        return false;

    table_name = _table_name;
    is_bind = true;
    table.init( _table_name );

    return true;
}

void DBMS::unbind()
{
    is_bind = false;
    table_name = "NULL";
}

/* $begin DDL */
void DBMS::alter_table_add_column( const string &_column_name ){

}

/* $end DDL */
