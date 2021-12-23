#pragma once
#include "EmpRec.h"
class Hourly_Employee :
    public EmpRec
{
private:

public:
    Hourly_Employee() :EmpRec() {
    };

    Hourly_Employee(const EmpRec &right) :EmpRec(right) {
    };

    Hourly_Employee(int empID, string firstName, string lastName, string street, string city, string state, string zip, string phone, float payrate,  float hours, float yearsEmployed) :
        EmpRec(empID, firstName, lastName, street, city, state, zip, phone, payrate, hours, yearsEmployed) {
    };


    bool isSalary() const override { return false; };

    float calcWeeklyEarnings() const override
    {
        return getPayrate() * getHours();
    }

    string toString() override
    {
        return EmpRec::toString() + " per hour";
    }
};