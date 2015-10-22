//
//  main.cpp
//  templates-with-iterators
//
//  Created by Kristie Nguyen on 10/8/15.

#include <iostream>
#include "collection.h"

int main()
{
    TemplateClass<int> test(69, 105);
    cout << test.biggerOne() << endl;
    
    TemplateClass2<int> test2(7);
    TemplateClass2<char> test3('q');
}
