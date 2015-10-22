// ExpressionTester.cpp

#include"ExpressionTester.h"
#include"MyStack.h"
#include<string>
using namespace my_stack;
using namespace std;

namespace expression_tester
{
	enum Token { TOKEN_VALUE, TOKEN_MULTIPLICATION, TOKEN_ADDITION,
				TOKEN_LEFT_GROUP, TOKEN_RIGHT_GROUP, TOKEN_UNKNOWN };
	Token toToken( char c );

	void processChar( char token, MyStack<Token> &stack, string &operations, bool &OK );
	void collapse( MyStack<Token> &stack, string &operations, bool &OK );
	Token top( MyStack<Token> &stack );
	bool isOperator( Token token );

	bool isExpression( string expressionCandidate, string &operations )
	{
		MyStack<Token> stack;
		bool OK = true;
		for ( string::size_type index = 0 ; index < expressionCandidate.size() ; ++index ) //loop through each character in the string like an array
            //e.g. "(a+b)*c+b+c" will loop over one iteration per character: '(', 'a', '+', 'b', ')', etc.
			processChar( expressionCandidate[index], stack, operations, OK );
		if ( !OK ) return false;

		// clean up any remaining addition operation
		collapse( stack, operations, OK );

		// make sure only a single value remains
		return OK && !stack.isEmpty() && TOKEN_VALUE == stack.pop() && stack.isEmpty();
	}

	bool isOperator( Token token )
	{
		return token == TOKEN_ADDITION || token == TOKEN_MULTIPLICATION;
	}

	Token toToken( char c )
	{
		switch (c)
		{
		case '+': return TOKEN_ADDITION;
		case '*': return TOKEN_MULTIPLICATION;
		case '(': return TOKEN_LEFT_GROUP;
		case ')': return TOKEN_RIGHT_GROUP;
		}
		return ( c>='a' && c<='z' ) ? TOKEN_VALUE : TOKEN_UNKNOWN;
	}

	// remove one complete arithmetic operation, if it is there
	void collapse( MyStack<Token> &stack, string &operations, bool &OK )
	{
		// It should end with a value
		if ( stack.isEmpty() || stack.top() != TOKEN_VALUE ) return;
		stack.pop();

		// if that was the ONLY thing on the stack or it is preceeded by (, it is OK
		if ( stack.isEmpty() || TOKEN_LEFT_GROUP == stack.top() )
		{
			stack << TOKEN_VALUE;
			return;
		}

		// The value should be preceeded with an operator
		Token operation;
		if ( stack.isEmpty() || !isOperator(operation = stack.pop()) )	{ OK = false; return; }
		operations += ((operation==TOKEN_ADDITION) ? "+" : "*");

		// The operator should be preceeded with a value
		if ( stack.isEmpty() || stack.pop() != TOKEN_VALUE )			{ OK = false; return; }

		// sucessful collapse - to a single value
		stack << TOKEN_VALUE;
	}

	void processChar( char item, MyStack<Token> &stack, string &operations, bool &OK )
	{
		// Note:
		// I could check top of stack before adding tokens
		// and catch many errors "now" instead of later.
		// I'd rather be lazy and let collapse() catch the errors.

		Token token = toToken(item);
		switch (token)
		{
		case TOKEN_VALUE:
			if		( stack.isEmpty() ) { stack << token; return; }
			switch ( stack.top() )
			{
			case TOKEN_LEFT_GROUP:		stack << token; break;
			case TOKEN_ADDITION:		stack << token; break; // don't collapse yet
			case TOKEN_MULTIPLICATION:	collapse( stack << token, operations, OK ); break;
			default:					OK = false; break;
			}
			break;

		case TOKEN_ADDITION:
			collapse( stack, operations, OK);
			stack << TOKEN_ADDITION;
			break;

		case TOKEN_MULTIPLICATION:
		case TOKEN_LEFT_GROUP:
			stack << token;
			break;

		case TOKEN_RIGHT_GROUP:
			// clear any pending addidion
			collapse( stack, operations, OK );
			if ( !OK ) return;

			// convert ( value ) to value
			if ( !stack.isEmpty() && TOKEN_VALUE == stack.pop()
					&& !stack.isEmpty() && TOKEN_LEFT_GROUP == stack.pop() )
				stack << TOKEN_VALUE;
			else
				OK = false;
			break;

		case TOKEN_UNKNOWN:
			OK = false;
			break;
		}
	}
}