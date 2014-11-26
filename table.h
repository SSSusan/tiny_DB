#ifndef TABLE_H
#define TABLE_H

#include <string>   // using std::string
#include <vector>   // using std::vector

using namespace std;

class Row
{
public:
    Row();
    Row( const vector<string> &_values );
    vector<string> values;
    string key_value;           // init(values[0])
};

class Table
{
public:
    Table();
    Table( const string &_name );
    void init( const string &_name );
    bool create( const string &_name );

    /*
     *  Provide APIs for DBMS to get table's infomation
     */
    const string & getName() const { return name; }
    const string & getKey() const { return key; }
    const string & getIndex() const { return index; }

    const vector<string> & getColumns() const { return columns; }

    const size_t & getColumnsCount() const { return columns_count; }
    const size_t & getRowsCount() const { return rows_count; }

    /*
     * Just realize the function, no ERROR check
     */
    /* $start DDL */
    void add_column( const string &_column_name );
    /* $end DDL */
    /* $start DML */
    vector<vector<string> > & select( const string &_column_name,
                                      const string &_value );
    vector<vector<string> > & select( const string &__column_name,
                                      const string &_column_name,
                                      const string &_value );
    void update( const string &_column_name,
                 const string &_value,
                 const string &_which_column,
                 const string &_which_column_name );
    void insert( const vector<string> &_values );

    void delete_row( const string &_column_name,
                     const string &_value );
    /* $end DML */
private:
    string name;        // init("NULL")
    string data_file;   // init("NULL")

    string key;         // init("NULL"), default("columns[0]")
    string index;       // init("NULL")



    /*
     * Core data orgnization method
     *  - 2D table
     */

    /*
     * Core data title
     *  - Each operator with colums must update colums_count
     */
    vector<string> columns;
    size_t columns_count;

    /*
     * Core data
     *  - Each operator with rows must update rows_count
     */
    vector<Row> rows;
    size_t rows_count;

    /*
     *  Query result;
     */
    //vector<string> result_row;
    vector<vector<string> > result_rows;

    void open();
    void read_data();
    void save_data();
};

#endif // TABLE_H
