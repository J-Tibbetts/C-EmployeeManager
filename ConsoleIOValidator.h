/*
* This class exists to serve as the base class for specific console
* prompt objects. It has tools for testing user entrys
*/
#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class ConsoleIOValidator
{
public:
	ConsoleIOValidator() {};

	//Print @param inputPrompt then ask user to input a char/int then check to see if the input is among the characters
	//in the vector @param inputOptions
	char inputCharIn(string inputPrompt, vector<char> inputOptions, string fieldName = "prompt");
	int inputValueIn(string inputPrompt, vector<int> inputOptions, string fieldName = "prompt");

	//Both inputValueIn functions take a string @param inputPrompt, @MAX_VALUE for the input size,
	//@MIN_VALUE for the input size and a field name
	int inputValueIn(string inputPrompt, const int MAX_VALUE, const int MIN_VALUE = 0, string fieldName = "prompt");
	float inputValueIn(string inputPrompt, const float MAX_VALUE, const float MIN_VALUE = 0, string fieldName = "prompt");

	//Will print the passed @inputPrompt and allow the user to input a string. If the bool @numeric is set to 'True'
	//the function will check that only numbers have been entered. The function will then check that the string is within the
	//specified length
	string inputStringLength(string inputPrompt, const int MAX_LENGTH, bool numeric = false, bool fixedLength=false, string fieldName = "prompt");
	//Will check each character in @param str to verify its a number. Will return true if all numeric
	bool checkNumericStr(string str);
	//Will take a string and reprint the word in Inticase format or all uppercased
	string convertCase(string word, bool fullUpper = false);


	string formatPhone(string phone);


	//This function is called by child classes should a user input incorrect data
	void invalidEntryMessage(string field, int length, bool numeric = false, bool fixedLen = false);
	//This function can be passed the results of a string accessor and will only output
	//if the string contains something
	void printCurrent(string stringAccessorF, string member);



	//will clear terminal of any print
	void clearScreen();
};
