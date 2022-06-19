// GroupWork.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Developer     : Jazmin Hayles 2021
// Description   : This project tests inheritance, polymorphism, dynamic-binding, encapsulation, data 
//                   abstraction, persistence through file handling, and defensive programming
//                   using exception handling techniques.
/*cin.clear();//clears error state of stream
cin.ignore();//discard characters remaining in the input buffer
cout << "invalid selection,try again" << endl;*/

#include <iostream>
#include <string>
#include <algorithm>// std::transform
#include <exception>
#include "ServiceProvider.h"
#include "Flow.h"
#include "Digicel.h"
#include "CustomerBase.h"

using namespace std;

int menu();
void Customer();
void serviceprovider();

int main()
{
    std::cout << "Welcome to the Shared Platform" << endl;
    menu();

    cout << "Have a Nice Day!" << endl;
    //ServiceProvider *service;
    //Flow flow;
    //service = &flow;
    
    //service->saveToCustomerFile(); 
    
    //service.createPhoneCredit();
    //service.addCustomer("ABC101", "Hayles", "Jazmin", "46Morningside", 8765061234);//works
    return 0;
}

int menu()
{
    int choice;
    
    //insert loop
    do {
        cout << "M E N U\nChoose one:\n"
            << "1 - Customer\n"
            << "2 - Service Provider\n"
            << "3 - Exit" << endl;
        cin >> choice;

        if (choice == 1)
        {
            Customer();
        }
        else if (choice == 2)
        {
            serviceprovider();
        }
        else {
            cout << "Incorrect Input" <<endl;
        }    
    } while (choice != 3);

    return 0;
     
}

void Customer()
{
    const int max_len = 30;
    string number_request;
    int creditBalance, phoneCardDenom;

    CustomerBase customer;
    ServiceProvider* serviceProvider;
    //serviceProvider = new Flow();
    
    cout << "\nDial number request: " 
         << "\nTo Add Credit Dial: *121*[13-digit-cardnumber]*[telephone-number]#" 
         << "\nTo Check Credit Balance Dial: *120*[telephone-number]#" << endl;
    getline(cin,number_request); //insert error handling here
    
    customer.parseCodeCheckRequest(number_request);
    
    if (customer.getServiceProvider() == "flow") {
        serviceProvider = new Flow();
    }
    else {
        serviceProvider = new Digicel();
    }

    if (number_request == "add"){
        phoneCardDenom = serviceProvider->searchCreditTopUpFile(customer.getPhoneCard()); 
        creditBalance = serviceProvider->searchCustomerFile(customer.getFullTelephone());
        creditBalance = customer.addCredit(creditBalance, phoneCardDenom);

        serviceProvider->updateCreditTopUpFile(customer.getPhoneCard());
        serviceProvider->updateCustomerFile(creditBalance, customer.getFullTelephone());
        cout << "Thank you for the visit Have a great Day" << endl;
    }
    else if(number_request == "check"){
        serviceProvider->searchCustomerFile(customer.getFullTelephone());
    }
}

void serviceprovider(){
    string password, companyName, companyId, companyAddress, parentCompany;
    int result = 0, branchNumber, choice;
    string fname, lname, address, trn;
    long long int number;
    ServiceProvider* service{};
    Flow flow;
    Digicel digi;

    cout << "Do you wish to View Total Number of Customers(1) or Login(2)?" << flush;
    cin >> choice;

    if (choice == 1) {
        service->getTotalCustomers();
        //return 
    }

    cout << "Please enter service provider Name : " << flush;
    cin >> companyName;
    //transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
    cout << "Please enter the password: " << flush;
    cin >> password;

    result = service->checkPassword(password, companyName);

    if (result == 1) {
        service = new Flow;
    }
    else if (result == 0) {
        service = new Digicel;
    }
    //exit login loop

    //menu after successful login
    cout << "\nPlease Enter Company Information\n ";
    cout << "Company Name: " << companyName << endl;
    cout << "Company ID: " << flush;
    cin >> companyId; 
    cout << "\nCompany Adddress *use underscore(_) to separate words*: " << flush;
    cin >> companyAddress;
    
    service->setCompanyAddress(companyAddress);
    service->setCompanyID(companyId);
    service->setCompanyName(companyName);

    if (result == 1) {
        cout << "\nParent Company: " << endl;
        cin >> parentCompany;
        flow.setParentCompanyName(parentCompany);
        //Flow flow(companyId, companyAddress, companyName, parentCompany);
        
    }
    else if (result == 0) {
        cout << "\nBranch Number: " << endl;
        cin >> branchNumber;
        digi.setBranchNumber(branchNumber);
    }
    
    cout << "Select an Option: " << endl;
    cout << "1 - Add Customer\n"  
         << "2 - Create Phone Credit\n" 
         << "3 - Display Company Information\n" 
         << "4-  View all Phone Credit\n" 
         << "5 - View Entire Customer Base" <<endl;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "\nENTER CUSTOMER DETAILS - \n First Name:" << flush;
        cin >> fname;
        cout << "\nLast Name:" << flush;
        cin >> lname;
        cout << "\nCustomer TRN:" << flush;
        cin >> trn;
        cout << "\nAddress:" << flush;
        cin >> address;
        cout << "\nTelephone Number:" << flush;
        cin >> number;
        service->addCustomer(trn, lname, fname, address, number);
        break;
    case 2:
        service->createPhoneCredit();
        break;
    case 3:
        service->displayCompanyInfo();
        break;
    case 4:
        service->viewAllFromCreditTopUpFile();
        break;
    case 5:
        service->viewAllCustomesrFile();
        break;
    default:
        cout << "Incorrect Input" << endl;
        break;
    }

}
 







// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

