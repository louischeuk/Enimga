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
    if (enigma.get_code() == NO_ERROR) {
        enigma.implement_config(argc, argv);
    } else {
        return enigma.get_code();
    }

    string letters;
    int letter_int;
    cin >> ws >> letters;

    for (string::iterator letter = letters.begin(); letter < letters.end(); letter++) {
        if (*letter < 65 || *letter > 90) {
            cerr << *letter;
            cerr << " is not a valid input character (input characters must be upper case letters A-Z)!";
            cerr << endl;
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
