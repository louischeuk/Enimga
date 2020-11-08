#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <fstream>
#include <map>
#include "helper.h"
#include "errors.h"

class Plugboard {
	int alphabet_map[26];
public:
	int code; // tells whether the config is valid or not
	Plugboard(const char* filename);
	void check_config(const char* filename);
	void implement_config(const char* filename);
	int encrypt(const int &letter);
};

#endif
