#include "plugboard.h"
using namespace std;

/* constructor */
Plugboard::Plugboard(const char* filename) {

	code = NO_ERROR;
	for (int i=0; i < 26; i++)
		this->alphabet_map[i] = i;

//	cout << "Plugboard with configuration file: " << filename << endl;
}

/* check configuration */
void Plugboard::check_config(const char* filename) {

	ifstream in;
	in.open(filename);

	if (in.fail()) 	// if fails to open filename
		code = ERROR_OPENING_CONFIGURATION_FILE;
	else {
		string input;
		int count = 0;
		map<string, int> plugboard_map; // store the existed plug number

		while ( (in >> input) && (code == NO_ERROR) ) { // get first string of each pair
			count++;

			if (count > 26) {
				cerr << "Incorrect number of parameters in plugboard file " << filename << endl;
				code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
			} else if (is_repeated_in_map(input, plugboard_map)) { // check all the conditions
				code = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
			} else {
				plugboard_map.insert(pair<string,int>(input, count));

				if (!is_index_valid(input)) {
					code = INVALID_INDEX;
				} else if (!is_numeric(input)) {
					cerr << "Non-numeric character in plugboard file " << filename << endl;
					code = NON_NUMERIC_CHARACTER;
				} else {
					if (!(in >> input)) { // if total amount is odd number
						cerr << "Incorrect number of parameters in plugboard file " << filename << endl;
						code = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
					} else { // get second string of each pair
						count++;
						if (is_repeated_in_map(input, plugboard_map)) {
							code = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
						} else {
							plugboard_map.insert(pair<string,int>(input,count));
							if (!is_index_valid(input))
								code = INVALID_INDEX;
							else if (!is_numeric(input)) {
								cerr << "Non-numeric character in plugboard file " << filename << endl;
								code = NON_NUMERIC_CHARACTER;
							}
						}
					}
				}
			}
		}
	}
	in.close();
}

void Plugboard::implement_config(const char* filename) {
	/* if passes, get a pair each time and swap with each other */
	if (code == NO_ERROR) {
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
	//////////////////////
//	cout << code << endl;
//	cout << "Plugboard array: ";
//	for (int j=0; j < 26; j++) {
//		cout << alphabet_map[j] << " ";
//	}
//	cout << endl;
	///////////////
}

/* encrypt the letter(s) with the plugboard setting */
int Plugboard::encrypt(const int &letter) {
	return alphabet_map[letter];
}

int Plugboard::get_code() {
	return code;
}
