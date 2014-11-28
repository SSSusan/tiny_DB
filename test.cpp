#define TEST_CPP
#ifndef TEST_CPP

#include <iostream>
#include"_string.h"
#include"dbms.h"
#include"table.h"
using namespace std;

int main()
{

    try
    {
        DBMS dbms1("figure1.txt");
        DBMS dbms2;
        dbms2.bind("figure2.txt");
        string s1,s2,s3;
        s1=dbms1.get_table_name();
        cout<<s1<<endl;
        DBMS dbms3;
        dbms3.create_table("figure3.txt");
        s3=dbms3.get_table_name();
        cout<<s3<<endl;
        dbms3.alter_table_add_column("Name");
        dbms3.alter_table_add_column("Type");
        dbms1.select("Amount","100");
        dbms1.select("Price","Name","a");
        dbms1.select("Type","Amount","200");
        dbms2.select("Color","red");
        dbms2.select("Amount","Color","green");
        dbms2.select("Price","Type","tt1");
        dbms1.alter_table_add_column("discount");
        dbms2.alter_table_add_column("discount");
        dbms1.update("discount","50%","discount","NULL");
        dbms1.update("Type","tt","Type","t1");
        vector<string> vv;
        vv.push_back("f");
        vv.push_back("t6");
        vv.push_back("300");
        vv.push_back("50");
        vv.push_back("90%");
        dbms1.insert(vv);
        vector<string> co;
        co.push_back("Type");
        co.push_back("Name");
        vector<string> va;
        va.push_back("t5");
        va.push_back("e");
        dbms1.insert(co,va);
        dbms2.insert(co,va);
        dbms1.delete_row("Type","t2");
        dbms2.unbind();
        s2=dbms2.get_table_name();
        cout<<s2<<endl;

     }
    catch(const char* e)
    {
        cout<<"Exception:"<<e<<endl;
    }

    return 0;
}

#endif
