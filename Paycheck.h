#pragma once
#include<string>
#include<vector>
#include"Salary_Employee.h"
#include"Hourly_Employee.h"


class Paycheck
{
private:
	int mEmpID;
	std::string mEmployeeName;
	float mPreTaxIncome;
	float mAdjustedEarnings;
	float mStateTax;
	float mFederalTax;
	float mFicaWithholding;
public:
	const static float FED_TAX_RATE;
	const static float STATE_TAX_RATE;
	const static float FICA_RATE;

	Paycheck() {
		this->mEmpID = 0;
		this->mEmployeeName = "";
		this->mPreTaxIncome = 0.0;
	}
/*
	Paycheck(EmpRec* emprec) {
		setEmployee(emprec);
	}
	
	void setEmployee(EmpRec* emprec) {
		this->mEmpID = emprec->getEmpID();
		this->mEmployeeName = emprec->getFirstName() + " " + emprec->getLastName();
		this->mPreTaxIncome = emprec->calcWeeklyEarnings();
		calcFedTax();
		calcStateTax();
		calcFICA();
		calcAdjustedIncome();
	}
	*/
	void setEmpID(int empID) { this->mEmpID = empID; };
	void setName(string first, string last) { this->mEmployeeName = first + " " + last; }
	void setPreTaxIncome(float pretaxIncome) {
		this->mPreTaxIncome = pretaxIncome;
		calcFedTax();
		calcStateTax();
		calcFICA();
		calcAdjustedIncome();
	};

	int getEmpID() { return this->mEmpID; };
	string getEmployeeName()const { return this->mEmployeeName; }
	float getPreTaxIncome() const { return this->mPreTaxIncome; }
	float getFedTax() const { return this->mFederalTax; }
	float getStateTax() const { return this->mStateTax; }
	float getFICA() const { return this->mFicaWithholding; }
	float getAdjustedIncome() const { return this->mAdjustedEarnings; }

	void calcFedTax() {
		this->mFederalTax = this->getPreTaxIncome() * FED_TAX_RATE;
	}
	void calcStateTax() {
		this->mStateTax = this->getPreTaxIncome() * STATE_TAX_RATE;
	}
	void calcFICA() {
		this->mFicaWithholding = this->getPreTaxIncome() * FICA_RATE;
	}
	void calcAdjustedIncome() {
		float netDeductions = getFedTax() + getStateTax() + getFICA();
		this->mAdjustedEarnings = getPreTaxIncome() - netDeductions;
	}
};

