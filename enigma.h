#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include "errors.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "helper.h"

class Enigma {
	Plugboard *plugboard;
	Rotor **rotor;
	Reflector *reflector;
	int number_of_rotor; // number of rotors
	int code; // error code
public:
	/* constructor */
	Enigma(int argc, char** argv);
	/* function that checks the enigma configuration files */
	void check_config(int argc, char **argv);
	/* fucntion that implements the all configuration files to the enigma*/
	void implement_config(int argc, char **argv);
	/* function that encrypts the letter when it pass through the enigma */
	int encrypt(const int &letter);
	/* function that rotates the rotor(s) once input a letter */
	void rotor_rotate(int number_of_rotor);
	/* function that sets the starting position(s) of the rotor(s) */
	int set_starting_pos(Rotor **rotor, int number_of_rotors, const char *filename);
	/* getter function thats get the code */
	int get_code() const;
	/* destructor */
	~Enigma();
};

#endif
