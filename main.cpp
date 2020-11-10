#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "enigma.h"
#include "helper.h"
#include "errors.h"

using namespace std;

int main(int argc, char** argv) {

    Enigma enigma(argc, argv);
    enigma.check_config(argc, argv);

    if (enigma.get_code() != NO_ERROR) {
        return enigma.get_code();
        // switch(enigma.get_code()) {
        //     case 1:
        //         return INSUFFICIENT_NUMBER_OF_PARAMETERS;
        //     case 2:
        //         cerr << "Invalid input character" << endl;
        //         return INVALID_INPUT_CHARACTER;
        //     case 3:
        //         cerr << "Invalid index!" << endl;
        //         return INVALID_INDEX;
        //     case 4:
        //         return NON_NUMERIC_CHARACTER;
        //     case 5:
        //         return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        //     case 6:
        //         return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
        //     case 7:
        //         return INVALID_ROTOR_MAPPING;
        //     case 8:
        //         return NO_ROTOR_STARTING_POSITION;
        //     case 9:
        //         return INVALID_REFLECTOR_MAPPING;
        //     case 10:
        //         return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
        //     case 11:
        //         cerr << "Error opening cinfiguration file" << endl;
        //         return ERROR_OPENING_CONFIGURATION_FILE;
        //     default:
        //         break;
        // }
    } else if (enigma.get_code() == NO_ERROR) {
        enigma.implement_config(argc, argv);
    }

    string letters;
    int letter_int;
    cin >> ws >> letters;

    for (string::iterator letter = letters.begin(); letter < letters.end(); letter++) {
        if (*letter < 65 || *letter > 90) {
            cerr << *letter << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
            return INVALID_INPUT_CHARACTER;
        }
        letter_int = *letter - 65;
        letter_int = enigma.encrypt(letter_int);
        *letter = static_cast<char>(letter_int + 65);
        cout << *letter;
    }
    cout << flush;

    return NO_ERROR;
}
