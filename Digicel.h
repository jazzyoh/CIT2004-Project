#ifndef DIGICEL_H_
#define DIGICEL_H_

#include <iostream>
#include <string>
#define MAX 25

using namespace std;

class Digicel: public ServiceProvider
{
private:
	int branchNumber;
	static int totalDigicelCustomers;

public:
	Digicel():ServiceProvider(){
		this->branchNumber = 0;
	}

	void setBranchNumber(int branchNumber){
		this->branchNumber = branchNumber;
	}

	int getBranchNumber(){
		return branchNumber;
	}

	void displayCompanyInfo() {
		//override for child classes
		ServiceProvider::displayCompanyInfo();
		cout << "Branch Number:" << branchNumber << endl;
	}

	//CUSTOMER FILE HANDLING
	bool saveToCustomerFile() {//writing to file from add customer
		ofstream saveToFile("DigicelCustomerFile.txt", ios::out | ios::app);

		if (saveToFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}

		saveToFile << customerbase.getCustID() << "\t" << customerbase.getFirstName() << "\t"
			<< customerbase.getLastName() << "\t" << customerbase.getAddress() << "\t"
			<< customerbase.getFullTelephone() << "\t" << customerbase.getCreditBalance();

		saveToFile.close();
		totalDigicelCustomers += 1;
		return true;

		//needs to be changed to binary and add error handling
	}

	bool viewAllCustomesrFile() {
		string customerID, firstName, lastName, customerAddress, telephone;
		int creditBalance, count = 0;
		ifstream readFromFile("DigicelCustomerFile.txt", ios::in);

		if (readFromFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}

		readFromFile >> customerID >> firstName >> lastName
			>> customerAddress >> telephone >> creditBalance;
		while (!readFromFile.eof()) {
			++count;
			cout << "\nWhile Loop Count # : " << count << endl;
			cout << "Customer Name: " << firstName + " " + lastName << "\n"
				<< "TRN: " << customerID << "\n"
				<< "Address: " << customerAddress << "\n"
				<< "Phone Number: " << telephone << "\n"
				<< "Credit Balance" << creditBalance << endl;
			readFromFile >> customerID >> firstName >> lastName
				>> customerAddress >> telephone >> creditBalance;
		}

		cout << "Total Digicel Customers: " << totalDigicelCustomers << endl;

		readFromFile.close();

		return true;

		//needs to be changed to binary and add error handling
		cout << "Hello Yay" << endl;
	}

	int searchCustomerFile(string searchPhoneNumber) {
		string customerID, firstName, lastName, customerAddress, telephone;
		int creditBalance, count = 0;
		ifstream searchFile("DigicelCustomerFile.txt", ios::in);

		if (searchFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return 0;
			//throw runtime error("");
		}

		searchFile >> customerID >> firstName >> lastName
			>> customerAddress >> telephone >> creditBalance;

		while (!searchFile.eof()) {
			++count;

			if (telephone == searchPhoneNumber) {
				cout << "Customer Name: " << firstName + " " + lastName << "\n"
					<< "TRN: " << customerID << "\n"
					<< "Address: " << customerAddress << "\n"
					<< "Phone Number: " << telephone << "\n"
					<< "Credit Balance" << creditBalance << endl;
				searchFile.close();
				return creditBalance;
			}

			cout << "\nWhile Loop Count # : " << count << endl;

			searchFile >> customerID >> firstName >> lastName
				>> customerAddress >> telephone >> creditBalance;
		}

		searchFile.close();
		return 0;
		//take in if user is adding credit or checking balance
		//return customerbase;
	}

	bool updateCustomerFile(int newCreditBalance, string phoneNumber) {
		//deleting and recreating the file this increases memory use though 
		//hence why I want to switch to binary
		string customerID[MAX] = {}, firstName[MAX] = {}, lastName[MAX] = {},
			customerAddress[MAX] = {}, telephone[MAX] = {}; //array of strings
		int creditBalance[MAX], count = 0, i = 0;
		ifstream updateFile("DigicelCustomerFile.txt", ios::in);

		if (updateFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}

		updateFile >> customerID[i] >> firstName[i] >> lastName[i]
			>> customerAddress[i] >> telephone[i] >> creditBalance[i];
		while (!updateFile.eof()) {
			if (telephone[i] == phoneNumber) {
				creditBalance[i] = newCreditBalance;//update
				cout << "Found and Updating" << endl;
			}

			//cout << "\nWhile Loop Count # : " << count << endl;
			++i; ++count;
			updateFile >> customerID[i] >> firstName[i] >> lastName[i]
				>> customerAddress[i] >> telephone[i] >> creditBalance[i];
		}

		updateFile.close();
		//return false;
		if ((remove("DigicelCustomerFile.txt")) == 0) {
			cout << "Update Process HalfWay ..." << endl;
		}

		ofstream saveupdateToFile("DigicelCustomerFile.txt", ios::out | ios::app);

		if (saveupdateToFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}
		for (i = 0; i < count; i++) {
			saveupdateToFile << customerID[i] << "\t" << firstName[i] << "\t" << lastName[i] << "\t"
				<< customerAddress[i] << "\t" << telephone[i] << "\t" << creditBalance[i] << endl;
		}

		saveupdateToFile.close();
		return true;

		cout << "Hello Yay" << endl;
	}

