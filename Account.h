#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <vector>
#include <sstream>
#include "Customer.h"
#include "Transaction.h"


/**
The Bank has Accounts and an Account belongs to a Customer.
Additionally, there are specialized types of accounts: Checking_Account and Savings_Account.
Checking_Account and Savings_Account have specialized ways of adding interest, and describing itself.

@author: Ed Walker
*/

//Prototypes for the classes defined later in this header file
class Savings_Account;
class Checking_Account;

class Account {
protected:
	Customer *customer;		// The customer who owns this account
	double balance;			// The available balance in this account
	int account_number;		// A unique number identifying this account
	std::vector<Transaction *> transactions;  // The record of transactions that have occured with this account

	/**
	Describe fees associated with the customer who owns this account.
	The fee will depend on the specific type of customer.
	@return string showing checking and overdraft fees
	*/
	std::string get_fees()
	{
		int overdraft, charge;
    
        // Polymorphism: calls the correct virtual methods from the specific customer type
        // Get the overdraft and check charge information from this accounts customer
        overdraft = customer->get_overdraft_penalty();
        charge = customer->get_check_charge();
        
        //Store this information in a string and output it
		std::stringstream ss;
		ss << "Check Charge: " << charge << " Overdraft Fee: " << overdraft;
		return ss.str();
	}

protected:
	/**
	Add interest based on a specified interest rate to account
	@param interest	The interest rate
	*/
	void add_interest(double interest) {
        //Calculate the amount after adding interest
		double amt = balance*interest;
		balance = balance + amt;
        //Define the transaction type
        std::string type = "Add interest";
        //Get the customer's fees
		std::string fees = get_fees();
        //Get the customer's ID number
        int cust_id = customer->get_customer_id();
        
        //Create a Transaction object and assign it to the transaction vector
		Transaction *tran = NULL;
        tran = new Transaction(cust_id,type, amt, fees);
		transactions.push_back(tran);
	}

public:
	/**
	Constructor requires a customer to create an account
	Balance always starts with 0 when account is created.
	*/
	Account(Customer *cust, int id) : customer(cust), account_number(id), balance(0) {}

	/**
	Generic accesser and setter methods for properties customer, balance, and account_number
	*/

	Customer *get_customer() {
		return customer;
	}

	void set_customer(Customer *cust) {
		customer = cust;
	}

	int get_account() {
		return account_number;
	}

	void set_balance(double new_balance) {
		balance = new_balance;
	}

	void set_account(int account_number) {
		this->account_number = account_number;
	}

	double get_balance() {
		return balance;
	}

	/**
	Generic method describing the account information.

	Remember that you will need to indicate if an account is Savings or Checking in 
	an overridden version of to_string() in the derived classes. 

	@return string describing generic information about the account
	*/
    
    //Function prototype that is defined later in the class
    virtual std::string to_string();

	/**
	Deposits amount into account
	@param amt The deposit amount
	*/
	virtual void deposit(double amt) {
        //Calculate the deposit amount
		balance += amt;
        //Get the customer's fees
		std::string fees = get_fees();
        //Define transaction type
        string type = "Deposit";
        //Get customer's ID
        int cust_id = customer->get_customer_id();
        
        //Create a Transaction object and assign it to transaction vector
		Transaction *tran = NULL;
        tran = new Transaction(cust_id,type, amt, fees);
		transactions.push_back(tran);
	}

	/**
	Withdraws amount from account
	@param amt The withdrawal amount
	*/
	virtual void withdraw(double amt) {
        //Calculate the withdrawal amount
		balance -= amt;
        //Get customer's fees
		std::string fees = get_fees();
        //Define transaction type
        string type = "Withdrawal";
        //Get customer's ID
        int cust_id = customer->get_customer_id();
        
        // Create a Transaction object and assign it to tran
		Transaction *tran = NULL;
        tran = new Transaction(cust_id, type, amt, fees);
		transactions.push_back(tran);
	}

	// Savings_Account and Checking_Account implement this
	virtual void add_interest() = 0;

};

//Savings_Account IS-A Account
class Savings_Account: public Account{

public:
    //Constructor for Savings_Account
    Savings_Account(Customer *cust, int id) : Account(cust, id) {};
    //Function to calculate balance after deposit
    void deposit(double amt)
    {
        balance += amt;
    }
    //Function to calculate balance after withdrawal
    void withdraw(double amt)
    {
        balance -= amt;
    }
    //Function to calculate balance after interest
    void add_interest()
    {
        double sav_interest = customer->get_savings_interest();
        double interest = balance * sav_interest;
        balance += interest;
        
    }
    //Define account type in the to_string function
    string to_string(){
        std::stringstream ss;
        
        ss << "Account type: Savings" << std::endl;
        return ss.str();
    }
};

//Checking_Account IS-A Account
class Checking_Account: public Account{
    
public:
    //Constructor for Checking_Account
    Checking_Account(Customer *cust, int id) : Account(cust, id) {};
    //Function to calculate blance after deposit
    void deposit(double amt)
    {
        balance += amt;
    }
    //Function to calculate balance after withdrawal
    void withdraw(double amt)
    {
        balance -= amt;
    }
    //Function to calculate balance after interest
    void add_interest()
    {
        double check_interest = customer->get_check_interest();
        double interest = balance * check_interest;
        balance += interest;
    }
    //Define account type in the to_string function
    string to_string(){
        std::stringstream ss;
        
        ss << "Account type: Checking" << std::endl;
        return ss.str();
    }
};

std::string Account::to_string() {
    std::stringstream ss; // for composing the string that describes this account
    
    //Add information about the customer who owns this account
    
    ss << "  Name: " << customer->get_name() << std::endl;
    ss << "  Customer ID number: " << customer->get_customer_id() << std:: endl;
    ss << "  Address: " << customer->get_address() << std:: endl;
    ss << "  Phone number: " << customer->get_telephone_number() << std:: endl;
    ss << "  Age: " << customer->get_age() << std:: endl;
    ss << "  Customer type: " << customer->get_cust_type() << std:: endl;
    ss << "  Balance: " << balance << std::endl;
    ss << "  Account ID: " << account_number << std::endl;
    ss << "  Savings interest: " << customer->get_savings_interest() << std::endl;
    ss << "  Checking interest: " << customer->get_check_interest() << std::endl;
    ss << "  Check charge: " << customer->get_check_charge() << std::endl;
    ss << "  Overdraft fee: " << customer->get_overdraft_penalty() << std::endl;
    //Returns the correct account type depending on the account 
    if (typeid(Savings_Account) == typeid(*this))
    {
        dynamic_cast<Savings_Account*>(this)->to_string();
    }
    else if(typeid(Checking_Account) == typeid(*this))
    {
        dynamic_cast<Checking_Account*>(this)->to_string();
    }
    return ss.str();
}

#endif
