#include "ConsoleIOValidator.h"

char ConsoleIOValidator::inputCharIn(string inputPrompt, vector<char> inputOptions, string fieldName) {
	char response = ' ';
	bool validResponse = false;
	while (!validResponse) {
		cout<<inputPrompt << endl<<"-"
			<< "Please select from the following: \n";
		for (char c : inputOptions) {
			cout << '\t' << c;
		}
		cout << endl<<">: ";
		cin>>response;
		response = toupper(response);
		for (char c : inputOptions) {
			if (response == toupper(c)) {
				validResponse = true;
				break;
			}
		}
		if (!validResponse) {
			invalidEntryMessage(fieldName, 1, false, true);

		}
	}
	cin.ignore(100, '\n');
	return response;
}

int ConsoleIOValidator::inputValueIn(string inputPrompt, vector<int> inputOptions, string fieldName) {
	int response;
	bool validResponse = false;
	while (!validResponse) {
		cout
			<< inputPrompt << endl<<"-"
			<< "Please select from the following:\n";
		for (int i : inputOptions) {
			cout << '\t' << i;
		}
		cout << endl<<">: ";
		cin >> response;
		for (int i : inputOptions) {
			if (response == i) {
				validResponse = true;
				break;
			}
		}
		if (!validResponse)
			invalidEntryMessage(fieldName, 5, true, false);
	}
	cin.ignore(100, '\n');
	return response;
}

int ConsoleIOValidator::inputValueIn(string inputPrompt, const int MAX_VALUE, const int MIN_VALUE, string fieldName) {
	int response = 0;
	bool validResponse = false;
	while (!validResponse) {
		cout << inputPrompt << endl<<"-"
			<< "Please select a value between " << MIN_VALUE << " and " << MAX_VALUE << endl<<">: ";
		cin >> response;
		if (response <= MAX_VALUE && response >= MIN_VALUE) {
			validResponse = true;
		}
		else {
			cout << "Accepted values for" << fieldName << " must be greater than or equal to " << MIN_VALUE
				<< " and less than " << MAX_VALUE << endl << "Please reinput " << fieldName << ": \n";
		}
	}
	cin.ignore(100, '\n');
	return response;
}

float ConsoleIOValidator::inputValueIn(string inputPrompt, const float MAX_VALUE, const float MIN_VALUE, string fieldName) {
	float response = 0.0;
	bool validResponse = false;
	while (!validResponse) {
		cout << inputPrompt << endl<<"-"
			<< "Please select a value between " << MIN_VALUE << " and " << MAX_VALUE << endl<<">: ";
		cin >> response;
		if (response <= MAX_VALUE && response >= MIN_VALUE) {
			validResponse = true;
		}
		else {
			cout << "Accepted values for" << fieldName << " must be greater than or equal to " << MIN_VALUE
				<< " and less than " << MAX_VALUE << endl << "Please reinput " << fieldName << ": \n";
		}
	}
	cin.ignore(100, '\n');
	return response;
}

//Will print the passed @inputPrompt and allow the user to input a string. If the bool @numeric is set to 'True'
//the function will check that only numbers have been entered. The function will then check that the string is within the
//specified length
string ConsoleIOValidator::inputStringLength(string inputPrompt, const int MAX_LENGTH, bool numeric, bool fixedLen, string fieldName) {
	bool validResponse = false;
	string response;
	while (!validResponse) {
		cout << inputPrompt << endl<<"-"
			<< "[max "<<fieldName<< " length: " << MAX_LENGTH << " characters]\n>: ";
		getline(cin, response);

		if ((!numeric || checkNumericStr(response)) && (!fixedLen&&response.length() <= MAX_LENGTH)||(fixedLen&&response.length()==MAX_LENGTH)) {
			validResponse = true;
		}
		else {
			invalidEntryMessage(fieldName, MAX_LENGTH, numeric, fixedLen);
		}
	}
	return response;
}

string ConsoleIOValidator::formatPhone(string phone) {
	string formattedPhone;
	if (strlen(phone.c_str()) >= 10) {
		formattedPhone = "(" + phone.substr(0, 3) + ")" + phone.substr(3, 3) + "-"
			+ phone.substr(6, 4);
	}
	else if (strlen(phone.c_str()) == 7) {
		formattedPhone = phone.substr(0, 3) + "-" + phone.substr(3);
	}
	else
		formattedPhone = phone;
	return formattedPhone;
}

//Will take a string and reprint the word in Inticase format or all uppercased
string ConsoleIOValidator::convertCase(string word, bool fullUpper) {
	int size = strlen(word.c_str());
	char* cstr = new char[size + 1];
	cstr[0] = toupper(word[0]);
	for (int i = 1; i < size; i++) {
		if (fullUpper||word[i-1]==' ')
			cstr[i] = toupper(word[i]);
		else
			cstr[i] = word[i];
	}
	cstr[size] = '\0';
	string str(cstr);
	delete[] cstr;
	return str;
}

bool ConsoleIOValidator::checkNumericStr(string str) {
	bool numeric = true;
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			numeric = false;
			break;
		}
	}
	return numeric;
}

//This function is called by child classes should a user input incorrect data
void ConsoleIOValidator::invalidEntryMessage(string field, int length, bool numeric, bool fixedLen) {
	string entryRequirements;
	if (fixedLen)
		entryRequirements = " exactly " + length;
	else
		entryRequirements = " no greater than " + length;

	if (numeric)
		entryRequirements += " numeric digits";
	else
		entryRequirements += " characters";

	cout << "--INVALID ENTRY--\n"
		<< field << " only accepts entries " << entryRequirements << "\n"
		<< "Please re-enter " << field << " as " << entryRequirements << endl;
}

//This function can be passed the results of a string accessor and will only output
//if the string contains something
void ConsoleIOValidator::printCurrent(string stringAccessorF, string member) {
	if (stringAccessorF != "")
		cout <<"Current " << member << ": " << stringAccessorF<<endl<<"---\n";
}



void ConsoleIOValidator::clearScreen() {
	cout << "\033[2J\033[1;1H";
}