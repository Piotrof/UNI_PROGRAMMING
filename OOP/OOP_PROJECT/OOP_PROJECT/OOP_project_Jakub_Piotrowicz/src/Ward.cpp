#include "Ward.h"
#include "Employee.h"
#include "Patient.h"
#include <iostream>
#include <cstring>

Ward::Ward(const Ward& other_obj) {

	this->name = other_obj.name;
	this->hospital_name = other_obj.hospital_name;
	this->employees = other_obj.employees;
	this->patients = other_obj.patients;
}

Ward::~Ward() {
	delete[] this->name;
	this->employees.clear();
	this->patients.clear();
	delete this;
}


bool Ward::add_employee(char* name, int ID) {

	for(int i = 0; i < this->employees.size(); i++)
	{
		if(strcmp(name, this->employees.at(i)->get_name()) == 0)
		{
			return false;
		}
	}

	Employee* temp = new Employee();
	temp->set_name(name);
	temp->set_ID(ID);
	temp->set_hospital_name(this->hospital_name);
	temp->set_ward_name(this);

	this->employees.push_back(temp);

	return true;
}

bool Ward::remove_employee(char* name) {

	for(int i = 0; i< this->employees.size(); i++)
	{
		if(strcmp(name, this->employees.at(i)->get_name()) == 0)
		{	
			for(int j = 0; j < this->patients.size(); j++)
			{	
				if(strcmp(name, (char*)this->patients.at(i)->get_doctor_name()) == 0)
				{
					this->patients.at(i)->set_doctor_name(nullptr);
				}
			}

			this->employees.erase(this->employees.begin() + i);
			return true;
		}
	}

	return false;
}

bool Ward::add_patient(char* name, int ID, char* employee_name) {

	bool isEmployee = false;
	Employee* temp_employee = new Employee();

	for(int i = 0; i < this->employees.size(); i++)
	{
		if(strcmp(employee_name, this->employees.at(i)->get_name()) == 0)
		{
			isEmployee = true;
			temp_employee = this->employees.at(i);
		}
	}

	if(isEmployee == false)
	{
		std::cout << "No such employee in this hospital.\n";
	}

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
	temp->set_ward_name(this);

	for(int i = 0; i < this->employees.size(); i++)
	{
		if(strcmp(employee_name,this->employees.at(i)->get_name()) == 0)
		{
			this->employees.at(i)->add_patient(name, ID);
			break;
		}
	}

	this->patients.push_back(temp);

	return true;
}

bool Ward::remove_patient(char* name) {

	for(int i = 0; i < this->patients.size(); i++)
	{
		if(strcmp(name, this->patients.at(i)->get_name()) == 0)
		{	
			for(int j = 0; j < this->employees.size(); j++)
			{
				this->employees.at(i)->remove_patient(name);
			}

			this->patients.erase(this->patients.begin() + i);
			return true;
		}
	}
}

char* Ward::get_name() const {

	return this->name;
}

void Ward::set_name(char* name) {

	this->name = name;
}


Hospital* Ward::get_hospital_name() const {

	return this->hospital_name;
}

void Ward::set_hospital_name(Hospital* hospital_name) {

	this->hospital_name = hospital_name;
}


void Ward::print() const {

	std::cout << "\tName: " << this->name << "\n";

	if(this->employees.size() == 0)
	{
		std::cout << "\t\tNo employees.\n";
	}
	else
	{
		std::cout << "\t\tEmployees: \n";
		for(int i = 0; i < this->employees.size(); i++)
		{
			this->employees.at(i)->print();
		}
	}
}