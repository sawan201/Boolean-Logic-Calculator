#include <iostream>                   // Include the I/O stream library for input and output operations.
#include "FileParse.cpp"                 // Include the external parse.cpp file, which might contain the shuntingYard function and other parsing utilities.

bool evalPostfix(const string& postfix) {  // Define a function that evaluates a postfix expression (assumed to be boolean).
    stack<bool> evalStack;                // Declare a stack to hold boolean values during evaluation.

    for (char c : postfix) {              // Iterate over each character in the postfix string.
        if ((c == 'T' || 't' || '1') || c == ('F' || 'f' || '0')) {       // Check if the character represents a boolean value.
            evalStack.push(c == 'T');     // Convert 'T' to true and 'F' to false and push to the stack.
        } else if (isOperator(c)) {       // Check if the character is an operator.
            if (c == '!') {               // Check for the NOT operator.
                bool val = evalStack.top();  // Retrieve the top element of the stack.
                evalStack.pop();          // Remove the top element.
                evalStack.push(!val);     // Push the negated value back to the stack.
            } else {                      // For binary operators:
                bool val1 = evalStack.top(); // Retrieve the top element (right operand).
                evalStack.pop();          // Remove the top element.
                bool val2 = evalStack.top(); // Retrieve the next top element (left operand).
                evalStack.pop();          // Remove the top element.
                switch (c) {              // Switch based on the operator.
                    case '&': evalStack.push(val2 && val1); break;  // AND operation.
                    case '|': evalStack.push(val2 || val1); break;  // OR operation.
                    case '@': evalStack.push(~(val2 && val1)); break; // NAND operation (custom operator '@').
                    case '$': evalStack.push(val2 ^ val1); break;   // XOR operation (custom operator '$').
                }
            }
        }
    }

    return evalStack.top();               // Return the remaining item in the stack, which is the result of the expression.
}

int main() {                             // Main function of the program.
    while(true){                         // Infinite loop to keep the program running.
    string expression;                   // Declare a string to store the user's input expression.
    cout << "Enter a boolean expression (use T for true and F for false): ";  // Prompt user for input.
    getline(cin, expression);            // Read a line of text from the standard input.

    string postfix = shuntingYard(expression); // Convert the input expression to postfix notation using shuntingYard function.
    bool result = evalPostfix(postfix);  // Evaluate the postfix expression.

    cout << "The result of the expression is: " << (result ? "T" : "F") << endl;  // Output the result.
    }

    return 0;                            // Return 0 to indicate successful execution.
}
