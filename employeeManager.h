#pragma once
#include"Employee_Entry_Prompter.h"
#include"Paycheck.h"
#include<algorithm>
class EmployeeManager
{
private:
	vector<EmpRec*> mEmployees;

	Emprec_Entry_Prompter mAssistant;
	int nextID;

	void eraseEmployee(int empID);
	int assignID();
	void sort();


public:
	EmployeeManager() {
		nextID = 1;
	};

	void start();

	void addEmployeeRecord();
	void updateEmployeeRecord();
	void deleteEmployeeRecord();
	void printAllEmployees();
	void printPayrollReport();

	EmpRec* getEmployee(int empID);
	vector<EmpRec*> getAllEmployees() const;
	vector<int> getAllEmpID();
};

