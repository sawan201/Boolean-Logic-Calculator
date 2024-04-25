#include <iostream>               // Include the I/O stream library for input and output operations.
#include <stack>                  // Include the stack container from the Standard Template Library.
#include <string>                 // Include the string library for using string data type.

using namespace std;              // Use the standard namespace to avoid typing "std::" before standard functions and types.

enum TokenType {                  // Define an enumeration to categorize different types of tokens.
  TOKEN_VAR,                      // Enumerator for boolean variable.
  TOKEN_OPERATOR,                 // Enumerator for operators.
  TOKEN_PAREN                     // Enumerator for parentheses.
};

struct Token {                    // Define a struct to represent a token with two properties.
  TokenType type;                 // Store the type of the token.
  char value;                     // Store the value of the token.
};

bool isOperator(char c) {         // Function to check if a character is an operator.
  return c == '&' || c == '|' || c == '!' || c == '@' || c == '$';  // Return true if the character is one of these operators.
}

bool isParen(char c) {            // Function to check if a character is a parenthesis.
  return c == '(' || c == ')';    // Return true if the character is '(' or ')'.
}

int getPrecedence(char c) {       // Function to get the precedence level of operators.
  switch (c) {                    // Use a switch statement to determine the precedence.
    case '!': return 4;           // Highest precedence for NOT operator.
    case '$': return 3;           // Second highest for XOR operator.
    case '&': return 2;           // Third for AND operator.
    case '|': return 1;           // Fourth for OR operator.
    case '@': return 0;           // Lowest for custom NAND operator.
    default:  return -1;          // Return -1 for undefined operators.
  }
}

string shuntingYard(const string& expression) {  // Function to convert infix expression to postfix using the Shunting Yard algorithm.
  stack<Token> operators;                        // Stack to hold operators and parentheses.
  string output;                                 // String to build the postfix expression.

  for (char c : expression) {                    // Loop over each character in the input expression.
    if(isspace(c)){                              // If the character is a space,
        continue;                                // skip it and continue to the next iteration.
    }
    if (isalpha(c)) {                            // If the character is an alphabetical character (variable),
      output += c;                               // append it to the output string.
      continue;                                  // and continue to the next character.
    }

    Token token;                                 // Create a new token instance.
    token.value = c;                             // Set the token's value to the current character.

    if (isOperator(c)) {                         // If the character is an operator,
      token.type = TOKEN_OPERATOR;               // set the token type to operator.
      while (!operators.empty() &&               // While there are tokens on the stack,
             operators.top().type == TOKEN_OPERATOR &&  // and the top of the stack is an operator
             getPrecedence(c) <= getPrecedence(operators.top().value)) {  // with higher or equal precedence,
        output += operators.top().value;         // append it to output.
        operators.pop();                         // Remove it from the stack.
      }
      operators.push(token);                     // Push the current operator token on the stack.
    } else if (isParen(c)) {                     // If the character is a parenthesis,
      token.type = TOKEN_PAREN;                  // set the token type to parenthesis.
      if (c == '(') {                            // If it is an opening parenthesis,
        operators.push(token);                   // push it onto the stack.
      } else {                                   // If it is a closing parenthesis,
        while (!operators.empty() && operators.top().value != '(') {  // Pop until an opening parenthesis is found.
          output += operators.top().value;       // Append each operator to the output.
          operators.pop();                       // Pop the operator from the stack.
        }
        if (!operators.empty()) {                // If an opening parenthesis is found,
          operators.pop();                       // pop it from the stack (discard it).
        }
      }
    }
  }

  while (!operators.empty()) {                  // At the end, pop all the operators left in the stack,
    output += operators.top().value;            // and append them to the output.
    operators.pop();                            // Pop each one.
  }

  return output;                                // Return the postfix expression.
}
