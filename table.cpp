#include "table.h"
#include "_string.h"
#include <string>   // using std::string
#include <fstream>  // using std::ifstream, std::ofstream
#include <iostream> // using std::cout

using namespace std;

Table::Table()
    :name("NULL"), data_file("data")
{
}

Table::Table( const string &_name )
    :name(_name), data_file("data")
{
    open ();
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

    // Bebug
    cout << data_file << endl;

    infile.open( _data_file );
    if ( infile.fail() )
        throw "Data read fail.";     // Fatal error!

    string _s;
    getline( infile, _s );
    _String __s( _s );
    colums = __s.split();
    colums_count = colums.size();

    // Debug
    for ( size_t i = 0; i < colums_count; ++i)
        cout << colums[i] << endl;

    infile.close();
}

void Table::save_data()
{

}
