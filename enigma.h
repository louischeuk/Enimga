#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include "errors.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "helper.h"

// class Rotor;

class Enigma {
	Plugboard *plugboard;
	Rotor **rotor;
	Reflector *reflector;
	int number_of_rotor; // number of rotors
	int code;
public:

	Enigma(int argc, char** argv);
	void check_config(int argc, char **argv);
	void implement_config(int argc, char **argv);
	int encrypt(const int &letter);

	int get_code(); // setter
	~Enigma();

	// int set_starting_pos(Rotor **rotor, int number_of_rotors, const char *filename); // in rotor
};

#endif
