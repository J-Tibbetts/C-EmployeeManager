#pragma once
#include<String>
using namespace std;

/*
*	The following class serves as an abstract class to create the
*	basis of both the Hourly_Employee and Salary_Employee classes
*
*	Because income is calculated differently for hourly and salary
*	employees, any functions to calculate pay must be left virtual
*/
class EmpRec
{
private:

	int mEmpID;
	string mFirstName;
	string mLastName;
	string mStreet;
	string mCity;
	string mState;
	string mZip;
	string mPhone;
	float mPayrate;
	float mHours;
	float mYearsEmployed;



public:
	EmpRec() {
		this->mEmpID = 0;
		this->mFirstName = "";
		this->mLastName = "";
		this->mStreet = "";
		this->mCity = "";
		this->mState = "";
		this->mZip = "";
		this->mPhone = "";
		this->mPayrate = 0.0;
		this->mHours = 0.0;
		this->mYearsEmployed = 0.0;
	}

	EmpRec(int empID, string firstName, string lastName, string street, string city, string state, string zip, string phone, float payrate, float hours, float yearsEmployed)
	{
		setEmpID(empID);
		setFirstName(firstName);
		setLastName(lastName);
		setStreet(street);
		setCity(city);
		setState(state);
		setZip(zip);
		setPhone(phone);
		setPayrate(payrate);
		setHours(hours);
		setYearsEmployeed(yearsEmployed);
	};

	EmpRec(const EmpRec& right) {
		setEmpID(right.getEmpID());
		setFirstName(right.getFirstName());
		setLastName(right.getLastName());
		setStreet(right.getStreet());
		setCity(right.getCity());
		setState(right.getState().c_str());
		setZip(right.getZip().c_str());
		setPhone(right.getPhone());
		setHours(right.getHours());
		setPayrate(right.getPayrate());
		setYearsEmployeed(right.getYearsEmployeed());
	}

	//Typical mutator set
	void setEmpID(int empID) {
		this->mEmpID = empID;
	}
	void setFirstName(string firstName)
	{
		this->mFirstName = firstName;
	};
	void setLastName(string lastName)
	{
		this->mLastName = lastName;
	};
	void setStreet(string street)
	{
		this->mStreet = street;
	};
	void setCity(string city)
	{
		this->mCity = city;
	};
	void setState(string state)
	{
		this->mState = state;
	};
	void setZip(string zip)
	{
		this->mZip = zip;
	};
	void setPhone(string phone)
	{
		this->mPhone = phone;
	};
	void setPayrate(float payrate)
	{
		this->mPayrate = payrate;
	};
	void setHours(float hours) {
		this->mHours = hours;
	}
	void setYearsEmployeed(float yearsEmployed)
	{
		this->mYearsEmployed = yearsEmployed;
	};

	//typical accessor set
	int getEmpID() const { return this->mEmpID; };
	string getFirstName() const { return this->mFirstName; };
	string getLastName() const { return this->mLastName; };
	string getStreet() const { return this->mStreet; };
	string getCity() const { return this->mCity; };
	string getState() const { return this->mState; };
	string getZip() const { return this->mZip; };
	string getPhone() const { return this->mPhone; };
	float getPayrate() const { return this->mPayrate; };
	float getHours() const { return this->mHours; };
	float getYearsEmployeed() const { return this->mYearsEmployed; };

	//Will divide the payrate by 52 for salary employees
	//will multiply the payrate by 40 for hourly employees
	//it is the payroll's job to tax the employees, not the employees
	virtual float calcWeeklyEarnings() const { return 0.0; };

	virtual bool isSalary() const  { return true; };
	//Used to sort collections of employees by ID number
	bool operator< (EmpRec right) const
	{
		return this->getEmpID() < right.getEmpID();
	}

	virtual string toString()
	{
		string str = "Employee ID: " + to_string(getEmpID()) + "\n"
			+ "Name: " + getFirstName() + ' ' + getLastName() + '\n'
			+ "Address: \n"
			+ getStreet() + "\n"
			+ getCity() + ", " + getState() + ' ' + getZip() + '\n'
			+ "Phone: " + getPhone() + '\n'
			+ "Years Employed: " + to_string(getYearsEmployeed()) + " years\n"
			+ "Scheduled Weekly Hours: " + to_string(getHours()) + " hours\n"
			+ "Payrate: $" + to_string(getPayrate());
		//Payrate is deliberately put on end of string so subclasses can
		//overload the function, call the parent class' method and just
		//concat on either 'per hour' or 'per year'

		return str;
	};

};