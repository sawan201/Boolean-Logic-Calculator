/*
 * ShuntingYard.cpp : Implementation of the Shunting Yard algorithm to convert infix expressions to postfix notation.
 *
 * 2024 ©Macrosoft
 *
 * Authors:
 *   - Ahmad Awan
 *   - Mario Simental
 *   - Sulitan Subade
 *   - Karsten Wolter
 *   - Jack Pigott
 *
 * Creation Date: April 24, 2024
 * Modification Date: May 1, 2024
 * 
 */

#include <iostream>               // Include the library for standard input/output stream operations.
#include <stack>                  // Include the library that provides the stack container class template.
#include <string>                 // Include the library for using the string type.
#include <cctype>                 // Include the library for character classification and conversion functions.
#include <unordered_set>          // Include the library that provides the unordered set container.
#include <exception>              // Include the library for exception handling utilities.
#include "TokenType.h"            // Include the user-defined header file that defines the TokenType enumeration.

using namespace std;              // Declare usage of the standard namespace to avoid prefixing std:: on standard library types and functions.

struct Token {                    // Define a structure to represent a token.
    TokenType type;               // Member to store the type of the token, as defined in TokenType.
    char value;                   // Member to store the character value of the token.
};

bool isOperator(char c) {         // Function to check if a character is one of the predefined operators.
    return c == '&' || c == '|' || c == '!' || c == '@' || c == '$';  // Returns true if the character matches one of the logical operators.
}

bool isParen(char c) {            // Function to check if a character is a parenthesis.
    return c == '(' || c == ')';  // Returns true if the character is an opening or closing parenthesis.
}

int getPrecedence(char c) {       // Function to determine the precedence of an operator.
    switch (c) {                  // Switch statement on the character.
        case '!': return 3;       // NOT operator has the highest precedence.
        case '$': return 2;       // XOR operator has second highest precedence.
        case '&': return 2;       // AND operator has second highest precedence.
        case '|': return 1;       // OR operator has lowest precedence.
        case '@': return 1;       // NAND operator has lowest precedence.
        default: throw invalid_argument("Unrecognized operator symbol: " + string(1, c));  // Throw an exception if the operator is not recognized. 
    }
}

bool isLeftAssociative(char c) {  // Function to determine if an operator is left associative.
    return c != '!';              // Returns true if the operator is not the NOT operator.
}

string shuntingYard(const string& expression) {  // Function implementing the shunting yard algorithm to convert infix to postfix notation.
    if (expression.empty()) throw runtime_error("No operands or operators present");  // Throw an error if the input expression is empty.

    stack<Token> operators;       // Stack to hold operators and parentheses during conversion.
    string output;                // String to store the postfix expression.
    bool expectOperand = true;    // Boolean flag to track whether the next character should be an operand.

    for (char c : expression) {   // Iterate over each character in the expression.
        if (isspace(c)) continue; // Skip whitespace characters.
        if (isalpha(c) && (c == 'T' || c == 'F')) {  // Check if the character is a boolean value 'T' or 'F'.
            if (!expectOperand) {
                throw runtime_error("Operand follows another operand or does not follow an operator");  // Error if two operands are found consecutively. 
            }
            output += c;          // Append the operand to the output string.
            expectOperand = false;// Reset the expectation to allow an operator next.
            continue;
        }

        Token token;              // Create a new token object.
        token.value = c;          // Set the token's character value.

        if (isOperator(c)) {      // Check if the character is an operator.
            if (expectOperand && c != '!') {  // Error handling for missing operand before a binary operator. 
                throw runtime_error("Missing operand before operator: " + string(1, c)); // Generic error for other operators.
            } else if (!expectOperand && c == '!') { // Handle NOT operator exception for unary usage.
                throw runtime_error("Consecutive operators detected without operand in between."); // Error if two operators are found consecutively. 
            }

            token.type = TOKEN_OPERATOR;  // Set the token's type to operator.
            while (!operators.empty() &&  // While there are operators on the stack,
                   operators.top().type == TOKEN_OPERATOR &&  // the top of the stack is an operator,
                   ((isLeftAssociative(c) && getPrecedence(c) <= getPrecedence(operators.top().value)) ||  // current operator is left associative and has lower or equal precedence than the operator at the top of the stack,
                    (!isLeftAssociative(c) and getPrecedence(c) < getPrecedence(operators.top().value)))) {  // or it is right associative and has lower precedence.
                output += operators.top().value;  // Pop the operator from the stack to the output string.
                operators.pop();                  // Remove the operator from the stack.
            }
            operators.push(token);               // Push the current operator onto the stack.
            expectOperand = true;                // Set the expectation to find an operand next.
        } else if (isParen(c)) {                // Check if the character is a parenthesis.
            token.type = TOKEN_PAREN;           // Set the token's type to parenthesis.
            if (c == '(') {                     // If it is an opening parenthesis,
                operators.push(token);          // push it onto the stack.
                expectOperand = true;           // Expect an operand or another parenthesis after. 
            } else {                            // If it is a closing parenthesis,
                while (!operators.empty() && operators.top().value != '(') {  // Pop operators until an opening parenthesis is found.
                    output += operators.top().value;
                    operators.pop();
                }
                if (operators.empty()) throw runtime_error("Mismatched parentheses");  // Error if no matching opening parenthesis is found. 
                operators.pop();                // Pop the opening parenthesis from the stack.
                expectOperand = false;          // Next character can be an operator.
            }
        } else {
            throw invalid_argument("Invalid character or operator: " + string(1, c));  // Error if the character is neither an operator nor a parenthesis.
        }
    }

    while (!operators.empty()) {                // After processing all characters,
        if (operators.top().type == TOKEN_PAREN) throw runtime_error("Mismatched parentheses");  // Check for any remaining unmatched parentheses. 
        output += operators.top().value;        // Add remaining operators to the output.
        operators.pop();                        // Remove the operator from the stack.
    }

    if (expectOperand) throw runtime_error("Missing operand after operator");  // Error if the last operator did not have an operand. 

    return output;                              // Return the postfix expression.
}
