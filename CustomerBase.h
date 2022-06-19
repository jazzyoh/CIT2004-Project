#ifndef CUSTOMERBASE_H_
#define CUSTOMERBASE_H_

#include <iostream>
#include <string>
#include "Telephone.h"

using namespace std;

class CustomerBase
{
private:
	Telephone telephone;
	string firstName;
	string lastName;
	string customerId;
	string address;
	int creditBalance;
	//variables used for the userinterface for users:
	string code, serviceprovider, phoneCard;
	Telephone phone;
public:
	//Constructors
	CustomerBase(){
		firstName = " ";
		lastName = " ";
		customerId = " ";
		address = " ";
		creditBalance = 0;
		
		telephone.setAreaCode(telephone.getAreaCode());
		telephone.setPrefix(telephone.getPrefix());
		telephone.setSerialNumber(telephone.getSerialNumber());
	}

	CustomerBase(string firstName, string lastName, string customerId, string address,
		int creditBalance, Telephone telephone){
		this->firstName = firstName;
		this->lastName = lastName;
		this->customerId = customerId;
		this->address = address;
		this->creditBalance = creditBalance;
		this->telephone = Telephone(telephone);
	}

	//mutators
	void setFirstName(string firstName) {
		this->firstName = firstName;
	}

	void setLastName(string lastName) {
		this->lastName = lastName;
	}
	
	void setCustID(string customerId) {
		this->customerId = customerId;
	}

	void setAddress(string address) {
		this->address = address;
	}

	void setCreditBalance(int creditBalance) {
		this->creditBalance = creditBalance;
	}

	void setTelephone(long long int telephone) {
		this->telephone.parseTelephoneNumber(telephone);
	}

	//accessors
	string getFirstName() {
		return this->firstName;
	}

	string getLastName() {
		return this->lastName;
	}

	string getCustID() {
		return this->customerId;
	}

	string getAddress() {
		return this->address;
	}

	int getCreditBalance() {
		return this->creditBalance;
	}

	Telephone getTelephone() {
		return telephone;
	}

	string getFullTelephone() {
		return telephone.getfullTeleNumber();
	}

	string parseCodeCheckRequest(string code)
	{
		string callcode = code.substr(1, 3);
		//*121*1234567891012*8766011234# 30 char
		//*120*8766011234# 16 char
		if (callcode == "121") {
			phoneCard = code.substr(5, 13);
			phone = std::stoi(code.substr(19, 10));
			Telephone(phone);

			//cout << "Add Credit" << endl;
			//code.substr(20, 10); is telephone number
			if (code.substr(23, 1) == "6") {
				serviceprovider = "flow";
			}
			else if (code.substr(23, 1) == "3") {
				serviceprovider = "digicel";
			}
			this->code = "add";
			//addCredit();
		}
		else if (code.substr(1, 3) == "120") {
			phone = std::stoi(code.substr(5, 10));
			//cout << "Check Balance" << endl;
			if (code.substr(8, 1) == "6") {
				serviceprovider = "flow";
			}
			else if (code.substr(8, 1) == "3") {
				serviceprovider = "digicel";
			}
			this->code = "check";
			//checkCreditBalance();
		}
		return code;
	}

	string getPhoneCard() {
		return phoneCard;
	}

	string getServiceProvider() {
		return serviceprovider;
	}

	int addCredit(int creditBalance, int phoneCardDenom)
	{
		creditBalance += phoneCardDenom;
		cout << "New Credit Balance is: " << creditBalance << endl;
		return creditBalance;
	}

	int checkCreditBalance()
	{
		//think this method is useless
	}

	void display()
	{
		cout << "Customer Successfully Added: \n"
			<< "Name: " << firstName + " " + lastName << "\n"
			<< "TRN: " << customerId << "\n"
			<< "Address: " << address << "\n"
			<< "Phone Number: " << telephone.getfullTeleNumber() << "\n"
			<< "Credit Balance: " << creditBalance << endl;
	}


};

#endif
