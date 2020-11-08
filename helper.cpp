#include "helper.h"

/* function definition that return FALSE if the file contains a number that is not between 0 and 25 */
bool is_index_valid(const string &string) {
	int number = stoi(string);
	if (number < 0 || number > 25) return 0;
	return 1;
}

/* function definition that returns TRUE if all characters in the file are numeric */
bool is_numeric(const string &string) {
	for (int i = 0; i < static_cast<int>(string.length()); i++) {
		if ( !isdigit(string[i]) )
			return 0;
	}
	return 1;
}

/* function definition that returns TRUE if there is repeated character in a file */
bool is_repeated_in_map(const string &key, const map<string,int> &map) {
	if(map.count(key))
		return 1;
	return 0;
}

/* function that returns TRUE if there is repeated character in an array */
bool is_repeated(const int n, const int number, const int map[]) {
	if (n <= 0) return 0; // skip the first one

	for (int i=0; i<n; i++) {
		if (map[i] == number)
			return 1;
	}
	return 0;
}

/* functio that returns the remainder when dividing number by 26 */
int mod(const int &number) {
	return (number + 26) % 26;
}

int string_to_int(const string &string) {
    int number;
    stringstream converter(string);
    converter >> number;
    
    return number;
}
