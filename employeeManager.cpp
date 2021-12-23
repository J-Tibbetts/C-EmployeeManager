#include "employeeManager.h"

void EmployeeManager::eraseEmployee(int empID) {
	int desiredIndex = 0;
	for (auto it = mEmployees.begin(); it < mEmployees.end(); it++) {
		if ((*it)->getEmpID() == empID) {
			delete *it;
			mEmployees.erase(it);
			break;
		}
	}
}
int EmployeeManager::assignID() {
	int id_number = this->nextID;
	nextID++;
	return id_number;
}
void EmployeeManager::sort() {
	if (!mEmployees.empty()) {
		std::sort(mEmployees.begin(), mEmployees.end());
	}
}

void EmployeeManager::start() {
	string menu = "Please select from the following options\n";
	menu += "1: Add Employee Record\n2: Update Existing Employee Record\n";
	menu += "3: Delete Employee Record\n4: View Current Employee Records\n";
	menu += "5: Print Payroll Report\n6: Quit\n";
	int option = 0;
	while (option != 6) {
		option = mAssistant.inputValueIn(menu, 6, 1, "action menu");
		mAssistant.clearScreen();
		switch (option) {
		case 1:
			addEmployeeRecord();
			break;
		case 2:
			updateEmployeeRecord();
			break;
		case 3:
			deleteEmployeeRecord();
			break;
		case 4:
			printAllEmployees();
			break;
		case 5:
			printPayrollReport();
			break;
		case 6:
			cout << "Goodbye!";
			break;
		default:
			cout << "Something went wrong\n";
		}
	}
}

void EmployeeManager::addEmployeeRecord() {
	mAssistant.createNewEmpRec(this->assignID());
	mEmployees.push_back(mAssistant.getCurrentEmployee());
	mAssistant.clear();
	sort();
}
void EmployeeManager::updateEmployeeRecord() {

	if (!mEmployees.empty()) {
		string prompt1 = "Please enter the ID number to select the employee you wish to modify",
			prompt2 = "Would you like to keep these changes?[Y/N]";
		vector<char> yesNo = { 'Y','N' };
		char save;

		int id = mAssistant.inputValueIn(prompt1, getAllEmpID(), "desired employee #");
		mAssistant.setCurrentEmployee(getEmployee(id));
		mAssistant.modifyEmpRec();
		save = mAssistant.inputCharIn(prompt2, yesNo, "save changes");
		mAssistant.clearScreen();
		if (save == 'Y') {
			eraseEmployee(id);
			mEmployees.push_back(mAssistant.getCurrentEmployee());
			sort();
		}
		else
			cout << "Changes were not saved\n";
			mAssistant.clear();
	}
	else {
		cout << "There are currently no employees on record\n\n";
	}
}
void EmployeeManager::deleteEmployeeRecord() {
	if (!mEmployees.empty()) {
		printAllEmployees();
		string prompt1 = "Please enter the ID number to select the employee you wish to delete",
			prompt2 = "Are you sure you want to delete this employee? [Y/N]";
		vector<char> options = { 'Y','N' };
		char selection;
		int id = mAssistant.inputValueIn(prompt1, getAllEmpID(), "ID of desired employee");
		mAssistant.setCurrentEmployee(getEmployee(id));
		cout << "\n";
		mAssistant.printCurrentEmployee();
		selection = mAssistant.inputCharIn(prompt2, options, "whether to delete");
		if (selection == 'Y') {
			eraseEmployee(id);
			sort();
			mAssistant.clear();
			mAssistant.clearScreen();
			cout << "\nEmployee record deleted\n";
		}
		else {
			cout << "\nEmployee record left alone\n";
		}
	}
	else {
		cout << "There are currently no employees on record\n\n";
	}
}

EmpRec* EmployeeManager::getEmployee(int empID) {
	int desiredIndex = 0;
	for (int i = 0; i < mEmployees.size(); i++) {
		if (mEmployees.at(i)->getEmpID() == empID) {
			desiredIndex = i;
		}
	}
	return mEmployees.at(desiredIndex);
}
vector<EmpRec* > EmployeeManager::getAllEmployees() const {
	return this->mEmployees;
}
vector<int> EmployeeManager::getAllEmpID() {
	vector<int> empIDSet;
	for (auto it = mEmployees.begin(); it < mEmployees.end(); it++) {
		empIDSet.push_back((*it)->getEmpID());
	}
	return empIDSet;
}


void EmployeeManager::printAllEmployees() {
	if (!mEmployees.empty()) {
		for (auto it = mEmployees.begin(); it < mEmployees.end(); it++) {
			mAssistant.setCurrentEmployee(*it);
			mAssistant.printCurrentEmployee();
			mAssistant.clear();
		}
	}
	else {
		cout << "There are currently no employees on record\n";
	}
}
void EmployeeManager::printPayrollReport() {
	if (!mEmployees.empty()) {
		for (int i = 0; i < mEmployees.size(); i++) {
			mAssistant.setCurrentEmployee(mEmployees.at(i));
			mAssistant.printPaycheck();
			cout << "\n----\n";
		}
	}
	else {
		cout << "There are currently no employees on record\n";
	}
}