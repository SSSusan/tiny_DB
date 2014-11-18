#include "_string.h"
#include <string>   // using std::string
#include <vector>   // using std::vector

using namespace std;

_String::_String()
{
}

_String::_String( const string &_s )
{
    str = _s;
}

const string::iterator & _String::indexof( const char &_c )
{
    string::iterator index;

    for ( index = str.begin(); index != str.end(); ++index )
        if ( (*index) == _c )
            break;
    ptr_c = index;

    return ptr_c;
}

const vector<string> & _String::split ()
{
    string::iterator index;

    string tmp_s;
    for ( index = str.begin(); index != str.end(); ++index ) {
        char tmp_c = (*index);
        if ( tmp_c == ',' ) {
            sub_strs.push_back( tmp_s );
            tmp_s.clear();
        }
        else
            tmp_s.push_back( tmp_c );
    }
    if ( index  == str.end() ) {
        sub_strs.push_back ( tmp_s );
        tmp_s.clear();
    }

    return sub_strs;
}
