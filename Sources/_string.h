/*
 * Class _String supposed to add some functions to string
 */

#ifndef _STRING_H
#define _STRING_H

#include <string>   // using std::string
#include <vector>   // using std::vector

using namespace std;

class _String
{
public:
    _String();
    _String( const string &_s );

    const vector<string> & split ();
private:
    string str;
    string::iterator ptr_c;
    vector<string> sub_strs;
};

#endif // _STRING_Hbb
