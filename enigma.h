#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include "errors.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "helper.h"
using namespace std;

class Enigma {
	Plugboard *plugboard;
	Rotor **rotor;
	Reflector *reflector;
	int number_of_rotor; // number of rotors
	int code;
public:
	Enigma(int argc, char** argv);
	/* checks the enigma configuration files */
	void check_config(int argc, char **argv);
	/* implements the enigma configuration files */
	void implement_config(int argc, char **argv);
	/* encrypts the letter */
	int encrypt(const int &letter);
	/* rotates the rotor(s) once a letter has been inputted */
	void rotor_rotate(int number_of_rotor);
	/* sets the starting position of the rotors */
	int set_starting_pos(Rotor **rotor, int number_of_rotors, const char *filename);
	/* getter function thats get the code */
	int get_code() const;
	/* destructor */
	~Enigma();
};

#endif
