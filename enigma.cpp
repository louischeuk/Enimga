#include "enigma.h"
using namespace std;

Enigma::Enigma(int argc, char** argv) {

	code = NO_ERROR;
	plugboard = nullptr;
	rotor = nullptr;
	reflector = nullptr;
	number_of_rotor = 0;

	// for (int i=0 ; i < argc; i++) {
//		cout << "Config file " << i << " is: " << argv[i] << endl;
	// }
}

void Enigma::check_config(int argc, char **argv) {
	if (argc == 1) {
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
		code = INSUFFICIENT_NUMBER_OF_PARAMETERS;
	} else {
		plugboard = new Plugboard(argv[1]);
		plugboard->check_config(argv[1]);
		code = plugboard->get_code();
		if (code == NO_ERROR) {
//			cout << "plugboad config ok" << endl;

			if (argc == 2) {
				cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
				code = INSUFFICIENT_NUMBER_OF_PARAMETERS;
			} else {
				reflector = new Reflector(argv[2]);
				reflector->check_config(argv[2]);
				code = reflector->get_code();
				if (code == NO_ERROR) {
//					cout << "Reflector config ok " << endl;

					if (argc == 3) {
						cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
						code = INSUFFICIENT_NUMBER_OF_PARAMETERS;
					} else if (argc >= 4) {
//						cout << "argc is >= 4" << endl;
						rotor = new Rotor *[argc - 4]; // an array of rotors
						number_of_rotor = argc - 4;

						for (int i=0; i < (argc - 4) && (code == NO_ERROR); i++) {
							rotor[i] = new Rotor(argv[i+3]);
							rotor[i]->check_config(argv[i+3]);
							code = rotor[i]->get_code();

							if (code != NO_ERROR) { // delete the rotors
								for (int j=0; j < i; j++)
									delete rotor[j];
								delete [] rotor;
							}
//							cout << "rotor "<< argv[i+3] << " config ok" << endl;
						}

						if (code == NO_ERROR) {
//							cout << "all(s) rotor config ok!" << endl;
							code = set_starting_pos(rotor, number_of_rotor, argv[argc - 1]);
						}

						if (code == NO_ERROR) { // set position succeed

//							cout << "set starting position ok" << endl;

//							cout << argc - 4 << " rotor(s) config using: " << endl; // how many rotors
							// for (int i=3; i <= argc - 2; i++ ) {
							// 	cout << argv[i] << endl;
							// }
//							cout << "Their position are configured using " << argv[argc-1] << endl; // position
						}
					}
					if (code == NO_ERROR) {
//						cout << "config done" << endl; // succeed
					}
				}
			}
		}
	}
}

/* function that implements the config */
void Enigma::implement_config(int argc, char **argv) {
	if (code == NO_ERROR) {
		plugboard->implement_config(argv[1]);
		reflector->implement_config(argv[2]);

		if (number_of_rotor > 0) {
			for (int i=0; i < (argc - 4) ; i++) {
				rotor[i]->implement_config(argv[i+3]);
			}
		}
	}
}

/* encrypt the letter */
int Enigma::encrypt(const int &letter) {

	if (number_of_rotor > 0) { 	// when a letter is pressed, the rightmost rotor rotates
		rotor[number_of_rotor - 1]->rotate();
		for (int i = number_of_rotor-1 ; i>0; i--) {
			for (int j=0; j < (rotor[i]->get_number_of_notch()) ; j++) { // iterator every notches
				if ( rotor[i]->get_top_pos() == rotor[i]->get_notch_pos(j))
					rotor[i-1]->rotate(); // top_pos+1
			}
 		}
	}

	int encoded_letter = letter;

	encoded_letter = plugboard->encrypt(encoded_letter); // plugboard

	if (number_of_rotor > 0) { // pass through rotor(s) go from rightmost to leftmost
		for (int i = number_of_rotor-1 ; i >= 0 ; i--) {
			encoded_letter = rotor[i]->map_r_to_l(encoded_letter);
		}
	}

	encoded_letter = reflector->encrypt(encoded_letter); // reflector

	if (number_of_rotor > 0) { // pass through rotor(s) from leftmost to rightmost
		for (int i=0; i <= number_of_rotor-1 ;i++) {
			encoded_letter = rotor[i]->map_l_to_r(encoded_letter);
		}
	}

	encoded_letter = plugboard->encrypt(encoded_letter); // plugboard

	return encoded_letter;
}


int Enigma::get_code() {
	return code;
}



int Enigma::set_starting_pos(Rotor **rotor, int number_of_rotors, const char *filename) {
	ifstream in;
	in.open(filename);

	if (in.fail())
		return ERROR_OPENING_CONFIGURATION_FILE;

	string input;
	for (int i=0; i < number_of_rotors; i++) {
		if (!(in >> input)) {
			cerr << "No starting position for rotor " << i << " in rotor position file: " << filename << endl;
			return NO_ROTOR_STARTING_POSITION;
		}
		if (!is_numeric(input)) {
			cerr << "Non-numeric character in rotor positions file " << filename << endl;
			return NON_NUMERIC_CHARACTER;
		}
		if (!is_index_valid(input))
			return INVALID_INDEX;

		// rotor[i]->top_pos = string_to_int(input);
		rotor[i]->set_top_pos(string_to_int(input));
	}
	return NO_ERROR;
}




Enigma::~Enigma() {
	if (plugboard != nullptr)
		delete plugboard;
	if (reflector != nullptr)
		delete reflector;
	// if (*rotor != nullptr ) {
	// 	for (int i=0; i < number_of_rotor; i++) {
	// 		delete rotor[i];
	// 	}
	// 	delete [] rotor;
	// }
}
