#include "dbms.h"
#include <iostream> // using std::cout, std::endl
#include <string>   // using std::string
#include <vector>   // using std::vector
#include <iterator> // using std::iterator

using namespace std;

DBMS::DBMS()
    : dbs_count(0), dbms_data_file("dbms_data.txt")
{
    open_dbms_data_infile();
    s_dbms_data_infile >> dbs_count;

    size_t index;
    for ( index = 0; index < dbs_count; ++index )
    {
        string _s;
        getline( s_dbms_data_infile, _s );
        db_names.push_back( _s ) ;
    }
    // After each file operate, must close it
    s_dbms_data_infile.close();
}

DBMS::~DBMS()
{
    // Do nothing
}

const bool DBMS::create_database( const string &_data_name )
{
    vector<string>::iterator result;
    result = find( db_names.begin(), db_names.end(), _data_name );

    if ( result !=  db_names.end() )
    {
        cout << "The database has existed." << endl;
        return false;
    }

    db_names.push_back( _data_name );
    dbs_count = db_names.size();    // Update db_count

    save_dbms_data_file();

    return true;
}

const bool DBMS::drop_database(const string &_data_name )
{
    vector<string>::iterator result;
    result = find( db_names.begin(), db_names.end(), _data_name );

    if ( result ==  db_names.end() )
    {
        cout << "The database is not existed." << endl;
        return false;
    }

    db_names.erase( result );
    dbs_count = db_names.size();    // Update db_count

    save_dbms_data_file();

    return true;
}

const bool bind_database( const string &_data_name )
{
    // ==
}

const bool DBMS::open_dbms_data_infile()
{
    const char *dbms_data_file_ptr = dbms_data_file.c_str();

    s_dbms_data_infile.open( dbms_data_file_ptr );

    if ( s_dbms_data_infile.fail() )
        throw "dbms data file open fail when reading";

    return true;
}

const bool DBMS::open_dbms_data_outfile()
{
    const char *dbms_data_file_ptr = dbms_data_file.c_str();

    s_dbms_data_outfile.open( dbms_data_file_ptr );

    if ( s_dbms_data_outfile.fail() )
        throw "dbms data file open fail when saving";

    return true;
}

const bool DBMS::save_dbms_data_file()
{
    if ( !open_dbms_data_outfile() )
        return false;

    s_dbms_data_outfile << dbs_count << endl;
    vector<string>::iterator index;
    for ( index = db_names.begin(); index != db_names.end(); ++index )
        s_dbms_data_outfile << (*index) << endl;

    s_dbms_data_outfile.close();

    return true;
}
