//#define TEST_CPP
#ifndef TEST_CPP

#include <iostream>
#include"_string.h"
#include"dbms.h"
#include"table.h"
#include <fstream>
using namespace std;

int main()
{
    vector <string> temp1 , temp3;
    vector <vector <string> > temp2;
    string filename1 , filename2 , filename3;
    cout.width(58);
    cout << "Welcome to the Sales Manager System" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "|You are allowed to:\n";
    cout << "|1.Insert data from file\n";
    cout << "|2.Insert data via console\n";
    cout << "|3.Query via console input\n";
    cout << "|4.Query via file input\n\n";
    cout << "|Please chose one function(0 to exit):";
    string a;
    while(cin >> a)
    {
        if (a[0]-'0' == 0)
            break;
        while (a[0]-'0'<1 || a[0]-'0'>4)
        {
            cout << "|Please enter the right choice again:";
            cin >> a;
        }
        if (a[0]-'0' == 1)
        {
            ifstream infile;
            DBMS dbms , dbms2;
            cout << "Please put the file along with this program and input filename." << endl
                    << "filename1(infile):";
            cin >> filename1;
            dbms.bind(filename1);
            cout << "filename2(outfile):";
            cin >> filename2;
            dbms2.bind(filename2);
            const char *_data_file = dbms.get_table_name().c_str();
            infile.open(_data_file);

            string _s;
            int i = 0;
            if(getline(infile , _s))
            {
                ;
            }
            while (getline(infile , _s))
            {
                temp1.push_back(_s);
                _String __s(_s);
                temp3 = __s.split();
                dbms2.insert(temp3);
                i++;
            }
            cout << i <<  " goods handled success!" << endl;
        }
        else if (a[0]-'0' == 2)
        {
            cout << "|Please type the file you want save(0 to exit):";
            while(cin >> filename1)
            {
                if (filename1[0] - '0' == 0)
                    break;
                ifstream infile;
                DBMS dbms;
                dbms.bind(filename1);
                const char *_data_file = dbms.get_table_name().c_str();
                infile.open(_data_file);
                string _ss , _s;
                getline(infile , _ss);
                int cnt1 = 0 , cnt2 = 0;
                for (size_t i = 0 ; i < _ss.size() ; i++)
                {
                    if (_ss[i] == ',')
                        cnt1++;
                }
                cout << "|Please type like blew(0 to exit, ',' to seperate each info)" << endl;
                cout << _ss << endl;
                while(cin>>_s)
                {
                    if (_s[0] == '0')
                        break;
                    cnt2 = 0;
                    for (size_t i = 0 ; i < _s.size() ; i++)
                    {
                        if (_s[i] == ',')
                                cnt2++;
                    }
                    if (cnt1 != cnt2)
                    {
                        cout << "Error.try again\n";
                        continue;
                    }
                    _String __s(_s);
                    temp3 = __s.split();
                    dbms.insert(temp3);
                    cout << "|Please type like blew(0 to exit)" << endl;
                    cout << _ss << endl;
                }
                 cout << "|Please type the file you want save(0 to exit):";
                 dbms.unbind();
            }
        }
        else if (a[0]-'0' == 3)
        {
            string s1 , s2 , s3 , aa;
            cout << "|Please choose the file:";
            cin >> filename1;
            DBMS dbms;
            dbms.bind(filename1);
            cout << "|You are allow two different types of query." << endl;
            cout << "|1.One key word,one value and return the item's all info" << endl;
            cout << "|2.One key word,one value and return the info you want" << endl;

            cout << "|Please chose one(0 to exit):";
            cin >> aa;
            if (aa[0]-'0' == 0)
                break;
            while (aa[0]-'0'<1 || aa[0]-'0'>2)
            {
                cout << "|Please enter the right choice again:";
                cin >> aa;
            }

            if (aa[0] - '0' == 1)
            {
                cin >> s1 >> s2;
                temp2 = dbms.select(s1 , s2);
                for (size_t i = 0 ; i < temp2.size() ; i++)
                {
                    size_t j = temp2[i].size();
                    for (size_t k = 0 ; k < j ; k++)
                        cout << temp2[i][k] << "\t";
                    cout << endl;
                }
            }
            else
            {
                cin >> s1 >> s2 >> s3;
                temp2 = dbms.select(s1 , s2 , s3);
                for (size_t i = 0 ; i < temp2.size() ; i++)
                {
                    size_t j = temp2[i].size();
                    for (size_t k = 0 ; k < j ; k++)
                        cout << temp2[i][k] << "\t";
                    cout << endl;
                }
            }
        }
        else
        {
            string s1 , s2 , s3 , aa;
            cout << "|Please enter the data file:";
            cin >> filename1;
            DBMS dbms , dbms2;
            dbms.bind(filename1);
            cout << "|Please enter the query file:";
            cin >> filename2;
            ifstream infile;
            ofstream outfile("result.txt");
            dbms2.bind(filename2);
            const char *_data_file = dbms2.get_table_name().c_str();
            infile.open(_data_file);
            string _s;
            int cntt = 0;
            while (getline(infile , _s))
            {
                cntt++;
                outfile << _s << endl;
                int cnt = 0;
                for (size_t i = 0 ; i < _s.size() ; i++)
                {
                    if (_s[i] == ',')
                        cnt++;
                }
                if (cnt == 1)
                {
                    _String __s(_s);
                    temp3 = __s.split();
                    temp2 = dbms.select(temp3[0] , temp3[1]);
                    for (size_t i = 0 ; i < temp2.size() ; i++)
                    {
                        size_t j = temp2[i].size();
                        for (size_t k = 0 ; k < j ; k++)
                            outfile << temp2[i][k] << "\t";
                        outfile << endl;
                    }
                }
                else
                {
                    _String __s(_s);
                    temp3 = __s.split();
                    temp2 = dbms.select(temp3[0] , temp3[1] , temp3[2]);
                    for (size_t i = 0 ; i < temp2.size() ; i++)
                    {
                        size_t j = temp2[i].size();
                        for (size_t k = 0 ; k < j ; k++)
                            outfile << temp2[i][k] << "\t";
                        outfile << endl;
                    }
                }

            }
            cout << cntt << " queries Success!" << endl;
        }
        cout << "|Please chose one function(0 to exit):";
    }



    cout.width(59);
    cout << "Thanks for using Sales Manager System" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    return 0;
}

#endif

