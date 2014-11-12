    #ifndef DB_H
#define DB_H

#include "table.h"
#include <string>   // using std::string
#include <vector>   // using std::vector
#include <fstream>  // using std::ifstream, std::ofstream
#include <map>      // using std::map

using namespace std;

class DB
{
public:
    DB();
    ~DB();
    void bind( const string & );
    const bool drop_table( const string & );
    const bool creat_table( const string & ,
                            const map<string, string> & );

private:
    bool is_bind;                   // init(false)
    string db_name;

    string db_data_file;            // init("")
    ifstream s_db_data_infile;
    ofstream s_db_data_outfile;

    unsigned int tables_count;      // init(0)
    vector<string> tables_name;
    map<string, Table> tables;

    const bool open_db_data_infile();
    const bool open_db_data_outfile();
    const bool save_db_data_file();
};

#endif // DB_H
