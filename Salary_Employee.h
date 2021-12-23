#pragma once
#include "EmpRec.h"
using namespace std;

class Salary_Employee :
    public EmpRec
{
private:
    //Inherients all class variables
    //from EmpRec

public:
    Salary_Employee() :EmpRec() {};

    Salary_Employee(int empID, string firstName, string lastName, string street, string city, string state, string zip, string phone, float payrate, float hours, float yearsEmployed) :
        EmpRec(empID, firstName, lastName, street, city, state, zip, phone, payrate, hours, yearsEmployed) {};

    Salary_Employee(const EmpRec& right) :
        EmpRec(right) {};

    bool isSalary() const override { return true; };


    float calcWeeklyEarnings() const override
    {
        return getPayrate() / 52;
    };

    string toString() override
    {
        return EmpRec::toString() + " per year";
    };

};