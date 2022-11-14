#include "Hospital.h"
#include <iostream>
#include <cstring>

Hospital::Hospital(const Hospital& other_obj) {
	this->name = other_obj.name;
	this->wards = other_obj.wards;
	this->employees = other_obj.employees;
	this->patients = other_obj.patients;
}

Hospital::~Hospital() {

	delete[] this->name;
	this->wards.clear();
	this->employees.clear();
	this->patients.clear();
	delete this;
}

char* Hospital::get_name() {

	return this->name;
}

void Hospital::set_name(char* name) {

	this->name = name;
}

bool Hospital::add_ward(char* name) {

	for(int i = 0; i < this->wards.size(); i++)
	{
		if(strcmp(name, this->wards.at(i)->get_name()) == 0)
		{
			return false;
		}
	}

	Ward* temp = new Ward();
	temp->set_name(name);
	temp->set_hospital_name(this);

	this->wards.push_back(temp);

	return true;
}

bool Hospital::remove_ward(char* name) {

	for(int i = 0; i < this->wards.size(); i++)
	{
		if(strcmp(name, this->wards.at(i)->get_name()) == 0)
		{	
			for(int j = 0; j < this->employees.size(); j++)
			{
				if(strcmp(name, (char*)this->employees.at(i)->get_ward_name()) == 0)
				{
					this->employees.at(i)->set_ward_name(nullptr);
				}
			}

			this->wards.erase(this->wards.begin() + i);

			return true;
		}
	}

	return false;
}

bool Hospital::add_employee(char* name, int ID, char* ward_name) {
	
	bool isWard = false;
	Ward* temp_ward = new Ward();

	for(int i = 0; i < this->wards.size(); i++)
	{
		if(strcmp(ward_name, this->wards.at(i)->get_name()) == 0)
		{
			isWard = true;
			temp_ward = this->wards.at(i);
		}
	}

	if(isWard == false)
	{	
		std::cout << "No such Ward in this hospital.\n";
		return false;
	}

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
	temp->set_hospital_name(this);
	temp->set_ward_name(temp_ward);

	for(int i = 0; i < this->wards.size(); i++)
	{
		if(strcmp(ward_name, this->wards.at(i)->get_name()) == 0)
		{
			this->wards.at(i)->add_employee(name, ID);
			break;
		}
	}

	this->employees.push_back(temp);

	return true;	
}

bool Hospital::remove_employee(char* name) {

	for(int i = 0; i < this->employees.size(); i++)
	{
		if(strcmp(name, this->employees.at(i)->get_name()) == 0)
		{
			this->wards.at(i)->remove_employee(name);

			this->employees.erase(this->employees.begin() + i);
			return true;
		}
	}

	return false;
}

bool Hospital::add_patient(char* name, int ID, char* ward_name, char* employee_name) {

	bool isWard = false;
	bool isEmployee = false;
	Ward* temp_ward = new Ward();
	Employee* temp_employee = new Employee();

	for(int i = 0; i < this->wards.size(); i++)
	{
		if(strcmp(ward_name, this->wards.at(i)->get_name()) == 0)
		{
			isWard = true;
			temp_ward = this->wards.at(i);
		}
	}

	if(isWard == false)
	{
		std::cout <<"No such ward in this hospital.\n";
		return false;
	}

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
		std::cout <<"No such employee in this hospital.\n";
		return false;
	}

	Patient* temp = new Patient();
	temp->set_name(name);
	temp->set_ID(ID);
	temp->set_hospital_name(this);
	temp->set_ward_name(temp_ward);
	temp->set_doctor_name(temp_employee);

	for(int i = 0; i < this->wards.size(); i++)
	{
		if(strcmp(ward_name, this->wards.at(i)->get_name()) == 0)
		{
			this->wards.at(i)->add_patient(name, ID, employee_name);
			break;
		}
	}

	this->patients.push_back(temp);

	return true;
}

bool Hospital::remove_patient(char* name) {

	for(int i = 0; i < this->patients.size(); i++)
	{
		if(strcmp(name, this->patients.at(i)->get_name()) == 0)
		{	
			for(int j = 0; j < this->wards.size(); j++)
			{
				this->wards.at(j)->remove_patient(name);
			}

			this->patients.erase(this->patients.begin() + i);
			return true;
		}
	}
	return true;
}

void Hospital::print() const {
	
	std::cout << "Name: " << this->name << "\n";

	if(this->wards.size() == 0)
	{
		std::cout << "\tNo wards.\n";
	}
	else
	{	
		std::cout << "\tWards: \n";
		for(int i = 0; i < this->wards.size(); i++)
		{
			this->wards.at(i)->print();
		}
	}
	std::cout<<"\n";
}