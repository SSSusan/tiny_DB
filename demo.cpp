#define DEMO_CPP
#ifndef DEMO_CPP
/*
 * Test DBMS
 */

#include  "dbms.h"
#include <iostream>

using namespace std;

int main()
{
    DBMS dbms;

    //dbms.create_table( "Sales ");
    //cout << dbms.get_bind_state() << endl;
    //dbms.alter_table_add_column( "Name");

    dbms.create_table( "test" );
    cout << dbms.get_table_name() << endl;

    return 0;
}
#endif
