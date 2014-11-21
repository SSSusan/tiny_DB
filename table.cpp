#include "table.h"
#include "_string.h"
#include <string>   // using std::string
#include <fstream>  // using std::ifstream, std::ofstream
#include <iostream> // using std::cout

using namespace std;

Row::Row()
    :key_value("NULL")
{
}

Row::Row(const vector<string> &_values )
    :values(_values), key_value(values[0])
{
}

Table::Table()
    :name("NULL"), data_file("NULL"), key("NULL"), index("NULL")
{
}

Table::Table( const string &_name )
    :name(_name), data_file(_name), key("NULL"), index("NULL")
{
    open ();
}

void Table::init( const string &_name )
{
    name = _name;
    data_file = _name;

    open();
}

void Table::open()
{    
    try {
        read_data();
    } catch (const char *e) {
        cout << e << endl;
    }
}
/* $begin DDL */
void Table::add_column( const string &_column_name )
{
    columns.push_back( _column_name );
    columns_count = columns.size();
}
/* $end DDL */

/* $begin DML */
vector<vector<string> > &
Table::select ( const string &_column_name,
                const string &_value)
{
    // Clear stack
    result_rows.clear();

    int p = -1;
    for ( size_t i = 0; i < columns_count; ++i )
        if ( columns[i] == _column_name )
        {
            p = i;
            break;
        }
    //////////////////////////////////////////
    if ( p == -1)
        throw "column_name no found.";      // fatal error
    vector<Row>::iterator index;
    for ( index = rows.begin(); index != rows.end(); ++index )
    {
        if ( (*index).values[p] == _value )
            result_rows.push_back( (*index).values );
    }

    return result_rows;
}

vector<vector<string> > &
Table::select( const string &__column_name,
               const string &_column_name,
               const string &_value)
{
    // Clear stack
    result_rows.clear();

    int po = -1, pi = -1;
    for ( size_t i = 0; i < columns_count; ++i )
    {
        if ( columns[i] == _column_name )
            pi = (int)i;
        if ( columns[i] == __column_name )
            po = (int)i;
    }
    ///////////////////////////////////////////
    // IF type no found, thow fatal error
    // Of cource if shouldn't happen here, just debug
    if ( po == -1 || pi == -1 )
        throw "column_name no found.";   // fatal error
    ///////////////////////////////////////////
    vector<Row>::iterator index;
    for ( index = rows.begin(); index != rows.end(); ++index )
    {
        vector<string> _result_row;
        if ( (*index).values[pi] == _value )
        {
            /*
             *  IF out type equal to key, THEN just out key_value
             */
            if ( columns[po] == key )       // equal to ( po == 0 )
                _result_row.push_back( (*index).key_value );
            else
            {
                _result_row.push_back( (*index).key_value );
                _result_row.push_back( (*index).values[po] );
            }

            result_rows.push_back( _result_row );
        }
    }

    return result_rows;
}

/*
 *  Direct modify core data variable
 */
void Table::update( const string &_column_name,
                    const string &_value,
                    const string &_which_column_name,
                    const string &_which_column_value)
{
    int pi = -1, po = -1;
    for ( size_t i = 0; i < columns_count; ++i )
    {
        if ( columns[i] == _column_name )
            po = i;
        if ( columns[i] == _which_column_name )
            pi = i;
    }
    ///////////////////////////////////////////////
    if ( pi == -1 || po == -1 )
        throw "column_name no found.";
    ///////////////////////////////////////////////

    if ( columns[po] == key )
        throw "No way to modify key.";

    vector<Row>::iterator index;
    for ( index = rows.begin(); index != rows.end(); ++index )
    {
        try {
            if ( (*index).values[pi] == _which_column_value )
                (*index).values[po] = _value;
        } catch ( const char *e) {
            cout << e << endl;
        }
    }
}

void Table::insert( const vector<string> &_values )
{
    Row _row( _values );
    rows.push_back( _row );
    rows_count = rows.size();
}

void Table::delete_row( const string &_column_name,
                        const string &_value )
{
    // Must understand vector more, especially copy constructor
}

/* $end DML*/

void Table::read_data()
{
    ifstream infile;

    const char *_data_file = data_file.c_str();
    infile.open( _data_file );
    if ( infile.fail() )
        throw "Data read fail.";     // Fatal error!

    string _s;
    getline( infile, _s );
    _String __s( _s );
    columns = __s.split();
    columns_count = columns.size();

    // Init key
    key = columns[0];
    /////////////////////////////////////////
    for ( size_t i = 0; i < columns_count; ++i)
        cout << columns[i] << endl;
    /////////////////////////////////////////

    infile.close();
}

void delete_last_comma( string &_s )
{
    // has comma
    if ( _s.find(',') != string::npos )
        _s.erase( _s.size() - 1 );
}

void Table::save_data()
{
    ofstream outfile;

    const char *_data_file = data_file.c_str();
    outfile.open( _data_file );
    if ( outfile.fail() )
        throw "Data save fail.";    // Fatal error!

    if ( columns_count ) {
        vector<string>::iterator i;
        string _columns;
        for ( i = columns.begin(); i != (columns.end()-1); ++i ) {
            _columns += (*i);
            _columns += ',';
        }
        delete_last_comma( _columns );
        outfile << _columns << endl;
    }

    if ( rows_count ) {
        vector<Row>::iterator ix;
        for ( ix = rows.begin(); ix != rows.end(); ++ix ) {
            Row the_row = (*ix);
            if ( the_row.key_value != "NULL" ) {
                string _row;
                vector<string>::iterator iy;
                for ( iy = the_row.values.begin();
                      iy != the_row.values.end(); ++iy ) {
                    _row += (*iy);
                    _row += ',';
                }
                delete_last_comma( _row );
                outfile << _row << endl;
            }
        }
    }

    outfile.close();
}
