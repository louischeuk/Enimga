#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

/* function that returns FALSE if the file contains a number that is not between 0 and 25 */
bool is_index_valid(const string &string);
/* fucntion that returns TRUE if all characters in the file are numeric */
bool is_numeric(const string &string);
/* function that returns TRUE if all characters in the file are numeric */
bool is_repeated_in_map(const string &key, const map<string,int> &map);
/* function that returns TRUE if there is repeated character in a file */
bool is_repeated(const int &n, const int &number, const int map[]);
/* function that takes the modulus of number by dividing 26 */
int mod(const int &number);
/* function that converts a string to an integer */
int string_to_int(const string &string);

#endif
