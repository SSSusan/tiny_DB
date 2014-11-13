#include "dbms.h"
#include <iostream> // using std::cout
#include <string>   // using std::string
#include <vector>   // using std::vector

using namespace std;

int main()
{
    DBMS dbms;

    dbms.drop_database( "s" );
    dbms.drop_database( "db1" );

    return 0;
}
