#include "../engine/generator.h"
#include <iostream>

int main(int argc, char* argv[])
{
    string s;
    getline(cin,s);
    try
    {
        Result r=generate(s);
	for(Result::iterator i=r.begin();i!=r.end();i++)
	    cout<<*i<<endl;
	return 0;
    }
    catch (const char* err)
    {
	cout<<err<<endl;
    }
}
