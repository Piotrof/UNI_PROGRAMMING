#pragma once
#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Ward.h"
#include "Employee.h"
#include "Patient.h"
#include <vector>

class Hospital
{
private:
	char* name;
	std::vector <Ward*> wards;
	std::vector <Employee*> employees;
	std::vector <Patient*> patients;

public:
	Hospital() = default;
	/**
	 * @brief Copy constructor, constructs a new object of this class with the same pareameters as the given object
	 * 
	 * @param other_obj 
	 */
	Hospital(const Hospital& other_obj);
	~Hospital();

	/**
	 * @brief Get this object's name
	 * 
	 * @return char* 
	 */
	char* get_name();

	/**
	 * @brief Set this object's name
	 * 
	 * @param name 
	 */
	void set_name(char* name);

	/**
	 * @brief adds a new ward to this hospital
	 * 
	 * @param name 
	 * @return true if the ward is added successfully
	 * @return false if the ward cannot be added
	 */
	bool add_ward(char* name);

	/**
	 * @brief removes a ward from this hospital
	 * 
	 * @param name 
	 * @return true if the ward is removed successfully
	 * @return false if the ward cannot be removed
	 */
	bool remove_ward(char* name);

	/**
	 * @brief adds an employee to this hospital
	 * 
	 * @param name 
	 * @param ID 
	 * @param ward_name 
	 * @return true if the employee is added successfully
	 * @return false if the employee cannot be added
	 */
	bool add_employee(char* name, int ID, char* ward_name);

	/**
	 * @brief removes an employee from this hospital
	 * 
	 * @param name 
	 * @return true if the employee is removed successfully
	 * @return false if the employee cannot be removed
	 */
	bool remove_employee(char* name);

	/**
	 * @brief adds a patient to this hospital 
	 * 
	 * @param name 
	 * @param ID 
	 * @param ward_name 
	 * @param employee_name 
	 * @return true if the patient is addeed successfully 
	 * @return false if the patient cannot be added 
	 */
	bool add_patient(char* name, int ID, char* ward_name, char* employee_name);

	/**
	 * @brief removes a patient from this hospital 
	 * 
	 * @param name 
	 * @return true if the patient is removed successfully
	 * @return false if the patient cannot be removed 
	 */
	bool remove_patient(char* name);

	/**
	 * @brief prints all the information about this hospital
	 * 
	 */
	void print() const;
};

#endif 
