#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "helper.h"
// #include "enigma.h"
#include "errors.h"

// class Enigma;

class Rotor {
	int alphabet_map[26];
	int code;
	int top_pos;
	int number_of_notch;
	int *notch_pos;
public:
	Rotor(const char* filename);
	void check_config(const char* filename);
	void implement_config(const char* filename);

	int w(const int &letter);
	int w_inverse(const int &letter);
	int map_r_to_l(const int &letter);
	int map_l_to_r(const int &letter);
	void rotate();

	int get_code();
	int get_top_pos();
	void set_top_pos(int position); // setter
	int get_number_of_notch();
	int get_notch_pos(const int &iterator);

};

#endif
