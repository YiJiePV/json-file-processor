// Title: Lab 1 - FileProcessing.cpp
//
// Purpose: Read and process files that the user inputs
//
// Class: CSC 2430 Winter 2022
// Author: Karena Qian
// The following code is from my authorship with the exception of the
// code provided by the instructors of this course.


#include "Formatting.h"
#include "FileProcessing.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::getline;

// Operates in a loop so multiple files can be processed.
// On each iteration, reads name of input and output files from user and opens them
// Then calls ProcessFile to do the actual file processing
// - If user enters a blank line for the input file, loop ends
// - If either file cannot be opened, loop restarts
//
// @param:
//      none
// @returns:
//      nothing
void ProcessFiles() {
    //for storing user input of output and input files
    string inputFile;
    string outputFile;

    //for storing max, min, and average of ages
    //(max initialized to -1 since age does not exist below 0)
    //(min initialized to 1 billion since human age does/has not exceeded the value)
    int maxAge = -1;
    int minAge = 1000000000;
    double sumAge = 0;
    double numPeople = 0;

    //first input for input file
    cout << "Input File Name: ";
    getline(cin, inputFile);

    //while the user input is not an empty line
    while (!inputFile.empty()){
        ifstream ifSS(inputFile);

        //(Note for error-checking code segments:
        // printing the error using cerr and then asking for input using cout gives an unsolvable bug)

        //checks if file is in correct format, if not, restart current loop
        if(inputFile.find_last_of('.') != string::npos) {
            if (inputFile.substr(inputFile.find_last_of('.'), inputFile.length() - 1) != ".json") {
                cout << "ERROR: Incorrect file format, please provide a JSON file" << endl;

                //get input for input file again before restarting loop
                cout << "Input File Name: ";
                getline(cin, inputFile);
                continue;
            }
        }

        //if input file cannot be opened, restart current loop
        if(!ifSS.is_open()){
            cout << "ERROR: " << inputFile << " not found" << endl;

            //get input for input file again before restarting loop
            cout << "Input File Name: ";
            getline(cin, inputFile);
            continue;
        }
        //else if file is successfully opened
        else {
            //for output file loop
            bool isValid = false;

            //get output file input
            cout << "Output File Name: ";
            getline(cin, outputFile);
            ofstream ofSS(outputFile);

            //runs until output file name is valid and successfully opened
            while (!isValid) {
                //checks for correct format, stays in loop if in incorrect format
                if (outputFile.find_last_of('.') != string::npos) {
                    if (outputFile.substr(outputFile.find_last_of('.'), outputFile.length() - 1) != ".csv") {
                        cout << "ERROR: Incorrect file format, please provide a CSV file" << endl;

                        //get output file input before current loop restarts
                        cout << "Output File Name: ";
                        getline(cin, outputFile);
                        ofstream ofSS(outputFile);
                    }
                    else{
                        isValid = true;
                    }
                }

                //checks if output file cannot be opened, stays in loop if true
                if (!ofSS.is_open()) {
                    cout << "ERROR: " << outputFile << " not found" << endl;

                    //get output file input before current loop restarts
                    cout << "Output File Name: ";
                    getline(cin, outputFile);
                    ofstream ofSS(outputFile);
                }
                else{
                    isValid = true;
                }
            }
            //if output file is valid and successfully opened:
            //create CSV file from JSON file
            //and gather info about ages
            ofSS << CSVHeader() << endl;

            //get first line
            string line;
            getline(ifSS, line);
            //runs while the variable is not empty
            //(prevents an extra empty CSV line from being printed at the end of the output file)
            while (!line.empty()) {
                //converts and prints each JSON line in CSV format
                ofSS << FormatAsCSV(line) << endl;

                //gathers age info if age exists
                if (!GetAge(line).empty()) {
                    int age = stoi(GetAge(line));
                    if (age > maxAge) {
                        maxAge = age;
                    }
                    if (age < minAge) {
                        minAge = age;
                    }
                    sumAge += age;
                    numPeople++;
                }

                line = "";
                //get next line if not end of file and if the file didn't fail
                if(!ifSS.fail()) {
                    getline(ifSS, line);
                }
            }

            //close output file
            ofSS.close();
        }
        //close input file
        ifSS.close();

        //prints out age info
        cout << "Minimum age: " << minAge << endl;
        cout << "Maximum age: " << maxAge << endl;
        cout << "Average age: " << sumAge / numPeople << endl;

        //Resets variables for recording age info
        maxAge = -1;
        minAge = 1000000000;
        sumAge = 0;
        numPeople = 0;

        //get input for input file before loop begins again
        cout << "Input File Name: ";
        getline(cin, inputFile);
    }
}

