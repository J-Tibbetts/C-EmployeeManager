#include "Employee_Entry_Prompter.h"
#include<iomanip>



//Will edit either first or lastname fields of current mEmployee
//if @lastname==true, will edit last name, else will edit first name
void Emprec_Entry_Prompter::inputName(bool lastName) {
	string target = "name", name;
	if (lastName) {
		target = "last " + target;
		printCurrent(mEmployee->getLastName(), target);
	}
	else {
		target = "first " + target;
		printCurrent(mEmployee->getFirstName(), target);
	}
	string prompt = "Please enter the employee's " + target;

	name = inputStringLength(prompt, MAX_NAME_LEN, false, false, target);
	name = convertCase(name);
	if (lastName)
		mEmployee->setLastName(name);
	else
		mEmployee->setFirstName(name);
};

//Will print street address if not null and allow user to reinput
void Emprec_Entry_Prompter::inputStreet() {
	string prompt = "Please enter the employee's street address [excluding city, ST, ZIP]",
		street;

	printCurrent(mEmployee->getStreet(), "street address");
	street = inputStringLength(prompt, MAX_LINE_LEN, false, false, "street address");
	street = convertCase(street);
	mEmployee->setStreet(street);
}

//will print city if not null and allow user to enter new city
void Emprec_Entry_Prompter::inputCity() {
	printCurrent(mEmployee->getCity(), "city");
	string prompt = "Please enter the the employee's city of residence",
		city;
	city = inputStringLength(prompt, MAX_NAME_LEN, false, false, "city");
	city = convertCase(city);
	mEmployee->setCity(city);
}

//will print state abbreviation if not null and allow user to enter new state
void Emprec_Entry_Prompter::inputState() {
	printCurrent(mEmployee->getState(), "state");
	string prompt = "Please enter the employee's state of residence\n[NOTE: Only 2 letter abbreviations are accepted]",
		state;
	state = inputStringLength(prompt, 2, false, false, "state");
	state = convertCase(state, true);
	mEmployee->setState(state);
}

//Will print zip if not null and allow user to enter new zip
//Will not accept zipcodes under 5 digits
void Emprec_Entry_Prompter::inputZip() {
	printCurrent(mEmployee->getZip(), "zip code");
	string prompt = "Please enter employee's five digit zipCode",
		zip;
	zip = inputStringLength(prompt, 5, true, true, "zip code");
	mEmployee->setZip(zip);
}

//Will print phone number if not null and allow user to enter new number
//Will only accept numeric strings for phone and will format string to (###)###-#### format
//after entry
void Emprec_Entry_Prompter::inputPhone() {
	printCurrent(this->mEmployee->getPhone(), "phone number");
	string prompt = "Please enter employee's 10 digit phone number",
		phone;
	phone = inputStringLength(prompt, 10, true, true, "phone number");
	string formattedPhone = formatPhone(phone);
	mEmployee->setPhone(formattedPhone);
}

//Will request salary status if payrate is set to zero(EmpRec is just initialized)
//Regardless, will allow user to input a payrate for employee. Won't allow negative payrate
void Emprec_Entry_Prompter::inputPayrate() {
	cout << setprecision(2)<<fixed;
	//if they payrate is in its default value, the program
	//will check to see what the desired salary status if for
	//this emprec
	const float MAX_PAYRATE=20000,
		MAX_SALARY=1000000;
	float payrate;
	string prompt, payformat;
	if (this->mEmployee->isSalary())
		payformat = " yearly salary";
	else
		payformat = " hourly rate";
	prompt = "Please enter this employee's " + payformat;

	if (mEmployee->getPayrate() > 0)
		printCurrent("$"+to_string(this->mEmployee->getPayrate()), payformat);
	if (mEmployee->isSalary()) {
		payrate = inputValueIn(prompt, MAX_SALARY, 0.0, payformat);
	}
	else {
		payrate = inputValueIn(prompt, MAX_PAYRATE, 0.0, payformat);
	}
	this->mEmployee->setPayrate(payrate);
}

void Emprec_Entry_Prompter::inputHours() {
	const float FULL_TIME_HOURS = 40;
		cout << setprecision(1) << fixed;
	if (this->mEmployee->isSalary()) {
		this->mEmployee->setHours(FULL_TIME_HOURS);
	}
	else {
		string prompt = "Please enter the number of hours the employee is ";
		prompt += "typically scheduled for each week";

		float hours = inputValueIn(prompt, FULL_TIME_HOURS, 0.0, "scheduled hours");
		this->mEmployee->setHours(hours);
	}
}

void Emprec_Entry_Prompter::inputYearsEmployed() {
	const float MAX_YEARS = 100;
	float yearsEmployeed = -1;
	char input = ' ';
	//Because the default value of yearsEmployeed will always be 0, the to_string
	//function will always print SOMETHING but seeing as new Employees will have 
	//worked for 0.0 years, that is acceptable
	cout << setprecision(1) << fixed;
	printCurrent(to_string(this->mEmployee->getYearsEmployeed()), "years employed");
	string prompt1 = "Would you like to change this value? [y/n]\n",
		prompt2 = "Please enter the number of years employed\n";
	vector<char> options = { 'Y', 'N' };
	input = inputCharIn(prompt1, options);

	if (input == 'Y') {
		yearsEmployeed = inputValueIn(prompt2, MAX_YEARS, 0.0, "years employed");

		mEmployee->setYearsEmployeed(yearsEmployeed);
	}
}

