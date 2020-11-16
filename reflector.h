#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <fstream>
#include <map>
#include "helper.h"
#include "errors.h"
using namespace std;

class Reflector {
	int alphabet_map[26];
	int code; // tells whether the config is valid or not
public:
	Reflector(const char *filename);
	/* function that checks the reflector configuration */
	void check_config(const char *filename);
	/* function that implements the reflector configuration */
	void implement_config(const char *filename);
	/* function that encrypts the letter */
	int encrypt(const int &letter);
	/* getter function thats get the code */
	int get_code() const;

};

#endif
