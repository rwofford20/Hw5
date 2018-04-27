#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>
#include <vector>

using namespace std;

/**
The Bank has Customers.  Each Customer has a name, address, age, and telephone number.
Additionally, there are specialized types of Customers: Adult, Senior, and Student.
Each type of Customer has its own checking and savings interest rates, 
as well as its own checking and overdraft fees.

@author: Ed Walker
*/

class Customer
{
protected:
    string name = "";
    string address = "";
    int age = 0;
    string telephone_number = "";
    int customer_number = 0;
    string cust_type = "";
    
public:
    //Constructor for Csutomer object
    Customer(int customer_id, string cust_name, string customer_type){
    
        name = cust_name;
        customer_number = customer_id;
        cust_type = customer_type;
    }
    
    //Accessor and manipulator functions for variables in Customer class
    int get_customer_id () {return customer_number;}
    string get_name() {return name;}
    string get_cust_type() {return cust_type;}
    string get_address() {return address;}
    string get_telephone_number() {return telephone_number;}
    int get_age() {return age;}
    void set_name(string name_)
    {
        name = name_;
    }
    void set_address(string address_)
    {
        address = address_;
    }
    void set_age(int age_)
    {
        age = age_;
    }
    void set_telephone_number(string telephone_number_)
    {
        telephone_number = telephone_number_;
    }
    void set_cust_type(string cust_type_)
    {
        cust_type = cust_type_;
    }
    void set_customer_id(int customer_number_)
    {
        customer_number = customer_number_; 
    }
    //Virtual functions to get the data from the subclasses
    virtual const double get_overdraft_penalty() = 0;
    virtual const double get_check_charge() = 0;
    virtual const double get_savings_interest() = 0;
    virtual const double get_check_interest() = 0;

};

//Students IS-A Customer
class Student: public Customer{
public:
    //Constructor for Customer object of type Student
    Student(int customer_id, string cust_name, string customer_type): Customer(customer_id, cust_name, customer_type){};
    //Set the values of the interest and fees
    const double SAVINGS_INTEREST = 0.01;
    const double CHECK_INTEREST = 0.05;
    const double CHECK_CHARGE = 1.00;
    const double OVERDRAFT_PENALTY = 25.00;
    //Accessor functions for the interest and fees specific to each subclass
    const double get_overdraft_penalty (){
        return OVERDRAFT_PENALTY;
    }
    const double get_check_charge(){
        return CHECK_CHARGE;
    }
    const double get_savings_interest(){
        return SAVINGS_INTEREST;
    }
    const double get_check_interest(){
        return CHECK_INTEREST;
    }
};

//Senior IS-A Customer
class Senior: public Customer{
public:
    //Constructor for Customer object of type Senior
    Senior(int customer_id, string cust_name, string customer_type): Customer(customer_id, cust_name, customer_type){};
    //Set the values of the interest and fees
    const double SAVINGS_INTEREST = 0.05;
    const double CHECK_INTEREST = 0.01;
    const double CHECK_CHARGE = 2.00;
    const double OVERDRAFT_PENALTY = 25.00;
    //Accessor functions for the interest and fees specific to each subclass
    const double get_overdraft_penalty (){
        return OVERDRAFT_PENALTY;
    }
    const double get_check_charge(){
        return CHECK_CHARGE;
    }
    const double get_savings_interest(){
        return SAVINGS_INTEREST;
    }
    const double get_check_interest(){
        return CHECK_INTEREST;
    }
};

//Adult IS-A Customer
class Adult: public Customer{
public:
    //Constructor for Customer object of type Adult
    Adult(int customer_id, string cust_name, string customer_type): Customer(customer_id, cust_name, customer_type){};
    //Set the values of the interest and fees
    const double SAVINGS_INTEREST = 0.03;
    const double CHECK_INTEREST = 0.03;
    const double CHECK_CHARGE = 1.50;
    const double OVERDRAFT_PENALTY = 35.00;
    //Accessor functions for the interest and fees specific to each subclass
    const double get_overdraft_penalty (){
        return OVERDRAFT_PENALTY;
    }
    const double get_check_charge(){
        return CHECK_CHARGE;
    }
    const double get_savings_interest(){
        return SAVINGS_INTEREST;
    }
    const double get_check_interest(){
        return CHECK_INTEREST;
    }
};

#endif
