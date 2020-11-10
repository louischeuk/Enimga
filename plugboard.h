#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <fstream>
#include <map>
#include "helper.h"
#include "errors.h"

class Plugboard {
	int alphabet_map[26];
	int code; // tells whether the config is valid or not
public:
	Plugboard(const char* filename);
	/* checks the plugboard configuration file */
	void check_config(const char* filename);
	/* implements the plugboard configuration file */
	void implement_config(const char* filename);
	/* encrypts the letter  */
	int encrypt(const int &letter);
	/* getter fucntion that gets the code */
	int get_code();
};

#endif
