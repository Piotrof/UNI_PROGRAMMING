#pragma once
#ifndef PATIENT_H
#define PATIENT_H

class Hospital;
class Ward;
class Employee;

class Patient
{
private:
	char* name;
	int ID;
	Hospital *hospital_name;
	Ward *ward_name;
	Employee *doctor_name;

public:
	Patient() = default;
	Patient(const Patient& other_obj);
	~Patient();

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
	 * @brief Get the name of the hospital this patient belongs to
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
	 * @brief Get the name of the ward this patient belongs to
	 * 
	 * @return Ward* 
	 */
	Ward* get_ward_name() const;

	/**
	 * @brief Set this object's ward's name
	 * 
	 * @param ward_name 
	 */
	void set_ward_name(Ward* ward_name);

	/**
	 * @brief Get the name of the employee this patient belongs to 
	 * 
	 * @return Employee* 
	 */
	Employee* get_doctor_name() const;

	/**
	 * @brief Set this object's employee's name
	 * 
	 * @param employee_name 
	 */
	void set_doctor_name(Employee* employee_name);

	/**
	 * @brief print all information about this patient
	 * 
	 */
	void print() const;
};

#endif
