#include <iostream>               // Include the I/O stream library for input and output operations.
#include <stack>                  // Include the stack container from the Standard Template Library.
#include <string>                 // Include the string library for using string data type.
#include "TokenType.h"            // Include the TokenType header for token type definitions.

using namespace std;              // Use the standard namespace to avoid typing "std::" before standard functions and types.

struct Token {                    // Define a struct to represent a token with two properties.
  TokenType type;                 // Store the type of the token (e.g., operator, operand, parenthesis).
  char value;                     // Store the value of the token (e.g., character representing the token).
};

bool isOperator(char c) {         // Function to check if a character is an operator.
  return c == '&' || c == '|' || c == '!' || c == '@' || c == '$';  // Return true if the character is one of the specified operators.
}

bool isParen(char c) {            // Function to check if a character is a parenthesis.
  return c == '(' || c == ')';    // Return true if the character is an opening or closing parenthesis.
}

int getPrecedence(char c) {       // Function to determine the precedence level of operators.
  switch (c) {                    // Use a switch statement to assign precedence based on operator type.
    case '!': return 3;           // NOT operator has the highest precedence.
    case '$': return 2;           // XOR operator has the second highest precedence.
    case '&': return 2;           // AND operator shares the second highest precedence.
    case '|': return 1;           // OR operator has the lowest precedence.
    case '@': return 1;
    default:  return -1;          // Return -1 for any undefined operators.
  }
}

bool isLeftAssociative(char c) {  // Determine if an operator is left associative.
  return c != '!';                // All operators are left associative except the NOT operator, which is right associative.
}

string shuntingYard(const string& expression) {  // Implement the shunting yard algorithm to convert infix to postfix notation.
  stack<Token> operators;                        // Stack to hold operators and parentheses.
  string output;                                 // String to store the postfix expression.

  for (char c : expression) {                    // Iterate over each character in the input expression.
    if (isspace(c)) continue;                    // Skip whitespace characters.
    if (isalpha(c)) {                            // Check if the character is an operand (assumed to be alphabetic).
      output += c;                               // Add operand directly to the output string.
      continue;
    }

    Token token;                                 // Create a token object.
    token.value = c;                             // Set the token's value to the current character.

    if (isOperator(c)) {                         // Check if the character is an operator.
      token.type = TOKEN_OPERATOR;               // Set token type to operator.
      while (!operators.empty() &&
             operators.top().type == TOKEN_OPERATOR &&
             ((isLeftAssociative(c) && getPrecedence(c) <= getPrecedence(operators.top().value)) ||
              (!isLeftAssociative(c) && getPrecedence(c) < getPrecedence(operators.top().value)))) {
        output += operators.top().value;         // Pop operators from the stack to the output if they have higher or equal precedence.
        operators.pop();
      }
      operators.push(token);                     // Push the current operator onto the stack.
    } else if (isParen(c)) {                     // Check if the character is a parenthesis.
      token.type = TOKEN_PAREN;                  // Set token type to parenthesis.
      if (c == '(') {                            // If it is an opening parenthesis,
        operators.push(token);                   // push it onto the stack.
      } else {                                   // If it is a closing parenthesis,
        while (!operators.empty() && operators.top().value != '(') {  // Pop all operators until an opening parenthesis is encountered.
          output += operators.top().value;
          operators.pop();
        }
        if (!operators.empty()) {                // Pop the opening parenthesis from the stack, but don't add to output.
          operators.pop();
        }
      }
    }
  }

  while (!operators.empty()) {                  // At the end of the expression, pop all remaining operators in the stack.
    output += operators.top().value;
    operators.pop();
  }

  return output;                                // Return the postfix expression.
}
