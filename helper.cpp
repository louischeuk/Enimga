#include "helper.h"

/* function definition of is_index_valid() */
bool is_index_valid(const string &string) {
	int number = string_to_int(string);
	if (number < 0 || number > 25) return 0;
	return 1;
}

/* function definition of is_numeric() */
bool is_numeric(const string &string) {
	for (int i = 0; i < static_cast<int>(string.length()); i++) {
		if ( !isdigit(string[i]) )
			return 0;
	}
	return 1;
}

/* function definition of is_repeated_in_map() */
bool is_repeated_in_map(const string &key, const map<string,int> &map) {
	if(map.count(key))
		return 1;
	return 0;
}

/* function definition of is_repeated() */
bool is_repeated(const int &n, const int &number, const int map[]) {
	// if (n <= 0) return 0; // skip the first one

	for (int i=0; i<n; i++) {
		if (map[i] == number)
			return 1;
	}
	return 0;
}

/* function definition of mod() */
int mod(const int &number) {
	return (number + 26) % 26;
}

/* function definion of string_to_int() */
int string_to_int(const string &string) {
    int number;
    stringstream converter(string);
    converter >> number;

    return number;
}
