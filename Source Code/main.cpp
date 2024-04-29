#include <iostream>                   // Include the I/O stream library for input and output operations.
#include "FileParse.cpp"              // Include the external FileParse.cpp file for parsing utilities such as the shuntingYard function.

bool evalPostfix(const string& postfix) {  // Define a function that evaluates a postfix expression (assumed to be boolean).
    stack<bool> evalStack;                 // Declare a stack to hold boolean values during evaluation.

    for (char c : postfix) {               // Iterate over each character in the postfix string.
        if (c == 'T' || c == 'F') {        // Check if the character represents a boolean value (true or false).
            evalStack.push(c == 'T');      // Convert 'T' to true and 'F' to false, then push it onto the stack.
        } else if (isOperator(c)) {        // Check if the character is an operator.
            if (c == '!') {                // Check for the NOT operator.
                bool val = evalStack.top();   // Retrieve the top element of the stack (to be negated).
                evalStack.pop();           // Remove the top element from the stack.
                evalStack.push(!val);      // Push the negated value back onto the stack.
            } else {                       // Handle binary operators (AND, OR, NAND, XOR).
                bool val1 = evalStack.top();  // Retrieve the top element (right operand).
                evalStack.pop();           // Remove the top element.
                bool val2 = evalStack.top();  // Retrieve the next top element (left operand).
                evalStack.pop();           // Remove the top element.
                switch (c) {               // Switch based on the operator.
                    case '&': evalStack.push(val2 && val1); break;  // AND operation.
                    case '|': evalStack.push(val2 || val1); break;  // OR operation.
                    case '@': evalStack.push(!(val2 && val1)); break; // NAND operation (custom operator '@').
                    case '$': evalStack.push(val1 != val2); break;   // XOR operation (custom operator '$').
                }
            }
        }
    }

    return evalStack.top();                // Return the remaining item in the stack, which is the result of the expression.
}

int main() {                              // Main function of the program.
    while (true) {                        // Infinite loop to continuously process user input.
        string expression;                // Declare a string to store the user's input expression.
        cout << "\nEnter a boolean expression (use T for true and F for false): ";  // Prompt user for input.
        getline(cin, expression);         // Read a line of text from the standard input.

        string postfix = shuntingYard(expression);  // Convert the input expression to postfix notation using the shuntingYard function.
        bool result = evalPostfix(postfix);         // Evaluate the postfix expression.

        cout << "The result of the expression is: " << (result ? "T" : "F") << endl;  // Output the result as 'T' for true or 'F' for false.
    }

    return 0;                             // Return 0 to indicate successful execution.
}
