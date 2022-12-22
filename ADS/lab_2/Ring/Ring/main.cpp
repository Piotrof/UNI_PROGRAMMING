#include <iostream>
#include "Ring.h"

using namespace std;

int main() {

	Ring<int> source;

	if (source.add(0) == true)
	{
		cout << "added element with key 0 to Ring 'source'.\n";
	}

	if (source.add(1) == true)
	{
		cout << "added element with key 1 to Ring 'source'.\n";
	}

	if (source.add(2) == true)
	{
		cout << "added element with key 2 to Ring 'source'.\n";
	}

	/*source.print();

	if (source.insert(3, 1) == true)
	{
		cout << "inserted element with key 3 after element with key 1.\n";
	}
	source.print();

	if (source.remove(2) == true)
	{
		cout << "removed element with key 2.\n";
	}
	source.print();*/

	Ring<int> res_1;
	Ring<int> res_2;

	source.add(3);
	source.add(4);
	source.add(5);
	source.add(6);
	source.add(7);
	source.add(8);
	source.print();

	//split(source, 3, 1, 4, res_1, 2, -1, 6, res_2);
	split_corrected(source, 1, 2, res_1, 2, 1, res_2, 3, -1);
	cout << "splitting source into res_1 and res_2.\n";
	cout << "res_1:\n";
	res_1.print();
	cout << "res_2\n";
	res_2.print();
 
	return 0;
};
