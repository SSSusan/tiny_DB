/*
 * Test DBMS
 */

#include  "dbms.h"
#include <iostream>

using namespace std;

int main()
{
    DBMS dbms;

    cout << dbms.bind( "test_data" ) << endl;
    cout << dbms.get_table_name() << endl;

    vector<vector<string> > select_result( dbms.select( "newsid", "100648768"));

    for ( size_t i = 0; i < select_result.size(); ++i )
    {
        for (size_t j = 0; j < select_result[i].size(); ++j )
            cout << select_result[i][j] << "\t";
        cout  << endl;
    }

    dbms.alter_table_add_column( "time" );

    return 0;
}
