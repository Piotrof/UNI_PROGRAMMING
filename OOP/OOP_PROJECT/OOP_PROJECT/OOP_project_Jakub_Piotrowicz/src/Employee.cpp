#include "Employee.h"
#include "Patient.h"
#include <iostream>
#include <cstring>

Employee::Employee(const Employee& other_obj) {
	this->name = other_obj.name;
	this->ID = other_obj.ID;
	this->hospital_name = other_obj.hospital_name;
	this->ward_name = other_obj.ward_name;
	this->patients = other_obj.patients;
}

Employee::~Employee() {
	delete[] this->name;
	this->patients.clear();
	delete this;
}

bool Employee::add_patient(char* name, int ID) {

	for(int i = 0; i < this->patients.size(); i++)
	{
		if(strcmp(name, this->patients.at(i)->get_name()) == 0)
		{
			return false;
		}
	}

	Patient* temp = new Patient();
	temp->set_name(name);
	temp->set_ID(ID);
	temp->set_hospital_name(this->hospital_name);
	temp->set_ward_name(this->ward_name);
	temp->set_doctor_name(this);

	this->patients.push_back(temp);

	return true;
}

bool Employee::remove_patient(char* name) {

	for(int i = 0; i< this->patients.size(); i++)
	{
		if(strcmp(name, this->patients.at(i)->get_name()) == 0)
		{
			this->patients.erase(this->patients.begin() + i);
			return true;
		}
	}

	return false;
}


char* Employee::get_name() const {

	return this->name;
}

void Employee::set_name(char* name) {

	this->name = name;
}


int Employee::get_ID() const {

	return this->ID;
}

void Employee::set_ID(int ID) {

	this->ID = ID;
}


Hospital* Employee::get_hospital_name() const {

	return this->hospital_name;
}

void Employee::set_hospital_name(Hospital* hospital_name) {

	this->hospital_name = hospital_name;
}


Ward* Employee::get_ward_name() const {

	return this->ward_name;
}

void Employee::set_ward_name(Ward* ward_name) {

	this->ward_name = ward_name;
}


void Employee::print() const {

	std::cout << "\t\tName: " << this->name << " ID: " << this->ID << "\n";

	if(this->patients.size() == 0)
	{
		std::cout << "\t\t\tNo patients.\n";
	}
	else
	{	
		std::cout <<"\t\t\tPatients:\n";
		for(int i = 0; i < this->patients.size(); i++)
		{
			this->patients.at(i)->print();
		}
	}
}