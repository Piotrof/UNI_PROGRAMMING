#include "Patient.h"
#include <iostream>

Patient::Patient(const Patient& other_obj) {
	this->name = other_obj.name;
	this->ID = other_obj.ID;
	this->hospital_name = other_obj.hospital_name;
	this->ward_name = other_obj.ward_name;
	this->doctor_name = other_obj.doctor_name;
}

Patient::~Patient() {
	delete[] this->name;
	delete this;
}

char* Patient::get_name() const {

	return this->name;
}

void Patient::set_name(char* name) {

	this->name = name;
}


int Patient::get_ID() const {

	return this->ID;
}

void Patient::set_ID(int ID) {

	this->ID = ID;
}


Hospital* Patient::get_hospital_name() const {

	return this->hospital_name;
}

void Patient::set_hospital_name(Hospital* hospital_name) {

	this->hospital_name = hospital_name;
}


Ward* Patient::get_ward_name() const {

	return this->ward_name;
}

void Patient::set_ward_name(Ward* ward_name) {

	this->ward_name = ward_name;
}


Employee* Patient::get_doctor_name() const {

	return this->doctor_name;
}

void Patient::set_doctor_name(Employee* employee_name) {

	this->doctor_name = employee_name;
}

void Patient::print() const {

	std::cout << "\t\t\tName: " << this->name << " ID: " << this->ID << "\n";
}