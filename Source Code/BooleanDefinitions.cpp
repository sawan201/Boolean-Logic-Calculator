/*
 * BooleanDefinitions.cpp : Adds the functionality to define booleans.
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
 * Creation Date: May 2, 2024
 * Modification Date: May 2, 2024
 * 
 */

#include <iostream>  // Include the library for input and output streaming.
#include "BooleanDefinitions.h"   // Include the user-defined header file that defines true and false.

using namespace std;              // Use the standard namespace to avoid prefixing with std::.

char trueDef = 'T';          // Default definition for true.
char falseDef = 'F';         // Default definition for false.

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