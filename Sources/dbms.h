#ifndef DBMS_H
#define DBMS_H

#include "table.h"
#include <string>   // using std::string
#include <vector>   // using std::vector

using namespace std;

class DBMS
{
public:
    DBMS();
    DBMS( const string &_table_name );
    ~DBMS();

    bool bind( const char *_table_name );
    bool bind( const string &_table_name );
    void unbind();

    const string & get_table_name() const { return table_name; }
    bool get_bind_state() const { return is_bind; }

    /* $begin DDL */
    /*
     *  CREATE TABLE table_name=value
     */
    bool create_table( const string &_table_name );
    /*
     *  AlTER TABLE table_name
     *  ADD column_name [datatype]
     */
    void alter_table_add_column( const string &_column_name );

    /* $end DDL */

    /*  $begin DML */
    /*
     *  SELECT row FROM table_name
     *  WHERE _column_name=_valave_data();ue
     */
    vector<vector<string> > & select( const string &_column_name,
                                      const string &_value);

    /*
     *  SELECT __column_name FROM table_name
     *  WHERE _column_name=_value
     */
    vector<vector<string> > & select ( const string &__column_name,
                                       const string &_column_name,
                                       const string &_value );

    /*
     *  SELECT _columns_name FROM table_name
     *  WHERE _column_name=_value
     */
    //vector<vector<string> > & select( const vector<string> &_columns_name,
    //                                  const string &_column_name,
    //                                  const string &_value);

    /*
     *  UPDATE table_name SET _column_name=_value
     *  WHERE _which_column_name=_which_column_value
     */
    void update( const string &_column_name,
                 const string &_value,
                 const string &_which_column_name,
                 const string &_which_column_value );
    /*
     *  INSERT INTO table_name
     *  VALUES(val1, val2, val3, ...)
     */
    void insert( const vector<string> &_values );
    /*
     *  INSERT INTO table_name
     *  COLUMNS(col1, col2, ...) VALUES(val1, val2, ...)
     */
    void insert( const vector<string> &_columns,
                 const vector<string> &_values );

    /*
     *  DELETE FROM table_name WHERE _column_name=_value
     */
    void delete_row( const string &_column_name,
                     const string &_value );
    /* $end DML */
private:
    bool is_bind;       // init(false)
    string table_name;  // init("NULL")

    Table table;
};

#endif // DBMS_H
