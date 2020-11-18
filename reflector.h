#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <fstream>
#include <map>
#include "helper.h"
#include "errors.h"

class Reflector {
	int alphabet_map[26]; // stores the 26 alphabets
	int code; // error code
public:
	/* constructor */
	Reflector(const char *filename);
	/* function that checks the reflector configuration file */
	void check_config(const char *filename);
	/* function that implements the reflector configuration file to the reflector */
	void implement_config(const char *filename);
	/* function that encrypts the letter when it passes through the reflector */
	int encrypt(const int &letter);
	/* getter function thats get the code */
	int get_code() const;
};

#endif
