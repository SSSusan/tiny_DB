/*
 * Test DBMS
 */

#include  "dbms.h"
#include <iostream>

using namespace std;

int main()
{
    DBMS dbms;

    dbms.create_table( "Sales ");
    cout << dbms.get_bind_state() << endl;

    dbms.alter_table_add_column( "Name");


    return 0;
}
