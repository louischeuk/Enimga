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
    // int alphabet_map[2][26];
    int alphabet_map[26];
public:
    int code;
    int top_pos;
    int number_of_notch;
    int *notch_pos; // should move to private

    Rotor(const char* filename);
    void check_config(const char* filename);
    void implement_config(const char* filename);

    int w(const int &letter);
    int w_inverse(const int &letter);
    int map_r_to_l(const int &letter);
    int map_l_to_r(const int &letter);
    void rotate();
    friend int set_starting_pos(Rotor **rotor, int number_of_rotors, const char *filename); // number_of_rotors is from the enimga class,
};

#endif
