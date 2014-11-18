#ifndef TABLE_H
#define TABLE_H

#include <string>   // using std::string
#include <vector>   // using std::vector

using namespace std;

class Table
{
public:
    Table();
    Table( const string &_name );

    void open();
private:
    string name;        // init("NULL")
    string data_file;   // init("data")

    /*
     * Core data orgnization method
     *  - 2D table
     */
    vector<string> colums;      // Each operator with colums must
    size_t colums_count;        // update colums_count


    void read_data();
    void save_data();
};

#endif // TABLE_H
