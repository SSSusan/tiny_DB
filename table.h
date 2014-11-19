#ifndef TABLE_H
#define TABLE_H

#include <string>   // using std::string
#include <vector>   // using std::vector
//#include <list>     // using std::list

using namespace std;

class Row
{
public:
    Row();
    string key_value;
    vector<string> values;
};

class Table
{
public:
    Table();
    Table( const string &_name );
    void init( const string &_name );

    void open();
private:
    string name;        // init("NULL")
    string data_file;   // init("NULL")

    string key;
    string index;

    /*
     * Core data orgnization method
     *  - 2D table
     */

    /*
     * Each operator with colums must update colums_count
     */
    vector<string> colums;
    size_t colums_count;

    /*
     * Each operator with rows must update rows_count
     */
    vector<Row> rows;
    size_t rows_count;

    void read_data();
    /*
     *  When finish each table operate must call it
     */
    void save_data();
};

#endif // TABLE_H
