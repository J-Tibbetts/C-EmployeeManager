#pragma once
#include"Hourly_Employee.h"
#include"Salary_Employee.h"
#include"ConsoleIOValidator.h"
#include"Paycheck.h"
#include<iostream>
#include<string>
#include <iomanip>
using namespace std;
class Emprec_Entry_Prompter :
	public ConsoleIOValidator
{
private:
	const static int MAX_NAME_LEN = 30,
		MAX_LINE_LEN = 80,
		PHONE_LEN = 10;
	EmpRec* mEmployee;

	//These private functions are to be called by the public functions
	//of Emprec_Entry_Prompter
	void inputSalaryStatus();
	void inputEmploymentStatus();
	void inputName(bool lastName);
	void inputStreet();
	void inputCity();
	void inputState();
	void inputZip();
	void inputPhone();
	void inputPayrate();
	void inputHours();
	void inputYearsEmployed();


public:
	Emprec_Entry_Prompter() {
		this->mEmployee = nullptr;
	};

	~Emprec_Entry_Prompter() {
		if (this->mEmployee != nullptr) {
			delete this->mEmployee;
			this->mEmployee = nullptr;
		}
	}

	void createNewEmpRec(int empID);
	void modifyEmpRec();

	void setCurrentEmployee(EmpRec* emprec);
	void printCurrentEmployee();
	void printPaycheck() ;
	EmpRec* getCurrentEmployee();
	void clear();
};
