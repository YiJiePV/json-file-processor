// Title: Lab 1 - Formatting.cpp
//
// Purpose: Convert a JSON-formatted line to a CSV-formatted line
//
// Class: CSC 2430 Winter 2022
// Author: Karena Qian
// The following code is from my authorship with the exception of the
// code provided by the instructors of this course.


#include "Formatting.h"
#include <string>
#include <sstream>

using std::stringstream;

// Returns CSV header as a string
//
// @param:
//      None
// @returns:
//      CSV header
string CSVHeader() {
    return "FirstName,LastName,Age,Height,Nationality";
}

// Converts one JSON formatted line to CSV, returning the CSV
// representation as a string
//
// @param:
//      json - JSON formatted line
// @returns:
//      CSV formatted line
string FormatAsCSV(const string& json) {
    string firstname = parseJson(json, "FirstName");
    string lastname = parseJson(json, "LastName");
    string age = parseJson(json, "Age");
    string height = parseJson(json, "Height");
    string nationality = parseJson(json, "Nationality");

    stringstream ss;
    ss << firstname << "," << lastname << "," << age << "," << height << "," << nationality;
    return ss.str();
}

// Return the age value stored in a JSON
// formatted line.  The return value is a string
// If age doesn't appear, returns empty string
//
// @param:
//      json - JSON formatted line
// @returns:
//      age as string, or empty if age doesn't appear
string GetAge(const string& json) {
    return parseJson(json, "Age");
}

// Parses through one JSON formatted line and returns the requested information
// as a string
// If not found, returns an empty string
// (Helper method for FormatAsCSV and GetAge)
//
// @param:
//      json - JSON formatted line
//      word - desired info
// @returns:
//      info as a string or empty if info does not appear
string parseJson(const string& json, const string& word) {
    string newStr = "";
    //If word is not found in json
    if (json.find(word) == string::npos) {
        //return a space
        return newStr;
    }
    else {
        //trims out desired info (gives json up to the desired info plus everything after it)
        newStr = json.substr(json.find(word), json.length());
        newStr = newStr.substr(newStr.find(':'), newStr.length());
        //finishes trimming out extra string based on type and position of info
        if (newStr.find(',') == string::npos) {
            if (word != "Age") {
                newStr = newStr.substr(2, newStr.find(' ') - 3);
            }
            else {
                newStr = newStr.substr(1, newStr.find('\"') - 1);
            }
        }
        else {
            if (word == "Age" || word == "Height") {
                if (word == "Age") {
                    newStr = newStr.substr(2, newStr.find(',') - 2);
                }
                else {
                    newStr = newStr.substr(1, newStr.find(',') - 1);
                }
            }
            else {
                newStr = newStr.substr(2, newStr.find(',') - 3);
            }
        }
        return newStr;
    }
}