void Emprec_Entry_Prompter::setCurrentEmployee(EmpRec* emprec) {
	if (this->mEmployee != nullptr)
		delete this->mEmployee;
	if (emprec->isSalary())
		this->mEmployee = new Salary_Employee(*emprec);
	else
		this->mEmployee = new Hourly_Employee(*emprec);
}

void Emprec_Entry_Prompter::createNewEmpRec(int empID) {
	inputEmploymentStatus();
	mEmployee->setEmpID(empID);
	inputName(false);
	inputName(true);
	inputStreet();
	inputCity();
	inputState();
	inputZip();
	inputPhone();
	inputPayrate();
	inputHours();
	inputYearsEmployed();
	clearScreen();
	printCurrentEmployee();
	cout << "\nPress enter to return to main menu\n";
	cin.ignore();
	clearScreen();
};

void Emprec_Entry_Prompter::modifyEmpRec() {
	bool editing = true;
	int input;
	string menu = "Please select a field to change from the following:\n";
	menu += "1- First Name\n2- Last Name\n3- Street Address\n4- City\n5- State\n";
	menu += "6- Zip code\n7- Phone number\n8- Payrate\n9- Hours Scheduled\n10- Years Employed\n11- Quit";
	while (editing) {
		clearScreen();
		printCurrentEmployee();
		input = inputValueIn(menu, 11, 0, "desired field");
		switch (input) {
		case 1:
			inputName(false);
			break;
		case 2:
			inputName(true);
			break;
		case 3:
			inputStreet();
			break;
		case 4:
			inputCity();
			break;
		case 5:
			inputState();
			break;
		case 6:
			inputZip();
			break;
		case 7:
			inputPhone();
			break;
		case 8:
			inputPayrate();
			break;
		case 9:
			inputHours();
			break;
		case 10:
			inputYearsEmployed();
			break;
		case 11:
			editing = false;
			break;
		default:
			cout << "ERROR: INVALID ENTRY\n";
		}
	}
}
//First will display current(possibly default) yearsEmployed value and ask user if they'd like
//to modify (for new hires, default value should be appropriate)



//Will allow user to modify salary status to either true (employee is paid yearly salary)
//or false (employee is changed hourly)
void Emprec_Entry_Prompter::inputEmploymentStatus() {
	char status;
	vector<char> inputOptions = { 'S','H' };
	cout << "Generating new employee record\n";
	string prompt = "Please enter either: \n";
	prompt += "'S' if the employee is to be paid a salary\n";
	prompt += "'H' if the employee is to be paid an hourly rate";
	status = inputCharIn(prompt, inputOptions);

	if (status == 'S')
		this->mEmployee = new Salary_Employee;
	else {
		this->mEmployee = new Hourly_Employee();
	}
}





//Will cast the current mEmployee to either an Hourly_Employee or Salary_Employee
//depending on current_emprec_salary_status, then print the class' toString() function
void Emprec_Entry_Prompter::printCurrentEmployee() {
	string payformat;
	if (mEmployee->isSalary())
		payformat = "Yearly Salary: $";
	else
		payformat = "Hourly Rate: $";
	cout<<setprecision(0)<<fixed
		<< "Employee ID: " << this->mEmployee->getEmpID() << "\n"
		<< "Name: " <<this->mEmployee->getFirstName() << ' ' <<this->mEmployee->getLastName() << '\n'
		<< "Address: \n"
		<< this->mEmployee->getStreet() << "\n"
		<< this->mEmployee->getCity() << ", " + this->mEmployee->getState() << ' ' + this->mEmployee->getZip() <<'\n'
		<< "Phone: " << this->mEmployee->getPhone() << '\n'<<setprecision(1)
		<< "Years Employed: " << this->mEmployee->getYearsEmployeed() << " years\n"
		<< "Scheduled Weekly Hours: " << this->mEmployee->getHours() << " hours\n"<<setprecision(2)
		<< payformat << this->mEmployee->getPayrate()<<endl<<endl;
}
//Will generate a paycheck object based upon the current emprec attached to mEmployee
void Emprec_Entry_Prompter::printPaycheck() {
	Paycheck check;
	check.setEmpID(mEmployee->getEmpID());
	check.setName(mEmployee->getFirstName(), mEmployee->getLastName());
	check.setPreTaxIncome(mEmployee->calcWeeklyEarnings());
	cout << "Employee ID: \t" << check.getEmpID() << endl << setprecision(2) << fixed << showpoint
		<< "Name: \t" << check.getEmployeeName() << endl
		<< " PreTax earnings: \t$" << check.getPreTaxIncome() << endl
		<< " -Federal Tax: \t\t$" << check.getFedTax() << endl
		<< " -State Tax: \t\t$" << check.getStateTax() << endl
		<< " -FICA withholding: \t$" << check.getFedTax() << endl
		<< "FINAL AMOUNT:\t\t$" << check.getAdjustedIncome() << endl;
};

//Dynamically creates either an Hourly_Employee or Salary_Employeed
//based decided by the state of current_employee_salary_status.
//Returns ptr to dynamiclly created object to calling program and 
//clears current mEmployee 
EmpRec* Emprec_Entry_Prompter::getCurrentEmployee() {
	EmpRec* temp = nullptr;
	if (mEmployee->isSalary())
		temp=new Salary_Employee(*mEmployee);
	else
		temp=new Hourly_Employee(*mEmployee);
	return temp;
}


//Deletes employee currently attached to mEmployee
void Emprec_Entry_Prompter::clear() {
	delete this->mEmployee;
	this->mEmployee = nullptr;
}