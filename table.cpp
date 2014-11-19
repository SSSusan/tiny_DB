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

Table::Table()
    :name("NULL"), data_file("NULL")
{
}

Table::Table( const string &_name )
    :name(_name), data_file(_name)
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
    colums = __s.split();
    colums_count = colums.size();

    /////////////////////////////////////////
    for ( size_t i = 0; i < colums_count; ++i)
        cout << colums[i] << endl;
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

    if ( colums_count ) {
        vector<string>::iterator i;
        string _colums;
        for ( i = colums.begin(); i != (colums.end()-1); ++i ) {
            _colums += (*i);
            _colums += ',';
        }
        delete_last_comma( _colums );
        outfile << _colums << endl;
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
