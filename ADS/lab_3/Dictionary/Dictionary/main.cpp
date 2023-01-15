#include <iostream>
#include <fstream>
#include "Dictionary.h"


using namespace std;

int main() {

	//set filename 
	string filename = "data.txt";

	//create a new dictionary
	Dictionary<string, int> dict;

	//perform the counter function
	dict = counter(filename);

	//draw the structure of the dictionary
	dict.draw();

	return 0;
}
