/*
 * main.cpp : Main driver which handles user input.
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
 * Modification Date: May 2, 2024
 * 
 */

#include <iostream>               // Include the library for input and output streaming.
#include <stdexcept>              // Include the library for standard exceptions.
#include <stack>                  // Include the library for using stack data structures.
#include <string>                 // Include the library for string manipulation.
#include <limits>                 // Include the library for error handling
#include "FileParse.cpp"          // Include custom functions from FileParse.cpp for parsing.
#include "TruthTable.cpp"         // Include custom functions from TruthTable.cpp for truth table printing.
#include "BooleanDefinitions.h"   // Include the user-defined header file that defines true and false.

using namespace std;              // Use the standard namespace to avoid prefixing with std::.

char trueDef = 'T';          // Default definition for true.
char falseDef = 'F';         // Default definition for false.

// Function to evaluate a postfix expression consisting of boolean values.
bool evalPostfix(const string& postfix) {
    stack<bool> evalStack;        // Stack to hold boolean values during evaluation.

    // Iterate over each character in the postfix expression.
    for (char c : postfix) {
        // Check if character is a boolean literal 'T' or 'F'.
        if (c == trueDef || c == falseDef) {
            evalStack.push(c == trueDef);  // Push true for 'T', false for 'F'.
        } else if (isOperator(c)) {   // Check if character is an operator.
            if (c == '!') {           // Specifically check for the NOT operator.
                if (evalStack.empty()) throw runtime_error("Missing operand for NOT operation");
                bool val = evalStack.top(); // Retrieve the top value from stack.
                evalStack.pop();            // Remove the top value.
                evalStack.push(!val);       // Push the negated value back onto the stack.
            } else { // Handling for binary operators (AND, OR, NAND, XOR).
                if (evalStack.size() < 2) throw runtime_error("Missing operand for binary operator");
                bool val1 = evalStack.top(); // Right operand.
                evalStack.pop();             // Remove the right operand.
                bool val2 = evalStack.top(); // Left operand.
                evalStack.pop();             // Remove the left operand.
                // Perform operation based on the operator and push the result.
                switch (c) {
                    case '&': evalStack.push(val2 && val1); break;  // AND operation.
                    case '|': evalStack.push(val2 || val1); break;  // OR operation.
                    case '@': evalStack.push(!(val2 && val1)); break; // NAND operation.
                    case '$': evalStack.push(val2 != val1); break;   // XOR operation.
                }
            }
        }
    }
    return evalStack.top();        // Return the result of the evaluated expression.
}

// Function to prompt the user to define true and false
void defineTrueFalse() {
    char trueInput, falseInput;

    // Loop until the user enters valid single characters for true and false representations
    do {
        cout << "Please enter what you want 'true' to represent (single character only): ";
        cin >> trueInput;
        
        // Check if input failed due to non-integer input
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input left in the input buffer
            cout << "Invalid input. Please enter a single character." << endl;
        } else if (cin.peek() != '\n') { // Check if input failed due to whitespaces.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input left in the input buffer
            cout << "Invalid input. Please enter a single character with no whitespaces." << endl;
        } else {
            if (trueInput == falseDef) { // Check if user assigned true and false to the same definition.
                cout << "Error: 'true' representation cannot be the same as 'false' representation. Please choose a different character." << endl;
            } else { // Assign definition to true and break out of loop.
                trueDef = trueInput;
                break;
            }
        }
    } while (true);

    // Reset input stream and clear buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Loop until the user enters valid single characters for true and false representations
    do {
        cout << "Please enter what you want 'false' to represent (single character only): ";
        cin >> falseInput;

        // Check if input failed due to non-integer input
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input left in the input buffer
            cout << "Invalid input. Please enter a single character." << endl;
        } else if (cin.peek() != '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input left in the input buffer
            cout << "Invalid input. Please enter only a single character." << endl;
        } else {
            if (falseInput == trueDef) { // Check if user assigned true and false to the same definition.
                cout << "Error: 'false' representation cannot be the same as 'true' representation. Please choose a different character." << endl;
            } else { // Assign definition to false and break out of loop.
                falseDef = falseInput;
                break; 
            }
        }
    } while (true);

    cout << "True representation set to: " << trueDef << endl;
    cout << "False representation set to: " << falseDef << endl;
}


// Main function of the program, handling user interactions.
int main() {
    bool running = true;           // Control variable to keep the program running.

    // Main loop to present options and handle user input continuously.
    while (running) {
        // Display options to the user.
        cout << "\nWelcome to the Boolean Logic Calculator! Please Choose an option:\n"
             << "1) Calculator\n"
             << "2) Define True and False\n"
             << "3) Truth Table\n"
             << "4) Exit\n"
             << endl;

        int choice;                // Variable to store user's choice.
        cout << "Enter your choice: ";
        cin >> choice;             // Read user's choice.

        // Check if input failed due to non-integer input
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input left in the input buffer
            cout << "Invalid Input. Please enter a number." << endl;
            continue; // Skip the rest of the loop and show the menu again
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean up any leftover characters in the input buffer

        // Switch to handle different choices.
        switch (choice) {
            case 1: {              // Case for Calculator.
                bool continueCalculator = true;  // Control variable for calculator loop.
                while (continueCalculator) {
                    string expression;  // String to store the user's boolean expression.
                    cout << "\nEnter a boolean expression using '" << trueDef << "' for true and '" << falseDef << "' for false (or type 'exit' to return to main menu): ";
                    getline(cin, expression); // Read the complete line as an expression.
                    if (expression == "exit") {
                        continueCalculator = false;  // Exit calculator loop if user types 'exit'.
                    } else {
                        try {
                            string postfix = shuntingYard(expression); // Convert expression to postfix notation.
                            bool result = evalPostfix(postfix);        // Evaluate the postfix expression.
                            cout << "Result: " << (result ? "True" : "False") << endl;
                        } catch (exception& e) { // Catch and report any exceptions.
                            cout << "Error: " << e.what() << endl;
                        }
                    }
                }
                break;
            }
            case 2:                // Case for defining true and false.
                defineTrueFalse();
                break;
            case 3:                // Case for printing Truth Table.
                cout << "\n" << endl;
                printTruthTable();
                break;
            case 4:                // Case to exit the program.
                running = false;   // Set running to false, stopping the loop.
                break;
            default:               // Default case for invalid input.
                cout << "Invalid Input. Please Try Again." << endl;
                break;
        }
    }
    return 0;                     // Return 0 to signal successful completion.
}
