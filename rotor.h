#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "helper.h"
#include "errors.h"

class Rotor {
	int alphabet_map[26]; // stores the 26 alphabets
	int code; // error code
	int top_pos; // stores the top position(s) of the rotor
	int number_of_notch; // stores the number of notches
	int *notch_pos; // stores the notch(es) position of the rotor
public:
	/* constructor */
	Rotor(const char* filename);
	/* function that checks the rotor configuration file */
	void check_config(const char* filename);
	/* function that implements the rotor configuration file to the rotor */
	void implement_config(const char* filename);
	/* function that converts the letter from the right-hand contact to the left-hand contact of rotor */
	int wiring(const int &letter);
	/* function that converts the letter from the left-hand contact to the right-hand contact of rotor */
	int wiring_inverse(const int &letter);
	/* function that converts the letter index from right-hand position to land-hand position of rotor */
	int map_r_to_l(const int &letter);
	/* function that converts the letter index from land-hand position to right-hand position of rotor */
	int map_l_to_r(const int &letter);
	/* function that rotates the rotor by one step */
	void rotate_one_step();
	/* getter function thats get the code */
	int get_code() const;
	/* getter function that gets the top_pos */
	int get_top_pos() const;
	/* setter function that sets the top_pos */
	void set_top_pos(int position);
	/* getter function that gets the number_of_notch */
	int get_number_of_notch() const;
	/* getter function that gets the notch_pos */
	int get_notch_pos(const int &iterator) const;
};

#endif
