#ifndef TELEPHONE_H_
#define TELEPHONE_H_

#include <iostream>
#include <string>

using namespace std;

class Telephone{
private:
	string areaCode;
	string prefix;
	string serialNumber;
	string fullNumber;

public:
	//constructors
	Telephone(){
		areaCode = "876";
		prefix = "110";
		serialNumber = "1234";
		setfullTeleNumber();
	}

	Telephone(int number) {
		parseTelephoneNumber(number);
	}

	void parseTelephoneNumber(long long int phoneNumber) {
		string phone = to_string(phoneNumber);
		//8765003154
		//error handling needed here to chech parts of telephone
		setAreaCode(phone.substr(0, 3));
		setPrefix(phone.substr(3, 3));
		setSerialNumber(phone.substr(6, 4));
		setfullTeleNumber();
		//cout << "Telephone.h : " << phoneNumber << " --- " << getfullTeleNumber() << endl;
	}

	//mutators
	void setAreaCode(string areaCode){
		this->areaCode = areaCode;
	}

	void setPrefix(string prefix){
		this->prefix = prefix;
	}

	void setSerialNumber(string serialNumber){
		this->serialNumber = serialNumber;
	}

	void setfullTeleNumber() {
		fullNumber = areaCode + prefix + serialNumber;
	}

	//accessors
	string getAreaCode(){
		return this->areaCode;
	}

	string getPrefix(){
		return  this->prefix;
	}

	string getSerialNumber(){
		return this->serialNumber;
	}

	string getfullTeleNumber(){
		fullNumber = areaCode + prefix + serialNumber;
		return fullNumber;
	}

	/* NEEDS TO:
		1. checkprefix = 0, check areacode, checkserialnumber here or in sp or main
		2. ensure/validate user input/error-handling
	*/

};

#endif
