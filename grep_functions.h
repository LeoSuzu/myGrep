#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <getopt.h>
#include <set>

using namespace std;


void print_usage();
void strGrep(string& pattern, string& filename);
int occur(string& pattern, string& filename, bool reverse, bool ignore_case)
void fileGrep(string& pattern, string& filename, bool lineNum,
               bool occurrences, bool ignore_case, bool reverse_match);

// Normal grep function witch will test first is inputted argument file or string
void strGrep(string& pattern, string& filename){

    //If file cant be read search pattern from inputted string
    size_t pos = filename.find(pattern);
    if (pos != string::npos) {
        cout << quoted(pattern) << " found in: " << quoted(filename) << " at position " << pos << endl;
    }
    else{
        cout << quoted(pattern) << " NOT found in " << quoted(filename) << endl;
    }
}

// This is the main grep functiomn witch will access to file and search match
void fileGrep(string& pattern, string& filename, bool lineNum, bool occurrences, bool ignore_case, bool reverse_match) {

    if(pattern.length() < 2 || filename.length() < 2) {
        cout << "Enter pattern and file/text correctly: not just letter" << endl;
        return;
    }
    else{
        // Try to read file first
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << filename << endl;
            return;
        }

        string line;
        int line_num = 0;
        set<int> printed_lines; // set to keep track of printed lines

        //Read lines from file to string line
        while (getline(file, line)) {
            ++line_num;

            string line_copy = line;
            string pattern_copy = pattern;

            //If user choose option "i" program ignore cases
            if (ignore_case) {
                // Modifying both file lines and pattern to lower case
                transform(line.begin(), line.end(), line_copy.begin(), ::tolower);
                transform(pattern.begin(), pattern.end(), pattern_copy.begin(), ::tolower);
            }

            bool match_found = false;
            size_t pos = 0;
            int count = 0;

            // Searching pattern_copy in line_copy and
            while ((pos = line_copy.find(pattern_copy, pos)) != string::npos) {
                match_found = true;

                // position and count increases everytime found
                ++count;
                ++pos;
            }

            // If NOT reverse_match then found. If reverse_match then NOT found
            if ((!reverse_match && match_found) || (reverse_match && !match_found)) {
                if (printed_lines.count(line_num) == 0) { // check if line has already been printed
                    printed_lines.insert(line_num); // add line number to set of printed lines

                    // If option line "l" is true print line num first
                    if (lineNum) {
                        cout << line_num<< ": ";
                    }
                    // If reverse_match is true print all the lines where pattern can NOT be found
                    // If reverse_match is false then print lines pattern found
                    cout << line << endl;



                }
            }
        }

        // Option "o" is true it will print number of occurences patter match
        if (occurrences) {
            if (reverse_match){
                cout << "Occurrences of lines NOT containing "<< pattern <<  ": " << occur(pattern, filename, reverse_match, ignore_case) << endl;
            }
            else{
                cout << "Occurrences of lines containing "<< pattern <<  ": " << occur(pattern, filename, reverse_match, ignore_case) << endl;
            }

        }

        file.close();

    }

}


//Function to print occurrences. This is Int function witch will return number of match
int occur(string& pattern, string& filename, bool reverse, bool ignore_case) {
    // Open file. Not necessary to check because this will used inside other function
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (ignore_case) {
            // convert both the pattern and line to lowercase
            transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
            transform(line.begin(), line.end(), line.begin(), ::tolower);
        }
        if (reverse) {
            if (line.find(pattern) == string::npos) {
                ++count;
            }
        } else {
            size_t pos = 0;
            while ((pos = line.find(pattern, pos)) != string::npos) {
                ++count;
                ++pos;  // start searching again after the match
            }
        }
    }
    file.close();
    return count;
}
This modification adds an if statement to check if ignore_case is true. If it is, then both the pattern and the line are converted to lowercase using the transform function. This ensures that the search is not case sensitive.





void print_usage() {
    cout << "If enter less than three arguments does not execute anything.\n";
    cout << "If enter three arguments program execute normal grep.\n";
    cout << "Enter: ./myGrep [options] <pattern> <file_name>\n";
    cout << "Leave [option] empty for normal 'grep' - from string or file:\n";
    cout << "Thease are commands for further use:\n";
    cout << "   l     Print line numbers\n"
         << "   o     Print only the count of matching lines\n"
         << "   r     Reverse search, print non-matching lines\n"
         << "   i     Ignore case when searching\n";
}