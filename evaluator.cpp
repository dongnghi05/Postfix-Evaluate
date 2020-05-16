/*
 * Name: Nghi Vo (Ivy)
 * Lab 4: Evaluating Postfix Operations - CSC 2431
 * Description: The function takes in a parameter postfix that contains a string with a postfix arithmetic expression.
 * The expression will have only integers (each can have several digits) and it can have the following operators: +, -, *, / and ^.
 * The other parameter is used to check whether the postfix operation was correctly formatted, therefore if Evaluate finds an error, it must set the error variable to true and return -1.
 * If everything goes well the function should set error to false and return the result of the expression.
 */

#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include <math.h>

using namespace std;


// Function to perform an operation and return output. 
float PerformOperation(string str, float number1, float number2)
{
    if(str[0] == '+') return number1 + number2;
    else if(str[0] == '-') return number2 - number1;
    else if(str[0] == '*') return number1 * number2;
    else if(str[0] == '/') return number2 / number1;
    else if(str[0] == '^') return pow(number2, number1);
}

// Function to verify whether a character is operator
bool IsOperator(string str) {
    // Operator is only one char so string has only 1 element 0.
    if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == '^') {
        return true;
    }
    else {
        return false;
    }
}

// Function to verify whether a character is digit.
bool IsFloat(string str) {
    // The number might have more than 2 digits so check both digit
    istringstream digit(str);
    float number;
    digit >> number;
    return digit.eof() && !digit.fail();
}

// Function to evaluate Postfix
double Evaluate(const string& postfix, bool& error)
{
    // Declaring a Stack from STL in C++.
    stack<float> Eval;
    istringstream iss(postfix);
    string str;
    while (!iss.eof()) {
        // Get string from the postfix string but eliminate space
        iss >> str;
        // If string take in is not digit or operator
        if (IsFloat(str) == false && IsOperator(str) == false) {
            error = true;
            return -1;
        }
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (IsOperator(str)) {
            // Pop two numbers.
            float number1;
            float number2;
            // If stack is empty
            if (!Eval.empty()) {
                number1 = Eval.top();
                Eval.pop();
                // If don't have second number
                if (!Eval.empty()) {
                    number2 = Eval.top();
                    Eval.pop();
                    float result = PerformOperation(str, number1, number2);
                    Eval.push(result); // Push result back to stack
                }
                else {
                    error = true;
                    return -1;
                }
            }
        } else if (IsFloat(str)) {
            // Change string to float
            Eval.push(stof(str));
        }
    }
    // If everything is in correct format. The last element will be the output.
    error = false;
    return Eval.top();
}
