#include "dbms.h"
#include <string>   // using std::string
#include <vector>   // using std::vector
#include <algorithm>// using std::find

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
bool DBMS::create_table( const string &_table_name )
{
    if ( is_bind )
        return false;

    if ( table.create( _table_name ) )
    {
        table.init( _table_name );
        is_bind = true;

        return true;
    }

    return false;
}

void DBMS::alter_table_add_column( const string &_column_name )
{
    if ( !is_bind )
        throw "No table bind.";

    table.add_column( _column_name );
}

vector<vector<string> > & DBMS::select( const string &_column_name,
                                        const string &_value )
{
    if ( !is_bind )
        throw "No data bind.";

    size_t table_rows_count = table.getRowsCount();
    if ( table_rows_count == 0 )
        throw "No data in this table.";

    return table.select( _column_name, _value );
}

vector<vector<string> > & DBMS::select( const string &__column_name,
                                        const string &_column_name,
                                        const string &_value )
{
    if ( !is_bind )
        throw "No table bind.";

    size_t table_rows_count = table.getRowsCount();
    if ( table_rows_count == 0 )
        throw "No data in this table.";

    vector<string> columns_name( table.getColumns() );
    vector<string>::const_iterator ptr;
    ptr = find( columns_name.begin(), columns_name.end(), __column_name );
    if ( ptr == columns_name.end() )
        throw "The column name do not exist.";        // Illegal visit

    return table.select( __column_name, _column_name, _value );
}

void DBMS::update( const string &_column_name,
                   const string &_value,
                   const string &_which_column_name,
                   const string &_which_column_value )
{    
    if ( !is_bind )
        throw "No table bind.";

    vector<string> _columns = table.getColumns();
    vector<string>::iterator p;

    // There is name column type
    p  = find( _columns.begin(), _columns.end(), _columns_name );
    if ( p == _columns.end() )
        throw "The column name do not exist. Cannot update.";

    // Cannot not locate
    p = find( _columns.begin(), _columns.end(), _which_column_name );
    if ( p == _columns.end() )
        throw "The column name do not exist. Cannot locate.";

    // There is no data
    if ( table.getRowsCount() == 0 )
        throw "No data in this table";

    // IF update key - value
    // Check whether can update key value
    if ( _column_name == table.getKey() )
    {
        vector<vector<string> > key_values;
        key_values = table.select( _columns[0] );

        p = find ( key_values.begin(), _columns.end, _column_name );
        if ( p != key_values.end() )
            throw "Cannot update the key's value.";
    }

    table.update( _column_name, _value,
                  _which_column_name, _which_column_value );
}

void DBMS::insert( const vector<string> &_values )
{
    if ( !is_bind )
        throw "No table bind";

    size_t columns_count = table.getColumnsCount();

    if ( _values.size() != columns_count )
        throw "Invalid insert. Values overflow.";    // Fatal error

    table.insert( _values );
}

void DBMS::insert( const vector<string> &_columns,
                   const vector<string> &_values )
{
    if ( !is_bind )
        throw "No table bind.";

    if ( _columns.size() != _values.size() )
        throw "Value size do not match the column size";

    size_t columns_count = table.getColumnsCount();
    vector<string> columns( table.getColumns() );

    if ( _values.size() > columns_count )
        throw "Invalid insert. Values overflow.";

    vector<string> __values;
    for ( size_t p = 0; p < columns_count; ++p )
    {
        size_t pi = 0;
        for ( pi = 0; pi < _columns.size(); ++pi )
        {
            if ( _columns[pi] == columns[p] )
            {
                __values.push_back( _values[pi] );
                break;
            }
        }
        if ( pi == _columns.size() )
            __values.push_back( "NULL" );
    }
    if ( __values.size() != columns_count )
        throw "Insert error. Try again.";

    table.insert( __values );
}

void DBMS::delete_row( const string &_column_name,
                       const string &_value )
{
    if ( !is_bind )
        throw "No table bind.";

    size_t table_rows_count = table.getRowsCount();
    if ( table_rows_count == 0 )
        throw "No data in this table.";

    vector<string> columns_name( table.getColumns() );
    vector<string>::const_iterator ptr;
    ptr = find( columns_name.begin(), columns_name.end(), _column_name );
    if ( ptr == columns_name.end() )
        throw "No this data record.";

    table.delete_row( _column_name, _value );
}

/* $end DDL */
