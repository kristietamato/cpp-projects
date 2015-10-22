//
//  collection.h
//  templates-with-iterators

#ifndef COLLECTION
#define COLLECTION

#include <iostream>
using namespace std;

template <class templateData>
class TemplateClass
{
    templateData first, second;
public:
    TemplateClass(templateData a, templateData b)
    {
        first = a;
        second = b;
    }
    
    templateData biggerOne();
};

template <class templateData>
templateData TemplateClass<templateData>::biggerOne()
{
    return ( first > second ? first:second);
}

template <class templateData2>
class TemplateClass2
{
public:
    TemplateClass2(templateData2 data)
    {
        cout << data << " is not a char" << endl;
    }
};

template<>
class TemplateClass2<char>
{
public:
    TemplateClass2(char x)
    {
        cout << x << " is a char" << endl;
    }
};

#endif
