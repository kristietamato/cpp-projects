// Exampel 05 - stack used to test arithmetic expression.

// Note:
// I am going to have the tester return a string of WHEN operations are recognized
// so that it can be seen that order of operations is observed.
// I considered having it output these instead of adding to a string,
// but a tester function has no business doing console output.

#include<iostream>
#include<string>
#include"Tools.h"
#include"ExpressionTester.h"
using namespace std;
using namespace tools;
using namespace expression_tester;

int main(void)
{
	cout << "Expression Evaluator: valid chars are a-z, +, *, (, and )." << endl;
	cout << endl;

	while ( true )
	{
		string expressionCandidate = getLine("Enter a string to test (nothing to quit): ");
		string operations;
		if ( isExpression( expressionCandidate, operations ) )
		{
			cout << "That is a proper expression." << endl;
			cout << "The operations, in order of evaluation, are \""
				<< operations << "\"" << endl;
		}
		else
		{
			cout << "That is not a proper expression." << endl;
		}

		cout << endl;

		if ( expressionCandidate == "" && !getBool("Do you want to do another? ") ) break;
	}

	return 0;
}