// my-stack.h

#include<vector>

#ifndef MY_STACK_LOCK
#define MY_STACK_LOCK

namespace my_stack
{
    template<class templateData>
    class MyStack
    {
    public:
        typedef templateData value_type;
        
        // modifiers
        MyStack<templateData> &push( const value_type &value )
        { values.push_back(value); return *this; }
        value_type pop(void)
        { value_type value = values[values.size()-1]; values.pop_back() ; return value; }
        
        // alternate interface, just for fun
        MyStack<templateData> &operator<<( const value_type &value )
        { push(value); return *this; }
        MyStack<templateData> &operator>>( value_type &value )
        { value = pop(); return *this; }
        
        // status
        bool isEmpty(void) const
        { return values.size() == 0; }
        typename std::vector<templateData>::size_type size(void) const
        { return values.size(); }
        value_type top(void) const
        { return values[values.size()-1]; }
        
    private:
        std::vector<value_type> values;
    };
    
}

#endif