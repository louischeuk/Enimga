#include "reflector.h"
using namespace std;

/* constructor */
Reflector::Reflector(const char* filename) {
	code = NO_ERROR;
	for (int i=0; i < 26; i++)
		this->alphabet_map[i] = i;
}

/* function definition of check_config() */
void Reflector::check_config(const char *filename) {

	ifstream in;
	in.open(filename);

	if ( in.fail() ) { 	// if fails to open filename
		cerr << "Error opening configuration file in reflector file: " << filename << endl;
				code = ERROR_OPENING_CONFIGURATION_FILE;
	} else {
		string input;
		int count = 0;
		map<string, int> reflector_map;

		while ( (in >> input) && (code == NO_ERROR) ) { // for every string from the filename
			count++;

			// check varies conditions that would cause faulty
			if (count > 26) {
				cerr << "Incorrect (odd) number of parameters in reflector file " << filename << endl;
				code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
			} else if (is_repeated_in_map(input, reflector_map)) {
				cerr << "Invalid reflector mapping in reflector file " << filename << endl;
				code = INVALID_REFLECTOR_MAPPING;
			} else {
				reflector_map.insert(pair<string,int>(input, count)); // put every string into the map

				if (!is_index_valid(input)) {
					cerr << "Invalid index in reflector file " << filename << endl;
					code = INVALID_INDEX;
				} else if (!is_numeric(input)) {
					cerr << "Non-numeric character in reflector file " << filename << endl;
					code = NON_NUMERIC_CHARACTER;
				} else {
					if (!(in >> input)) {
						cerr << "Incorrect (odd) number of parameters in reflector file " << filename << endl;
						code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
					} else {
						count++;
						if (is_repeated_in_map(input, reflector_map)) {
							cerr << "Invalid reflector mapping in reflector file " << filename << endl;
							code = INVALID_REFLECTOR_MAPPING;
						} else {
							reflector_map.insert(pair<string,int>(input, count));

							if (!is_index_valid(input)) {
								cerr << "Invalid index in reflector file " << filename << endl;
								code = INVALID_INDEX;
							} else if (!is_numeric(input)) {
								cerr << "Non-numeric character in reflector file " << filename << endl;
								code = NON_NUMERIC_CHARACTER;
							}
						}
					}
				}
			}
		}
		if (code == NO_ERROR) {
			if ((count < 26)) { // reflector has to have exactly 26 alphabets
				cerr << "Insufficient number of mappings in reflector file: " << filename << endl;
				code = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
			}
		}
	}
	in.close();
}

/* function defintion of implement_config() */
void Reflector::implement_config(const char *filename) {
	ifstream in_2;
	in_2.open(filename);

	string input;
	int input_number_1, input_number_2;
	while (in_2 >> input) {
		input_number_1 = string_to_int(input);
		in_2 >> input;
		input_number_2 = string_to_int(input);
		alphabet_map[input_number_1] = input_number_2; // swap the pair
		alphabet_map[input_number_2] = input_number_1;
	}
	in_2.close();
}

/* function definition of encrypt() */
int Reflector::encrypt(const int &letter) {
	return alphabet_map[letter];
}

/* getter function definition of get_code() */
int Reflector::get_code() const {
	return code;
}
