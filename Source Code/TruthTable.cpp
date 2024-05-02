/*
 * TruthTable.cpp : Adds the functionality to print truth tables to the main program.
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

#include <iostream>  // Include the library for input and output streaming.
#include <iomanip>   // Include the library for manipulating input and output formatting.
#include "BooleanDefinitions.h"   // Include the user-defined header file that defines true and false.

// Define a function implementing the AND logic gate.
bool AND(bool a, bool b) {
    return a && b;  // Returns true if both a and b are true, false otherwise.
}

// Define a function implementing the OR logic gate.
bool OR(bool a, bool b) {
    return a || b;  // Returns true if either a or b is true, true otherwise.
}

// Define a function implementing the NAND logic gate.
bool NAND(bool a, bool b) {
    return !(a && b);  // Returns true if NOT both a and b are true, false otherwise.
}

// Define a function implementing the XOR logic gate.
bool XOR(bool a, bool b) {
    return a != b;  // Returns true if a is not equal to b, false if they are equal.
}

// Define a function implementing the NOT logic gate.
bool NOT(bool a) {
    return !a;  // Returns true if a is false, false if a is true.
}

// Function to print the truth table for two variables.
void printTruthTable() {
    // Print headers for the truth table columns.
    std::cout << trueDef << " " << falseDef << "|\tAND\tOR\tNAND\tXOR |\tNOT " << trueDef << "\t\tNOT " << falseDef << "\n";
    // Print a line to separate headers from the data.
    std::cout << "--------------------------------------------------------------"<< std::endl;
    // Nested loops to generate all combinations of A and B.
    for (int i = 0; i < 2; ++i) {      // Outer loop for the first boolean variable (A).
        for (int j = 0; j < 2; ++j) {  // Inner loop for the second boolean variable (B).
            // Print the values of A and B followed by the results of the logic gates.
            std::cout << i << " " << j << "|\t "
                      << AND(i, j) << "\t " << OR(i, j) << "\t  " << NAND(i, j) << "\t " << XOR(i, j) << "  |\t  "
                      << NOT(i) << "\t\t  " << NOT(j) << "\n";  // Output the results of AND, OR, NAND, XOR, and NOT operations.
        }
    }
}
