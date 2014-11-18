#ifndef DBMS_H
#define DBMS_H

#include "table.h"
#include <string>   // using std::string

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

private:
    bool is_bind;       // init(false)
    string table_name;  // init("NULL")

    Table table;
};

#endif // DBMS_H
