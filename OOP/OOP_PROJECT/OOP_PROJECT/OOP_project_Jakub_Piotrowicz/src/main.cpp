#include "Hospital.h"
#include <iostream>

using namespace std;

int main() {

	//creating an object of the 'Hospital' class
	Hospital h1;

	//setting the name of the Hospital
	h1.set_name("Saint George's Hospital");
	//adding a Ward
	h1.add_ward("Oncology");

	//trying to add the same Ward again
	cout << "Test 1: ";
	if(h1.add_ward("Oncology") == false)
	{
		cout << "Failed to add the Ward\n";
	}

	//adding a second, different Ward
	h1.add_ward("Dermatology");

	//trying to add an Employee to a Ward that doesn't exist
	cout << "Test 2: ";
	h1.add_employee("John Swanson", 1, "ER");
	

	//adding Employees to a Wards which exists
	h1.add_employee("John Swanson", 1, "Oncology");
	h1.add_employee("Johnnie Walker", 2, "Dermatology");

	//trying to assign a Patient to an Employee who doesn't exist
	cout << "Test 3: ";
	h1.add_patient("Teo", 1, "Oncology","Babe Ruth");

	//trying to assign a Patient to a Ward that doesn't exist
	cout << "Test 4: ";
	h1.add_patient("Teo", 1, "ER", "John Swanson");

	//assigning Patients to Employees
	h1.add_patient("Teo", 1, "Oncology","John Swanson");
	h1.add_patient("Sareen", 1, "Dermatology", "Johnnie Walker");

	//displaying information about the hospital
	h1.print();

	//creating a second object with the copy constructor
	Hospital h2(h1);

	//printing information about the two objects 
	h1.print();
	h2.print();

	//removing and adding patients, employees and wards from the second hospital to introduce changes
	cout << "Test 5: \n";
	h2.remove_employee("Teo");
	h2.add_ward("ER");
	h2.add_employee("Booba Fett", 3, "ER");

	//displaying the new information
	h1.print();
	h2.print();

	//using the overloaded '=' operator to copy data from h2 to h1
	h1 = h2;
	
	//printing information about both Hospitals
	h1.print();
	h2.print();

	return 0;
}