// (c) 2007 by Ighor Poteryakhin, ighor@ighor.ru
#include "generator.h"

template <class List>
List operator *(List first,List second)
{
    List r;
    for(typename List::iterator i=first.begin();i!=first.end();i++)
        for(typename List::iterator j=second.begin();j!=second.end();j++)
            r.push_back((*i)+(*j));
    return r;
}

template <class List>
List operator *(string first,List second)
{
    List one;
    one.push_back(first);
    return one*second;
}

template <class List>
List operator *(List first,string second)
{
    List one;
    one.push_back(second);
    return first*one;
}

template <class List>
List operator *=(List&first,List second)
{
    first=first*second;
    return first;
}

template <class List>
List operator +(List first,List second)
{
    List r;
    for(typename List::iterator i=first.begin();i!=first.end();i++)
        r.push_back(*i);
    for(typename List::iterator i=second.begin();i!=second.end();i++)
        r.push_back(*i);
    return r;
}

template <class List>
List operator +=(List&first,List second)
{
    first=first+second;
    return first;
}

template <class List>
List operator +=(List&first,string second)
{
    first.push_back(second);
    return first;
}

Result split(const string& s)
{
    Result r;
    int opened=0;
    unsigned remember=0,c;

    for(c=0;c<s.length();c++)
    {
	if(s[c]=='['||s[c]=='{')
	    opened++;
	if(s[c]==']'||s[c]=='}')
	    opened--;
	if(s[c]=='|'&&opened==0)
	{
	    r+=generate(s.substr(remember,c-remember));

	    remember=c+1;
	}
    }
    r+=generate(s.substr(remember,-1));

    return r;
}

Result mix(const string& s)
{
    Result r;
    Result members;
    int opened=0;
    unsigned remember=0,c;

    // разбираем внутренности и запихиваем всё разделённое '|' в members
    for(c=0;c<s.length();c++)
    {
	if(s[c]=='['||s[c]=='{')
	    opened++;
	if(s[c]==']'||s[c]=='}')
	    opened--;
	if(s[c]=='|'&&opened==0)
	{
	    members.push_back(s.substr(remember,c-remember));
	    remember=c+1;
	}
    }
    members.push_back(s.substr(remember,-1));

    // если не хватает элементов - принять их равным ""
    for(int i=members.size();i<3;i++)
	members.push_back("");

    Result::iterator i=members.begin();
    for(++i;i!=members.end();i++)
    {
	Result::iterator j=members.begin();
	for(++j;j!=members.end();j++)
	    if(i!=j)
		r+=generate(*i)*generate(*members.begin())*generate(*j);
    }    
    return r;
}


Result generate(const string& s)
{
    Result r,r1;
    unsigned remember;
    int opened;

    for(unsigned c=0;c<s.length();)
	switch(s[c])
	{
	    case '[':
		remember=c;
		opened=1;
		do
		{
		    c++;
		    if(s[c]=='[')
			opened++;
		    if(s[c]==']')
			opened--;
		    if(c==s.length()&&opened)
			throw("Incomplete number of '[]'s");
		}
		while(opened&&c<s.length());
		
		r=s.substr(0,remember)*split(s.substr(remember+1,(c++)-remember-1)); // непосредственно до скобок * содердимое квадратных скобок
		r*=generate(s.substr(c,-1)); // и остаток строки после скобок

		return r;

	    case '{':
		remember=c;
		opened=1;
		do
		{
		    c++;
		    if(s[c]=='{')
			opened++;
		    if(s[c]=='}')
			opened--;
		    if(c==s.length()&&opened)
			throw("Incomplete number of '{}'s");
		}
		while(opened&&c<s.length());
		
		r=s.substr(0,remember)*mix(s.substr(remember+1,(c++)-remember-1));
		r*=generate(s.substr(c,-1));
		
		return r;
	    default: c++;
	}
    r.push_back(s);
    return r;
}
