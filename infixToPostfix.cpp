/*
 * Name: Noah Nininger
 * Date Submitted: 02/00/23
 * Lab Section: 001
 * Assignment Name: Lab 2 - Infix to Postfix Conversion
 */

#include <iostream>
#include <string>
#include <stack>

using namespace std;

// function prototypes
int operators(char c);
bool validation(string infix[], int length);
int infixToPostfix(string infix[], int length, string postfix[]);

//Main function to test infixToPostfix()
//Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//            to 2 3 4 * + 5 6 - 7 + 8 * +
/*int main()
{
    string infixExp[] = {"2", "+", "3", "*", "4", "+", "(",
                         "5", "-", "6", "+", "7", ")", "*",
                         "8"};
    string postfixExp[15];
    int postfixLength;

    cout << "Infix expression: ";
    for (int i=0; i<15; i++)
        { cout << infixExp[i] << " "; }
    cout << endl;
    cout << "Length: 15" << endl << endl;

    postfixLength = infixToPostfix(infixExp, 15, postfixExp);

    cout << "Postfix expression: ";
    for (int i=0; i<postfixLength; i++)
        { cout << postfixExp[i] << " "; }
    cout << endl;
    cout << "Length: " << postfixLength << endl;
    
    return 0;
}*/

// function definitions
int operators(char c)
{
    if (c == '*' || c == '/' || c == '%')
        { return 2; }
    else if (c == '+' || c == '-')
        { return 1; }
    else
        { return -1; }  
}

bool validation(string infix[], int length)
{
    stack<string> stack;
    string str;

    for (int i = 0; i < length; i++)
    {
        switch (infix[i][0])
        {
            case '(':
                stack.push(infix[i]);       // pushes element into the stack
                break;
            case ')':
                if (stack.empty())
                    { return 0; }
                str = stack.top();
                stack.pop();            // pops the element
                break;
        }
    }

    return (stack.empty());     // otherwise, return empty stack / false
}

//Converts an infix arithmetic expression into postfix
//The function takes 3 parameters
//First parameter: array of strings for infix expression
//    each string is either an integer number or operator symbol
//Second parameter: number of strings in infix expression
//Third parameter: array of strings for postfix expression
//    generated by function, same format as first parameter
//    assumes that postfix is at least the size of postfix
//Return value: int, number of strings in postfix expression
//    Returns 0 if an error is encountered when converting expression
//    An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
//Operator symbols:
// ( : left parenthesis, all operations between this and ")" take place first
// ) : right parenthesis, all op.s back to previous "(" take place first
// * : multiplication, higher precedence - takes place before "+" and "-"
// / : division, higher precedence - takes place before "+" and "-"
// % : remainder, higher precedence - takes place before "+" and "-"
// + : addition, lower precedence - takes place after "*" , "/" , "%"
// - : subtraction, lower precedence - takes place after "*" , "/" , "%"
//The function is not specified to work with any other operator symbols
//Any string in infix may be assumed to be an integer operand if none
// of the above symbols
int infixToPostfix(string infix[], int length, string postfix[])
{
    if (!validation(infix, length))
        { return 0; }
    stack<string> stack;
    string str;

    stack.push("P");

    int count {0};
    for (int i = 0; i < length; i++)
    {
        if(isdigit(infix[i][0]))        // adds character to postfix if it is a number
            { postfix[count++] = infix[i]; }
        else if (infix[i][0] == '(')    // puts character to the stack if it is a (
            { stack.push(infix[i]); }
        else if (infix[i][0] == ')')
        {
            while (stack.top()[0] != 'P' && stack.top()[0] != '(')
            {
                str = stack.top();
                stack.pop();
                postfix[count++] = str;
            }
            
            if (stack.top()[0] == '(')
                { stack.pop(); }
        }
        else
        {
            while (stack.top()[0] != 'P' && operators(infix[i][0]) <= operators(stack.top()[0]))
            {
                str = stack.top();
                stack.pop();
                postfix[count++] = str;
            }
            stack.push(infix[i]);
        }
    }

    while (stack.top()[0] != 'P')       // pop reamaining elements from the stack
    {
        str = stack.top();
        stack.pop();
        postfix[count++] = str;
    }

    return count;
}
