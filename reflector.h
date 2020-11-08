#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <fstream>
#include <map>
#include "helper.h"
#include "errors.h"
using namespace std;

class Reflector {
	int alphabet_map[26];
public:
	int code; // tells whether the config is valid or not
	Reflector(const char *filename);
	void check_config(const char *filename);
	void implement_config(const char *filename);
	int encrypt(const int &letter);
};

#endif
