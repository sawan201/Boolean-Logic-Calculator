/*
 * Main.cpp : Main driver which handles user input.
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

#include <iostream>               // Include the I/O stream library for input and output operations.
#include "FileParse.cpp"          // Include the external FileParse.cpp file for parsing utilities such as the shuntingYard function.

// Define a function to evaluate a postfix expression consisting of boolean values.
bool evalPostfix(const string& postfix) {
    stack<bool> evalStack;       // Define a stack to hold boolean values during evaluation.

    
    for (char c : postfix) {        // Iterate over each character in the postfix string.
        if (c == 'T' || c == 'F') { // If the character represents a boolean value (true or false),
            evalStack.push(c == 'T'); // Convert 'T' to true and 'F' to false, then push it onto the stack.
        } else if (isOperator(c)) {  // If the character is an operator,
            if (c == '!') {          // Check for the NOT operator.
                if (evalStack.empty()) throw runtime_error("Missing operand for NOT operation"); // Throw an error if the stack is empty.
                bool val = evalStack.top();   // Retrieve the top element of the stack.
                evalStack.pop();              // Remove the top element from the stack.
                evalStack.push(!val);         // Push the negated value back onto the stack.
            } else {                 // For binary operators (AND, OR, NAND, XOR),
                if (evalStack.size() < 2) throw runtime_error("Missing operand for binary operator"); // Ensure there are two operands.
                bool val1 = evalStack.top(); // Retrieve the top element (right operand).
                evalStack.pop();     // Remove the top element.
                bool val2 = evalStack.top(); // Retrieve the next top element (left operand).
                evalStack.pop();     // Remove the top element.
                switch (c) {         // Switch based on the operator type.
                    case '&': evalStack.push(val2 && val1); break;  // AND operation.
                    case '|': evalStack.push(val2 || val1); break;  // OR operation.
                    case '@': evalStack.push(!(val2 && val1)); break; // NAND operation.
                    case '$': evalStack.push(val2 != val1); break;   // XOR operation.
                }
            }
        }
    }

    return evalStack.top();        // Return the remaining item in the stack, which is the result of the expression.
}

int main() {                      // Main function of the program.
    while (true) {                // Infinite loop to continuously process user input.
        string expression;        // Declare a string to store the user's input expression.
        cout << "\nEnter a boolean expression (use T for true and F for false): ";  // Prompt user for input.
        getline(cin, expression); // Read a line of text from the standard input.

        try {
            string postfix = shuntingYard(expression); // Convert the input expression to postfix notation using the shuntingYard function.
            bool result = evalPostfix(postfix);        // Evaluate the postfix expression.
            cout << "The result of the expression is: " << (result ? "True" : "False") << endl; // Output the result as 'True' or 'False'.
        } catch (exception& e) {   // Catch any exceptions.
            cout << "Error: " << e.what() << endl;  // Display the error message.
        }
    }

    return 0;                     // Return 0 to indicate successful execution.
}
