#include "rotor.h"
using namespace std;

/* constructor */
Rotor::Rotor(const char* filename) {
	code = NO_ERROR;
	number_of_notch = 0;
	top_pos = 0;
	notch_pos = NULL;

	for (int i=0; i < 26; i++) {
		this->alphabet_map[i] = i;
	}

	cout << "Rotor with configuration file " << filename << endl;
}

/* check the rotor configuration file */
void Rotor::check_config(const char* filename) {

	ifstream in;
	in.open(filename);

	if (in.fail())
		code = ERROR_OPENING_CONFIGURATION_FILE;
	else {
		string input;
		map<string, int> rotor_map; // store the existed numbers

		for (int i=0 ; (i<26) && (code == NO_ERROR) ; i++) { // check the first 26 alphabets index
			if (!(in >> input))
				code = INVALID_ROTOR_MAPPING;
			else {
				if (is_repeated_in_map(input, rotor_map))
					code = INVALID_ROTOR_MAPPING;
				else {
					rotor_map.insert(pair<string,int>(input, i));

					if (!is_index_valid(input))
						code = INVALID_INDEX;
					else if (!is_numeric(input))
						code = NON_NUMERIC_CHARACTER;
					else {
						cout << "alphabet" << input << endl;
					}
				}
			}
		}

		if (code == NO_ERROR) {
			int *temp_notch_pos = new int[26]; // each rotor can have maximum of 26 notches

			for (int i=0 ; (in >> input) && (code == NO_ERROR) ; i++) { // check the turnover notches
				if (!is_index_valid(input))
					code = INVALID_INDEX;
				else if (!is_numeric(input))
					code = NON_NUMERIC_CHARACTER;
				else {
					int input_number = stoi(input);
					if (is_repeated(i, input_number, temp_notch_pos))
						code = INVALID_ROTOR_MAPPING;
					else {
						cout << "notch " << input << endl;
						temp_notch_pos[i] = input_number;
						number_of_notch++;
					}
				}
			}
			in.close();

			if (code == NO_ERROR) {
				if (number_of_notch == 0) // rotor must have at least one notch
					code = INVALID_ROTOR_MAPPING;
			}
			delete[] temp_notch_pos;
		}
	}
}

/* implement the configuration */
void Rotor::implement_config(const char* filename) {
	ifstream in;
	in.open(filename);

	string input;
	int input_number;
	for (int i=0; i < 26 && (code == NO_ERROR); i++) { 	// first 26 alphabet config
		in >> input;
		input_number = stoi(input);
		alphabet_map[i] = input_number; // configuration is stored in righ-hand contact
	}

	int *temp_notch_pos = new int[26]; 	// store notches in temp array
	for (int i=0 ; (in >> input) ; i++) { // input the turnover notches
		temp_notch_pos[i] = input_number;
		number_of_notch++;
	}
	in.close();

	notch_pos = new int[number_of_notch]; // store notches in data member
	for (int notch=0 ; notch < number_of_notch ; notch++ )
		notch_pos[notch] = temp_notch_pos[notch];
	delete[] temp_notch_pos;
}


/* conversion function from the right-hand contact to the left-hand contact of rotor */
int Rotor::w(const int &letter) {
	return alphabet_map[letter];
}

/* conversion function from the left-hand contact to the right-hand contact of rotor */
int Rotor::w_inverse(const int &letter) {
	for (int i=0; i < 26; i++) {
		if (w(i) == letter)
			return i;
	}
	return letter;
}

/* function that conversion the letter index from right-hand contact to land-hand contact of rotor */
int Rotor::map_r_to_l(const int &letter) {
	int r_contact = mod(letter + top_pos);
	int l_contact = w(r_contact);
	int l_pos = mod(l_contact - top_pos);

	return l_pos;
}

/* function that conversion the letter index from land-hand contact to right-hand contact of rotor */
int Rotor::map_l_to_r(const int &letter) {
	int l_contact = mod(letter + top_pos);
	int r_contact = w_inverse(l_contact);
	int r_pos = mod(r_contact - top_pos);

	return r_pos;
}

/* function that rotates the top position by 1 */
void Rotor::rotate() {
	top_pos = (top_pos + 1) % 26;
}


/* friend function that sets the starting postition of rotors */
int set_starting_pos(Rotor **rotor, int number_of_rotors, const char *filename) {
	ifstream in;
	in.open(filename);

	if (in.fail())
		return ERROR_OPENING_CONFIGURATION_FILE;

	string input;
	for (int i=0; i < number_of_rotors; i++) {
		if (!(in >> input))
			return NO_ROTOR_STARTING_POSITION;
		if (!is_index_valid(input))
			return INVALID_INDEX;
		if (!is_numeric(input))
			return NON_NUMERIC_CHARACTER;

		rotor[i]->top_pos = stoi(input);
	}
	return NO_ERROR;
}

/* destructor */
Rotor::~Rotor() {
	// delete [] notch_pos;
}
