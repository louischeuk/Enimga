#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "enigma.h"
// #include "reflector.h"
// #include "rotor.h"
// #include "plugboard.h"
#include "helper.h"
#include "errors.h"

using namespace std;

int main(int argc, char** argv) {

    // // plugboard
    // Plugboard plugboard("plugboards/I.pb");
    // plugboard.check_config("plugboards/I.pb");
    // if (plugboard.code == 0)
    //     plugboard.implement_config("plugboards/I.pb");
    // cout << "Plugboard code: " << plugboard.code << endl << endl;

    // rotor
    // Rotor rotor("rotors/II.rot");
    // rotor.check_config("rotors/II.rot");
    // if (rotor.code == 0)
    //     rotor.implement_config("rotors/II.rot");
    // cout << "Rotor code: " << rotor.code << endl;


    // int test5 = rotor.map_r_to_l(6);
    // cout << "test5:" << test5 << endl;
    // test5 = rotor.map_l_to_r(test5);
    // cout << "test5:" << test5 << endl;


    // reflector
    // Reflector reflector("reflectors/II.rf");
    // reflector.check_config("reflectors/II.rf");
    // if (reflector.code == 0)
    //     reflector.implement_config("reflectors/II.rf");
    // cout << "Reflector code: " << reflector.code << endl;



    Enigma enigma(argc, argv);
    enigma.check_config(argc, argv);

    if (enigma.code != NO_ERROR) {
        switch(enigma.code) {
            case 1:
                return INSUFFICIENT_NUMBER_OF_PARAMETERS;
            case 2:
                cerr << "Invalid input character" << endl;
                return INVALID_INPUT_CHARACTER;
            case 3:
                cerr << "Invalid index!" << endl;
                return INVALID_INDEX;
            case 4:
                return NON_NUMERIC_CHARACTER;
            case 5:
                return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
            case 6:
                cerr << "Incorrect number of plugboard parameters!" << endl;
                return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
            case 7:
                return INVALID_ROTOR_MAPPING;
            case 8:
                return NO_ROTOR_STARTING_POSITION;
            case 9:
                cerr << "Invalid reflector mapping!" << endl;
                return INVALID_REFLECTOR_MAPPING;
            case 10:
                cerr << "Incorrect number of reflector parameters!" << endl;
                return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
            case 11:
                cerr << "Error opening cinfiguration file" << endl;
                return ERROR_OPENING_CONFIGURATION_FILE;
            default:
                break;
        }
    } else if (enigma.code == NO_ERROR) {
        enigma.implement_config(argc, argv);
//        cout << "enigma can be used." << endl;
    }


    /* start inputting letters */
//    cout << "Input any uppercase letter (A-Z) for encryption: ";
    string letters;
    int letter_int;
    cin >> ws >> letters;
//    cout << '\n' << "Encrypted ciphertext is: ";

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