	//PHONE CARD FILE HANDLING
	bool saveToCreditTopUpFile(string cardnum, int denom, string status) {
		ofstream saveToFile("DigicelPhoneCardFile.txt", ios::out | ios::app);

		if (saveToFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}

		saveToFile << cardnum << "\t" << denom << "\t" << status;

		saveToFile.close();

		//needs to be changed to binary and add error handling
		return true;
	}

	bool viewAllFromCreditTopUpFile() {
		string phonecredit, status;
		int denom, count = 0;
		ifstream readFromFile("DigicelPhoneCardFile.txt", ios::in);

		if (readFromFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}

		readFromFile >> phonecredit >> denom >> status;
		while (!readFromFile.eof()) {
			++count;
			cout << "\nWhile Loop Count # : " << count << endl;
			cout << "Phone Credit: " << phonecredit << "\n"
				<< "Status: " << status << "\n"
				<< "Denomination: " << denom << endl;
			readFromFile >> phonecredit >> status >> denom;
		}

		readFromFile.close();
		return true;

		//needs to be changed to binary and add error handling
		cout << "Hello Yay" << endl;
	}

	int searchCreditTopUpFile(string findPhoneCard) {
		string phoneCard, status;
		int denom, count = 0;
		ifstream searchFile("DigicelPhoneCardFile.txt", ios::in);

		if (searchFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return 0;
			//throw runtime error("");
		}

		searchFile >> phoneCard >> denom >> status;
		while (!searchFile.eof()) {
			++count;

			if (findPhoneCard == phoneCard) {
				cout << "Phone Credit: " << phoneCard << "\n"
					<< "Status: " << status << "\n"
					<< "Denomination: " << denom << endl;
				searchFile.close();
				return denom;
			}

			cout << "\nWhile Loop Count # : " << count << endl;

			searchFile >> phoneCard >> denom >> status;
		}
		
		searchFile.close();
		return 0;
		//return false;
		//take in if user is adding credit or checking balance
		//return customerbase;
		cout << "Hello Yay" << endl;
	}

	bool updateCreditTopUpFile(string card) {
		string phoneCard[MAX] = {}, status[MAX] = {}; //array of strings
		int denom[MAX], count = 0, i = 0;
		ifstream updateFile("DigicelPhoneCardFile.txt", ios::in);

		if (updateFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}

		updateFile >> phoneCard[i] >> denom[i] >> status[i];
		while (!updateFile.eof()) {
			if (phoneCard[i] == card) {
				status[i] = "Used";//update
				cout << "Found and Updating" << endl;
			}
			//cout << "\nWhile Loop Count # : " << count << endl;
			++i; ++count;
			updateFile >> phoneCard[i] >> denom[i] >> status[i];
		}

		updateFile.close();
		//return false;
		if ((remove("DigicelPhoneCardFile.txt")) == 0) {
			cout << "Update Process HalfWay ..." << endl;
		}

		ofstream saveupdateToFile("DigicelPhoneCardFile.txt", ios::out | ios::app);

		if (saveupdateToFile.fail()) {
			cout << "File cannot be accessed!" << endl;
			return false;
			//throw runtime error("");
		}
		for (i = 0; i < count; i++) {
			saveupdateToFile << phoneCard[i] << "\t" << denom[i] << "\t" << status[i];
		}

		saveupdateToFile.close();
		return true;
		//deleting and recreing a new file
		//deleting and recreating the file this increases memory use though
		//hence why I want to switch to binary
		//cout << "Hello Yay" << endl;
	}

};

int Digicel::totalDigicelCustomers = 0;

#endif
