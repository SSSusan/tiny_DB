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
    table.add_column( _column_name );
}

vector<vector<string> > & DBMS::select( const string &_column_name,
                                        const string &_value )
{
    size_t table_rows_count = table.getRowsCount();
    if ( table_rows_count == 0 )
        throw "No data type";

    return table.select( _column_name, _value );
}

vector<vector<string> > & DBMS::select( const string &__column_name,
                                        const string &_column_name,
                                        const string &_value )
{
    size_t table_rows_count = table.getRowsCount();
    if ( table_rows_count == 0 )
        throw "No type data";

    vector<string> columns_name( table.getColumns() );
    vector<string>::const_iterator ptr;
    ptr = find( columns_name.begin(), columns_name.end(), __column_name );
    if ( ptr == columns_name.end() )
        throw "No columns name";        // Illegal visit

    return table.select( __column_name, _column_name, _value );
}

void DBMS::update( const string &_column_name,
                   const string &_value,
                   const string &_which_column_name,
                   const string &_which_column_value )
{
    // Finish later!!!!!!!!!!
    table.update( _column_name, _value,
                  _which_column_name, _which_column_value );
}

void DBMS::insert( const vector<string> &_values )
{
    size_t columns_count = table.getColumnsCount();

    if ( _values.size() == columns_count )
        throw "invalid insert overflow";    // Fatal error

    table.insert( _values );
}

void DBMS::insert( const vector<string> &_columns,
                   const vector<string> &_values )
{
    if ( _columns.size() != _values.size() )
        throw "invalid insert";

    size_t columns_count = table.getColumnsCount();
    vector<string> columns( table.getColumns() );

    if ( _values.size() > columns_count )
        throw "invalid insert overflow";

    vector<string> __values;
    for ( size_t p = 0; p < columns_count; ++p )
    {
        size_t pi = 0;
        for ( pi = 0; pi < _columns.size(); ++pi )
        {
            if ( _columns[pi] == columns[p] )
            {
                __values.push_back( _columns[pi] );
                break;
            }
        }
        if ( pi == _columns.size() )
            __values.push_back( "NULL" );
    }
    ///////////////////////////////////
    if ( __values.size() != columns_count )
        throw "insert error";
    ///////////////////////////////////

    table.insert( __values );
}

void DBMS::delete_row( const string &_column_name,
                       const string &_value )
{
    size_t table_rows_count = table.getRowsCount();
    if ( table_rows_count == 0 )
        throw "No type data";

    vector<string> columns_name( table.getColumns() );
    vector<string>::const_iterator ptr;
    ptr = find( columns_name.begin(), columns_name.end(), _column_name );
    if ( ptr == columns_name.end() )
        throw "No column name";

    table.delete_row( _column_name, _value );
}

/* $end DDL */
