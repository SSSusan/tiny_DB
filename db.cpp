#include "db.h"
#include "table.h"
#include <iostream> // using std::cout, std::endl;
#include <vector>   // using std::vector
#include <string>   // using std::string

using namespace std;

DB::DB()
    :is_bind(false), db_data_file("Data/"),
     tables_count(0), db_name("")
{
    // Do nothing
}

DB::~DB()
{
    // Do nothing
}

void DB::bind( const string &_database_name )
{
    db_name = _database_name;

    // Just activate the DB
    is_bind = true;
    db_data_file += _database_name;

    open_db_data_infile();
    s_db_data_infile >> tables_count;

    // Read each table's property is here
    size_t index;
    for ( index = 0; index < tables_count; ++index )
    {
        Table theTable;
        theTable.parent_dbname = _database_name;
        s_db_data_infile >> theTable.table_name
                         >> theTable.colums_count
                         >> theTable.index_count;
        tables_name.push_back( theTable.table_name );

        size_t index1, index2;
        for ( index1 = 0; index1 < theTable.colums_count; ++index1 )
        {
            string _colum_name;
            getline( s_db_data_infile, _colum_name );
            theTable.colums.push_back( _colum_name );
        }
        for ( index2 = 0; index2  < theTable.index_count; ++index2 )
        {
            string _index_name;
            getline( s_db_data_infile, _index_name );
            theTable.indexs.push_back( _index_name );
        }

        tables.insert({ theTable.table_name, theTable });
    }

    // After each file operate, must close it
    s_db_data_infile.close();
}

const bool DB::open_db_data_infile()
{
    const char *db_data_file_ptr = db_data_file.c_str();

    s_db_data_infile.open( db_data_file_ptr );

    if ( s_db_data_infile.fail() )
        throw "db data file open fail when reading";

    return true;
}

const bool DB::open_db_data_outfile()
{
    const char *db_data_file_ptr = db_data_file.c_str();

    s_db_data_outfile.open( db_data_file_ptr );

    if ( s_db_data_outfile.fail() )
        throw "db data file open fail when saving";

    return true;
}

const bool DB::save_db_data_file()
{
    if ( !open_db_data_outfile() )
        return false;

    s_db_data_outfile << tables_count << endl;
    vector<string>::iterator index;
    for ( index = tables_name.begin(); index != tables_name.end(); ++index )
    {
        string _tables_name = (*index);
        s_db_data_outfile << tables[_tables_name].table_name
                          << tables[_tables_name].colums_count
                          << tables[_tables_name].index_count
                          << endl;

        size_t index1, index2;
        for ( index1 = 0; index1 < tables[_tables_name].colums_count; ++index1)
            s_db_data_outfile << tables[_tables_name].colums[index1] << endl;

        for ( index2 = 0; index2 < tables[_tables_name].index_count; ++index2)
            s_db_data_outfile << tables[_tables_name].indexs[index2] << endl;
    }

    s_db_data_outfile.close();

    return true;
}
