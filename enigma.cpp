#include "enigma.h"

/* constructor */
Enigma::Enigma(int argc, char** argv) {
	code = NO_ERROR;
	plugboard = nullptr;
	rotor = nullptr;
	reflector = nullptr;
	number_of_rotor = 0;
}

/* function that checks the enigma configuration files */
void Enigma::check_config(int argc, char **argv) {
	if (argc == 1) {
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
		code = INSUFFICIENT_NUMBER_OF_PARAMETERS;
	} else {
		plugboard = new Plugboard(argv[1]);
		plugboard->check_config(argv[1]);
		code = plugboard->get_code();
		if (code == NO_ERROR) {

			if (argc == 2) {
				cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
				code = INSUFFICIENT_NUMBER_OF_PARAMETERS;
			} else {
				reflector = new Reflector(argv[2]);
				reflector->check_config(argv[2]);
				code = reflector->get_code();
				if (code == NO_ERROR) {

					if (argc == 3) {
						cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
						code = INSUFFICIENT_NUMBER_OF_PARAMETERS;
					} else if (argc >= 4) {
						if (argc > 4 ) {
							rotor = new Rotor *[argc - 4]; // an array of rotors
							number_of_rotor = argc - 4;

							for (int i=0; i < (argc - 4) && (code == NO_ERROR); i++) {
								rotor[i] = new Rotor(argv[i+3]);
								rotor[i]->check_config(argv[i+3]);
								code = rotor[i]->get_code();
							}

							if (code == NO_ERROR) {
								code = set_starting_pos(rotor, number_of_rotor, argv[argc - 1]);
							}
						}
					}
				}
			}
		}
	}
}

/* function that implements the enigma configuration files */
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

/* function that encrypts the letter */
int Enigma::encrypt(const int &letter) {

	if (number_of_rotor > 0)
		rotor_rotate(number_of_rotor); // rotate the rotor(s)

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

/* function that rotates the rotor(s) once a letter has been inputted */
void Enigma::rotor_rotate(int number_of_rotor) {

	if (number_of_rotor > 0) { // base case
		rotor[number_of_rotor - 1]->rotate_one_step(); // top_pos + 1

		for (int i=0; i < rotor[number_of_rotor - 1]->get_number_of_notch() ; i++) { // iterate all notches at that rotor
			if ( rotor[number_of_rotor - 1]->get_top_pos() == rotor[number_of_rotor - 1]->get_notch_pos(i)) { // if top_pos == notch_pos
				rotor_rotate(number_of_rotor-1); // go to left rotor
			}
		}
	}
}

/* setter function that sets the starting position of the rotors */
int Enigma::set_starting_pos(Rotor **rotor, int number_of_rotors, const char *filename) {
	ifstream in;
	in.open(filename);

	if (in.fail()) {
		cerr << "Error opening configuration file in rotor position file: " << filename << endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}

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
		if (!is_index_valid(input)) {
			cerr << "Invalid input in the file " << filename << endl;
			return INVALID_INDEX;
		}
		rotor[i]->set_top_pos(string_to_int(input));
	}
	return NO_ERROR;
}

/* getter function thats get the code */
int Enigma::get_code() const {
	return code;
}

/* destructor */
Enigma::~Enigma() {
	if (plugboard != nullptr)
		delete plugboard;
	if (reflector != nullptr)
		delete reflector;
	if ( rotor != nullptr ) { // check if the array exists
		for (int i=0; i < number_of_rotor; i++) { // for every rotor
			if (rotor[i] != nullptr) {
				delete rotor[i];
			}
		}
		delete[] rotor;
	}
}
