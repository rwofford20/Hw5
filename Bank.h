#ifndef BANK_H_
#define BANK_H_
#include <vector>
#include <stdexcept>
#include "Account.h"
#include "Customer.h"

/**
The CS273 Bank has Accounts and Customers

@author: Ed Walker
*/
class Bank
{
private:
	std::vector<Account *> accounts; // Bank HAS accounts
	std::vector<Customer *> customers;  // Bank HAS customers
    //Use dynamic/type_id to walk through and figure out who's seniors, students, adults, etc.
	
	// Counters for generating unique account and customer IDs
	int account_id = 0;
	int customer_id = 0;


	/**
	Return a vector of accounts owned by the specified name of the customer.
	Remember a customer can have many accounts.  
	@param name The customer name 
	@return vector of account ids
	*/
    
    //Go through accounts vector instead
	std::vector<int> find_accounts_by_name(std::string name)
	{
		std::vector<int> user_accounts;
        
        //Find all the accounts belonging to a customer name and add it to the vector of account numbers
        for(int j = 0; j < accounts.size(); j++)
        {
            //Create Customer object pointing to the customer's accounts
            Customer *C1 = accounts[j]->get_customer();
            //Create an account object
            Account *A1 = accounts[j];
            
            //Get the customer's account
            int acct_id = A1->get_account();
            
            //Get's the customer's name
            string name_ = C1->get_name();
            
            //If the customer's name matches the input name, add the account to the user_accounts vector
            if(name_ == name)
            {
                user_accounts.push_back(acct_id);
            }
        }
        
		return user_accounts;
	}

	/**
	Find a customer based on his/her name
	@param name The customer name
	@return customer object if found, NULL otherwise
	*/
	Customer *find_customer(std::string name)
	{
		// Find and return the Customer object with the parameter name
        //Loops through the vector of Customer objects
        for(size_t i = 0; i < customers.size(); i++){
            //If input name matches a name in the Customer vector, return that Customer object
            if (customers[i]->get_name() == name)
            {
                return customers[i];
       
            }
        }
        //If no customer with that name is found, return NULL
        return NULL;
	}
    
	/**
	Add a new account to a customer object (irrespective of its specific type: adult, senior, or student)
	@param cust The customer object 
	@param account_type The account type, i.e. "savings" or "checking"
	@return the newly created account object
	*/
	Account * add_account (Customer *cust, std::string account_type)
	{
		Account *acct = NULL;
        //Factory method for creating a Account object (could be a Saving_Account or a Checking_Account).
        for (int i = 0; i < customers.size(); i++)
        {
            //Get customer's name
            string cust_name = cust->get_name();
            //Customer object exists that agrees with the Customer object passed in
            if (customers[i]->get_name() == cust_name)
            {
                //If Customer wants to create a savings account
                if(account_type == "savings")
                {
                    //increment account_id
                    ++account_id;
                    //Create a new Savings_Account object
                    acct = new Savings_Account(cust, account_id);
                }
                //If Customer wants to create a checking account
                else if(account_type == "checking")
                {
                    //increment account_id
                    ++account_id;
                    //Create a ne Checking_Account object
                    acct = new Checking_Account(cust, account_id);
                }
                //Add the new account to the accounts vector
                accounts.push_back(acct);
            }
        }

		return acct;
	}

public:
	/** Constructor
	*/
	Bank() : account_id(1000), customer_id(1000) {}

	/**
	Add account for an existing user
	@param name The customer name
	@param account_type The account type, i.e. "checking" or "savings"
	@return the newly created account object if the customer exist, or NULL otherwise
	*/
	Account* add_account(std::string name, std::string account_type) 
	{
		Customer *cust = find_customer(name);
		if (cust == NULL)
			return NULL;
		return add_account(cust, account_type);
	}

	/** 
	Add account for new user.  This creates a new customer and adds an account to him/her.
	@param name Customer name
	@param address Customer address
	@param telephone Customer telephone number
	@param age Customer age
	@param cust_type Customer type, i.e. "adult", "senior" or "student"
	@param account_type Account type, i.e. "checking" or "savings"
	@return the newly created account object
	*/
	Account* add_account(std::string name, std::string address, std::string telephone, int age,
            std::string cust_type, std::string account_type)
	{
        //Create a new Customer object
		Customer *cust = NULL;
        
		// Depending on the customer type, we want to create an Adult, Senior, or Student object.
        //Set name, address, phone number, age, and customer type for the Customer object
        
        //If customer is type "adult"
        if (cust_type == "adult")
        {
            //Increment the customer ID and assign that value to cust
            ++customer_id;
            //Create new Adult object
            cust = new Adult (customer_id, name, cust_type);
            cust->set_customer_id(customer_id);
        }
        //If customer is type "senior"
        else if (cust_type == "senior")
        {
            //Increment the customer ID and assign that value to cust
            ++customer_id;
            //Create new Senior object
            cust = new Senior (customer_id, name, cust_type);
        }
        //If customer is type "student"
        else if (cust_type == "student")
        {
            //Increment the customer ID and assign that value to cust
            ++customer_id;
            //Create new Student object
            cust = new Student (customer_id, name, cust_type);
        }
        
        cust->set_customer_id(customer_id);
        cust->set_name(name);
        cust->set_address(address);
        cust->set_telephone_number(telephone);
        cust->set_age(age);
        cust->set_cust_type(cust_type);
        
        customers.push_back(cust);
		return add_account(cust, account_type);
	}

	/**
	Make a deposit in an account identified by the account id
	@param acct_number	The account id
	@param amt			The amount to deposit
	*/
	void make_deposit(int acct_number, double amt) 
	{
        //Get the account's number
		Account *acct = get_account(acct_number);
        //If the account exists, deposit the amount
		if (acct) {
            acct->deposit(amt);
		}
        //If the account doesn't exist, inform the user
        else {
            cout << "Sorry, account " << acct_number << " could not be found." << endl;
        }
	}

	/** 
	Make a withdrawal in an account identified by the account id
	@param acct_number	The account id
	@param amt			The amount to withdraw
	*/
	void make_withdrawal(int acct_number, double amt) 
	{
        //Get the account's number
		Account *acct = get_account(acct_number);
        //If the account exists, withdraw the amount
		if (acct) {
            acct->withdraw(amt);
		}
        //If the account doesn't exist, inform the user
        else {
            cout << "Sorry, account " << acct_number << " could not be found." << endl;
        }
	}
 
	/**
	Get the list of account numbers associated with a user, identified by his/her name
	@param name The customer name
	@return vector of account ids
	*/
	std::vector<int> get_account(std::string name) 
	{
		return find_accounts_by_name(name);
	}

	/**
	Get the account object for an account identified by an account id
	@param acct_name The account id
	@return the account object if it exists, NULL otherwise
	*/
	Account *get_account(int acct_number)
	{
		for (size_t i = 0; i < accounts.size(); i++) {
			if (accounts[i]->get_account() == acct_number)
				return accounts[i];
		}
		return NULL;
	}
};

#endif
