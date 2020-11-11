#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "helper.h"
#include "errors.h"
using namespace std;

class Rotor {
	int alphabet_map[26];
	int code;
	int top_pos;
	int number_of_notch;
	int *notch_pos;
public:
	Rotor(const char* filename);
	/* checks the rotor configuration file */
	void check_config(const char* filename);
	/* implements the rotor configuration file */
	void implement_config(const char* filename);
	/* converts the letter from the right-hand contact config to the left-hand contact of rotor config*/
	int w(const int &letter);
	/* converts the letter from the left-hand contact config to the right-hand contact of rotor config */
	int w_inverse(const int &letter);
	/* converts the letter index from right-hand position to land-hand position of rotor */
	int map_r_to_l(const int &letter);
	/* converts the letter index from land-hand position to right-hand position of rotor */
	int map_l_to_r(const int &letter);
	/* function that rotates the rotor by one step */
	void rotate_one_step();
	/* getter function thats get the code */
	int get_code();
	/* getter function that gets the top_pos */
	int get_top_pos();
	/* setter function that set the top_pos */
	void set_top_pos(int position);
	/* getter function that gets the number_of_notch */
	int get_number_of_notch();
	/* getter function that gets the notch_pos */
	int get_notch_pos(const int &iterator);
};

#endif
