#include "dbms.h"
#include <iostream> // using std::cout, std::endl
#include <string>   // using std::string
#include <vector>   // using std::vector
#include <iterator> // using std::iterator
#include <algorithm>// using std::find
//#include <list>     // using std::list

using namespace std;

DBMS::DBMS()
    : dbs_count(0), dbms_data_file("dbms_data.txt")
{
    try {
        open_dbms_data_infile();
    } catch (const char *e) {
        cout << e << endl;
    }

    s_dbms_data_infile >> dbs_count;
    string _t;
    getline(s_dbms_data_infile, _t );

    size_t index;
    for ( index = 0; index < dbs_count; ++index )
    {   
        string _s;
        getline( s_dbms_data_infile, _s );
        db_names.push_back( _s );
    }
    // Debug
    show_db_all();

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

    show_db_all();
    db_names.erase( result );
    dbs_count = db_names.size();    // Update db_count
    show_db_all();

    save_dbms_data_file();

    return true;
}

const bool DBMS::bind_database( const string &_database_name )
{
    the_db.bind( _database_name );
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

void DBMS::show_db_all()
{
    vector<string>::iterator i;
    for ( i = db_names.begin(); i != db_names.end(); ++i )
        cout << ":" << (*i) << "\t";
    cout << endl;
}

/*
 * This is a bug here
 * - overload fail
 */
ostream & operator<<( ostream &os, const vector<string> &_vec )
{
     vector<string>::const_iterator index;
     for ( index = _vec.begin() ; index != _vec.end(); ++index )
         os << (*index) << "\t";

     return os;
}

