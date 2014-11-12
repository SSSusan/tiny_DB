#ifndef _STRING_H
#define _STRING_H

#include <string>   // using std::string
#include <vector>   // using std::vector

using namespace std;

class _String
{
public:
    _String();
    _String( const string & );
    const string::iterator & indexof( const char & ); // in str
    const vector<string> & split ();
private:
    string str;
    string::iterator ptr_c;
    vector<string> sub_strs;
};

#endif // _STRING_Hbb
