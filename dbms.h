#ifndef DBMS_H
#define DBMS_H

#include "db.h"
#include <fstream>  // using std::ifstream, std::ofstream
#include <string>   // using std::string
#include <vector>   // using std::vector
//#include <list>     // using std::list

using namespace std;

class DBMS
{
    friend ostream & operator<<( ostream &os, const vector<string> &_vec );
public:
    DBMS();
    ~DBMS();

    const bool create_database( const string &_database_name );
    const bool drop_database( const string &_database_name );

    const bool bind_database( const string &_database_name );

    void show_db_all();

private:
    ifstream s_dbms_data_infile;
    ofstream s_dbms_data_outfile;
    const string dbms_data_file;    // init("dbms_data.txt")

    unsigned int dbs_count;         // init(0)
    vector<string> db_names;

    /*
     *  It should bind only one db.
     */
    DB the_db;

    const bool open_dbms_data_infile();
    const bool open_dbms_data_outfile();
    const bool save_dbms_data_file();
};

#endif // DBMS_H
