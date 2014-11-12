#include <iostream> // using std::cout
#include <string>   // using std::string
#include <vector>   // using std::vector
#include "_string.h"
using namespace std;

int main()
{
    _String s("pepsi,drink,2");

    vector<string> sub_s;
    sub_s = s.split();

    vector<string>::iterator i;
    for ( i = sub_s.begin(); i != sub_s.end(); ++i) {
        cout << (*i) << "  ";
    }
    cout << endl;

    string::iterator tmp;
    tmp = s.indexof(',');
    cout << (*tmp) << endl;



    return 0;
}
