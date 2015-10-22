// expression-tester.cpp
// A modified ExpressionTester.cpp by Professor Hester

#include"expression-tester.h"
#include"my-stack.h"
#include<string>
#include <iostream>
using namespace my_stack;
using namespace std;

namespace expression_tester
{
    enum Token { TOKEN_WFF, TOKEN_UPPER, TOKEN_COMMA,
                TOKEN_LEFT_GROUP, TOKEN_RIGHT_GROUP, TOKEN_UNKNOWN };
    Token toToken( char c );
    void processChar( char token, MyStack<Token> &stacK, bool &OK );
    void collapse( MyStack<Token> &stack, bool &OK );
    Token top( MyStack<Token> &stack );
    
    bool isExpression( string expressionCandidate )
    {
        MyStack<Token> stack;
        bool OK = true;

        // loop backwards through each character e.g. "(a,G(HHb,d))"
        // will loop over one iteration per character: ) ) d , b H H ( G , a (
        for ( long int index = expressionCandidate.size() - 1 ; index >= 0  ; index-- )
        {
            processChar( expressionCandidate[index], stack, OK );
        }

        if ( !OK )
        {
            return false;
        }

        // combine tokens to create possible WFFs
        collapse( stack, OK );
        
        // make sure only a single value remains
        return OK && !stack.isEmpty() && TOKEN_WFF == stack.pop() && stack.isEmpty();
    }

    Token toToken( char c )
    {
        switch (c)
        {
            case ',': return TOKEN_COMMA;
            case '(': return TOKEN_LEFT_GROUP;
            case ')': return TOKEN_RIGHT_GROUP;
        }
        if ( c>='A' && c<='Z' )
        {
            return TOKEN_UPPER;
        }
        return ( c>='a' && c<='z' ) ? TOKEN_WFF : TOKEN_UNKNOWN;
    }

    // do some character checking
    void processChar( char item, MyStack<Token> &stack, bool &OK )
    {
        Token token = toToken(item);
        switch (token)
        {
            case TOKEN_WFF:
                if	( !stack.isEmpty() && stack.top() == TOKEN_UPPER )
                {
                    OK = false; break;
                }
                if (!stack.isEmpty() && stack.top() == TOKEN_COMMA)
                {
                    collapse( stack, OK ); break;
                }
                if (!stack.isEmpty() && stack.top() == TOKEN_WFF)
                {
                    OK = false; break;
                }
                stack << token; break;
            
            case TOKEN_UPPER:
                if	( stack.isEmpty() )
                {
                    OK = false; break;
                }
                if	( !stack.isEmpty() && stack.top() == TOKEN_WFF )
                {
                    collapse( stack, OK ); break;
                }
                stack << token; break;
            
            case TOKEN_RIGHT_GROUP:
                stack << token; break;
            
            case TOKEN_COMMA:
                if	( stack.isEmpty() || stack.top() == TOKEN_LEFT_GROUP
                    || stack.top() == TOKEN_RIGHT_GROUP )
                {
                    OK = false; break;
                }
                // check for parentheses when there's a comma and WFF e.g (a, or ,a)
                if ( stack.pop() == TOKEN_WFF )
                    {
                        if (stack.isEmpty())
                        {
                            OK = false; break;
                        }
                        stack << TOKEN_WFF;
                    }
                stack << token;
                break;
            
            case TOKEN_LEFT_GROUP:
                // convert ( WFF ) to WFF
                if ( !stack.isEmpty() && TOKEN_WFF == stack.pop() && !stack.isEmpty()
                    && TOKEN_RIGHT_GROUP == stack.pop() )
                {
                    stack << TOKEN_WFF;
                }
                else
                {
                    OK = false;
                }
                break;
            
            case TOKEN_UNKNOWN:
                OK = false;
                break;
        }
    }

    void collapse( MyStack<Token> &stack, bool &OK )
    {
        if (stack.top() == TOKEN_COMMA)
        {
            stack.pop(); // pop COMMA
        }

        // It should end with a value
        if ( stack.isEmpty() || stack.top() != TOKEN_WFF )
        {
            return;
        }
        
        // pop single WFF or
        // WFF followed by UPPER collapses into WFF
        stack.pop();
        
        if(!stack.isEmpty() && stack.top() == TOKEN_WFF)
        {
            stack.pop();
        }

        // sucessful collapse - to a single value
        stack << TOKEN_WFF;
    }
}