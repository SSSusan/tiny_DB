#ifndef TABLE_H
#define TABLE_H

#include <vector>   // using std::vecotr
#include <string>   // using std::string
#include <map>      // using std::map

using namespace std;

struct Table
{
    Table();

    string parent_dbname;
    string table_name;
    vector<string> colums;
    // don't know how to orgnize and set index
    vector<string> indexs;
    unsigned int colums_count;      // init(0)
    unsigned int index_count;       // init(0)

    const int get_colums_count();
    const int get_rows_count();
};

#endif // TABLE_H
