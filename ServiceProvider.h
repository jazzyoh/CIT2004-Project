//parent class has a customerbase and is either flow or digicel
//admin section
/*addCustomer, view customer base, phone credit creation, viewphonecredit */

#ifndef SERVICEPROVIDER_H_
#define SERVICEPROVIDER_H_

#include <iostream>
#include <string>
#include <fstream>
#include<random> //for generating random 13 digit number
#include "CustomerBase.h"

using namespace std;

class ServiceProvider{
private:
	const string flowPassword = "TheWayIFlow2021";
	const string digiPassword = "TheBiggerBetterNetwork2021";

protected:
	CustomerBase customerbase;
	//CustomerUser customerUser;
	static int totalCustomers;
	string companyId, companyName, companyAddress;
	string credit;

public:
	//default constructor
	ServiceProvider(){
		companyId = " ";
		companyName = " ";
		companyAddress = " ";
		credit = " ";
		++totalCustomers;
	}
	

	//primary constructor
	ServiceProvider(string companyId, string companyAddress, string companyName){
		this->companyAddress = companyAddress;
		this->companyId = companyId;
		this->companyName = companyName;
	}

	//copy constructor
	ServiceProvider(ServiceProvider& obj) {
		this->companyAddress = obj.getCompanyAddress();
		this->companyId = obj.getCompanyID();
		this->companyName = obj.getCompanyName();
	}

	//CUSTOMER FILE
	virtual bool saveToCustomerFile() = 0;
	virtual bool viewAllCustomesrFile() = 0;
	virtual int searchCustomerFile(string) = 0;
	virtual bool updateCustomerFile(int, string) = 0;

	//CREDIT TOP UP FILE
	virtual bool saveToCreditTopUpFile(string, int, string) = 0;
	virtual bool viewAllFromCreditTopUpFile() = 0;
	virtual int searchCreditTopUpFile(string) = 0;
	virtual bool updateCreditTopUpFile(string) = 0;

	int checkPassword(string password,string companyName){
		if (flowPassword == password && companyName == "flow") {
			return 1;
		}
		else if (digiPassword == password && companyName == "digicel") {
			return 0;
		}
		else {
			cout << "Incorrect Password or Company Name\nCheck Spelling and ensure no spacing\n" << endl;
			return 2; //incorrect password
		}

		return 2;
	}

	//mutators
	void setCompanyID(string companyId){
		this->companyId = companyId;
	}

	void setCompanyAddress(string companyAddress){
		this->companyAddress = companyAddress;
	}

	void setCompanyName(string companyName){
		this->companyName = companyName;
	}

	//accessors
	string getCompanyID(){
		return this->companyId;
	}

	string getCompanyAddress(){
		return this->companyAddress;
	}

	string getCompanyName(){
		return this->companyName;
	}

	int getTotalCustomers() {
		return totalCustomers;
	}

	//
	virtual void displayCompanyInfo(){
		//override for child classes
		cout << "Company ID: " << companyId  
			 << "\nCompany Address: " << companyAddress
			 << "\nCompany Name: " << companyName << endl;
	}

	void addCustomer(string customerTrn, string customerLastName, string customerFirstName,
		string customerAddress, long long int telephoneNumber){
		customerbase.setCustID(customerTrn);
		customerbase.setFirstName(customerFirstName);
		customerbase.setLastName(customerLastName);
		customerbase.setAddress(customerAddress);
		customerbase.setCreditBalance(100);
		customerbase.setTelephone(telephoneNumber);
		customerbase.display();

		if (saveToCustomerFile()) {
			cout << "Successfully Saved to File!" << endl;
			totalCustomers += 1;
			cout << "Total Customers: " << totalCustomers << endl;
		}
		
		//string areacode = customerbase.telephone.getAreaCode(); 
		//write to file method and pass customerbase through
	}

	void createPhoneCredit(){
		random_device rdSeed; //Seed
		default_random_engine generator(rdSeed());//random number generator
		string cardnum;
		int denom;
		string status = "Available";

		//setting the limit
		uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFF);

		cardnum = to_string(distribution(generator));
		//cout << cardnum.length() << endl;

		if (cardnum.length() != 13) {
			if (cardnum.length() > 13) {
				cardnum.erase(12, (cardnum.length() - 13));
				//cout << "erase here" << endl;
			}
			else if (cardnum.length() < 13) {
				do {
					cardnum = to_string(distribution(generator));
					//cout << "loop here" << endl;
				} while (cardnum.length() != 13);

			}
		}

		cout << "The phone credit number is: " << cardnum << endl;

		cout << "What is the denomination of this card?\nPlease enter one: [100, 200, 500, 1000]\n"
			<< flush;
		cin >> denom;
		
		cout<< "\nPhone Card Creation Completed\n Details : "
			<< "\nPhone Card Number: " << cardnum << "\n"
			<< "Denomination: " << denom << "\n"
			<< "Status: " << status << endl;

		if (saveToCreditTopUpFile(cardnum, denom, status)) {
			cout << "Successfully Saved to file" << endl;
		}
		
		/* NEEDS TO:
			1. check file to ensure no phone card matches the newly created one
			2. save to file the newly created phone card
			3. ensure/validate user input/error-handling
		*/
	}

};

int ServiceProvider::totalCustomers = 0;


#endif
