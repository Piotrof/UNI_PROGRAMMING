#include <iostream>
#include "Sequence.h"

using namespace std;

int main(){
	
	/*testing the functionality*/
	cout << "Creating a sequence S1\n\n";
	Sequence<int,int> S1;
	cout << "Adding data to S1\n";
	S1.add(1, 3);
	S1.add(3, 2);
	S1.print();

	cout << "\nPushing el. no. 2 to front\n\n";
	S1.push_front(3, 2);
	S1.print();

	cout << "\n";
	S1.add(4, 6);
	S1.print();

	cout << "\nPusing el. no. 2 to back\n\n";
	S1.push_back(1, 3);
	S1.print();

	cout << "Testing split function.\n";
	Sequence<int, int> res_1;
	Sequence<int, int> res_2;

	split(S1, res_1, 5, 2, res_2, 6, 3);
	cout << "Printing result 1.\n";
	res_1.print();
	cout << "Printing result 2.\n";
	res_2.print();

	return 0;
}