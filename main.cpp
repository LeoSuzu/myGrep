// This is simple grep program made by Leo Suzuki
// This program needs grep_functions.h to work
// EXAMPLE FILE man_grep_plain_ASCII.txt

#include "grep_functions.h"
#include <iostream>
#include <algorithm>


using namespace std;

int main(int argc, char* argv[]) {

    // Variables
    string use, pattern, filename, usage;
    // Basic use options are all false state
    bool line_num = false;
    bool occurrences = false;
    bool ignore_case = false;
    bool reverse_match = false;

    if (argc == 1){

        // Tell the user that since only ./myGrep is only argc program make simple grep with file or text string
        cout << "Enter 'help' for usage leave empty for simple grep: ";
        getline(cin, usage);

        if(usage.empty()){
            // If program started with only one argc (./myGrep) it will ask two varables from user and make normal grep
            cout << "Give a string or file name from which to search for: ";
            getline(cin, filename);

            cout << "Give search pattern: ";
            getline(cin, pattern);

            ifstream file(filename);

            if(pattern.length() < 2 || filename.length() < 2){
                cout << "Enter pattern and file/text correctly: not just letter" << endl;
                return 1;
            }
            else{
                // If file can be open
                if (file.good()) {
                    string lines;
                    fileGrep(pattern, filename, line_num, occurrences, ignore_case, reverse_match);
                } else
                {
                    //Grep function for string
                    strGrep(pattern,filename);
                }
            }

        }
        else if (usage == "help"){
            print_usage();
        }
        else{
            return 1;
        }


    }

    else if (argc == 2){
        cout << "Too few arguments provided \n";
        print_usage();
    }

    // If provided three arguments execute grep() with 2 arguments
    else if (argc == 3)
    {
        string arg1 = argv[1];
        string arg2 = argv[2];
        fileGrep(arg1, arg2, line_num, occurrences, ignore_case, reverse_match);
    }

    // If provided three arguments execute fileGrep() with 3 arguments
    else if (argc == 4)
    {
        string arg2 = argv[2];
        string arg3 = argv[3];

        // Process option. Check first is there "-o" sign
        if (::strncmp(argv[1], "-o", 2)==0){

            // Erasing "-o" from string
            string input = argv[1];
            string option = "-o";
            input.erase(0, option.length());

            // Check what options are included and make boolean values to true if found option letters
            for (char c : input) {
                if (c == 'l'){
                    line_num = true;
                }
                if (c == 'o'){
                    occurrences = true;
                }
                if (c == 'i'){
                    ignore_case = true;
                }
                if (c == 'r'){
                    reverse_match = true;
                }
            }

            fileGrep(arg2, arg3, line_num, occurrences, ignore_case, reverse_match);

        }
        // If argv[2] is NOT start with "-o"
        else{
            cout << "Option ERROR\n";
            return 1;
        }


    }

    else
    {
        // If provided more than 4 arguments
        cout << "Too many arguments!!!\n";
        print_usage();
        return 1;
    }

    return 0;
}
