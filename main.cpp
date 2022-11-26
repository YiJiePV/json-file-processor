// Title: Lab 1 - main.cpp
//
// Purpose: Convert files with lines in JSON format to a CSV file
//
// Class: CSC 2430 Winter 2022
// Author: Max Benson


#include <iostream>
#include <cassert>
using std::cout;
using std::endl;
using std::string;

#include "FileProcessing.h"
#include "Formatting.h"

// Forward declaration
bool TestFormatting();

int main() {
    // Validate the string re-formatting function
    if (!TestFormatting()) {
        return 1;
    }
    cout << "VALIDATION SUCCEEDS" << endl;

    // Process one set of files
    ProcessFiles();
    return 0;
}

// Unit Test function for validating the formatting functions
//
// Parameters:
//      none
// Returns:
//      true if validation passes, false otherwise
bool TestFormatting() {
    string inputJSON[] = {
            R"({ "FirstName":"Hulk" })",
            R"({ "FirstName":"Peter", "LastName":"Parker" })",
            R"({ "LastName":"Stark", "FirstName":"Tony" })",
            R"({ "FirstName":"Flash", "LastName":"Thompson", "Age":16"  })"
    };
    string outputCSV[] = {
            "Hulk,,,,",
            "Peter,Parker,,,",
            "Tony,Stark,,,",
            "Flash,Thompson,16,,"
    };
    string outputNumber[] = {
            "",
            "",
            "",
            "16"
    };

    // Test ParseNumberValue
    assert( sizeof(inputJSON)/sizeof(inputJSON[0]) == sizeof(outputNumber)/sizeof(outputNumber[0]) );
    for (int i = 0; i < sizeof(inputJSON)/sizeof(inputJSON[0]); i ++ ) {
        if (GetAge(inputJSON[i]) != outputNumber[i]) {
            cout << "VALIDATION FAILURE: GetAge( '" << inputJSON[i] << "' ) returns"  << GetAge(inputJSON[i]) << endl;
            return false;
        }
    }

    // Test FormatAsCSV
    assert( sizeof(inputJSON)/sizeof(inputJSON[0]) == sizeof(outputCSV)/sizeof(outputCSV[0]) );
    for (int i = 0; i < sizeof(inputJSON)/sizeof(inputJSON[0]); i ++ ) {
        if (FormatAsCSV(inputJSON[i]) != outputCSV[i]) {
            cout << "VALIDATION FAILURE: FormatAsCSV( '" << inputJSON[i] << "' ) returns " << FormatAsCSV(inputJSON[i]) << endl;
            return false;
        }
    }

    return true;
}