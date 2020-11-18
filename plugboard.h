#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <fstream>
#include <map>
#include "helper.h"
#include "errors.h"

class Plugboard {
	int alphabet_map[26]; // stores the 26 alphabets
	int code; // error code
public:
	/* constructor */
	Plugboard(const char* filename);
	/* fucntion that checks the plugboard configuration file */
	void check_config(const char* filename);
	/* function that implements with the plugboard configuration file to plugboard */
	void implement_config(const char* filename);
	/* function thats encrypts the letter when it passes through the plugboard */
	int encrypt(const int &letter);
	/* getter fucntion that gets the code */
	int get_code() const;
};

#endif
