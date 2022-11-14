#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <vector>

class Hospital;
class Ward;
class Patient;

class Employee
{
private:
	char* name;
	int ID;
	Hospital *hospital_name;
	Ward *ward_name;
	std::vector <Patient*> patients;

public:
	Employee() = default;
	Employee(const Employee& other_obj);
	~Employee();

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
	 * @brief Get this object's ID
	 * 
	 * @return int 
	 */
	int get_ID() const;

	/**
	 * @brief Set this object's ID
	 * 
	 * @param ID 
	 */
	void set_ID(int ID);

	/**
	 * @brief Get the name of the hospital this employee belongs to
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
	 * @brief Get the name of the ward this employee belongs to
	 * 
	 * @return Ward* 
	 */
	Ward* get_ward_name() const;

	/**
	 * @brief Set this object's ward name
	 * 
	 * @param ward_name 
	 */
	void set_ward_name(Ward* ward_name);
	
	/**
	 * @brief adds a patient to this employee
	 * 
	 * @param name 
	 * @param ID 
	 * @return true if the patient is added successsfully
	 * @return false if the patient cannot be added
	 */
	bool add_patient(char* name, int ID);

	/**
	 * @brief removes a patient from this employee
	 * 
	 * @param name 
	 * @return true if the patient is removed successfully
	 * @return false if the patient cannot be removed
	 */
	bool remove_patient(char* name);

	/**
	 * @brief prints all information about this employee
	 * 
	 */
	void print() const;
};

#endif 
