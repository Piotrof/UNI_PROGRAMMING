#pragma once
#ifndef WARD_H
#define WARD_H

#include <vector>

class Hospital;
class Employee;
class Patient;

class Ward
{
private:
	char* name;
	Hospital* hospital_name;
	std::vector <Employee*> employees;
	std::vector <Patient*> patients;

public:
	Ward() = default;
	Ward(const Ward& other_obj);
	~Ward();

	/**
	 * @brief Get this object's name
	 * 
	 * @return char* 
	 */
	char* get_name() const;

	/**
	 * @brief Set this object's name
	 * 
	 * @param name 
	 */
	void set_name(char* name);

	/**
	 * @brief Get the name of the hospital this object belongs to
	 * 
	 * @return Hospital* 
	 */
	Hospital* get_hospital_name() const;

	/**
	 * @brief Set this object's hospital's name
	 * 
	 * @param hospital_name 
	 */
	void set_hospital_name(Hospital* hospital_name);

	/**
	 * @brief adds an employee to this ward
	 * 
	 * @param name 
	 * @param ID 
	 * @return true if the employee is added successfully
	 * @return false if the employee cannot be added
	 */
	bool add_employee(char* name, int ID);

	/**
	 * @brief removes an employee from this ward
	 * 
	 * @param name 
	 * @return true if the employee is removed successfully
	 * @return false if the employee cannot be removed
	 */
	bool remove_employee(char* name);

	/**
	 * @brief adds a patient to this ward
	 * 
	 * @param name 
	 * @param ID 
	 * @param employee_name 
	 * @return true if the patient is added successfully
	 * @return false if the patient cannot be added
	 */
	bool add_patient(char* name, int ID, char* employee_name);

	/**
	 * @brief removes a patient from this ward
	 * 
	 * @param name 
	 * @return true if the patient is removed successsfully
	 * @return false if the patient cannot be removed
	 */
	bool remove_patient(char* name);

	/**
	 * @brief prints all information about this ward
	 * 
	 */
	void print() const;
};

#endif
