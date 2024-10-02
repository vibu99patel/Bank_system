// This file contains the class definition for the BankSystem class, which manages the bank's accounts and 
// provides various operations such as adding, deleting, modifying, and searching for accounts, as well as 
// depositing, withdrawing, and transferring money between accounts. 
// The BankSystem class also provides a method to print information about a specific account and all accounts in the bank. 

#ifndef BANK_SYSTEM_HPP
#define BANK_SYSTEM_HPP

#include "acc_class.hpp"
#include <unordered_map>
#include <iostream>
#include <string>
#include <list>

class BankSystem {
private:
    std::unordered_map<int, std::list<Acc_Class*>> accounts;

public:
    int add_Account(std::string name, std::string address, std::string password, int total);
    int generateNextAccountNumber();
    void delete_Account(int account_number);
    void modify_Account(int account_number, std::string name, std::string address, std::string password);
    void withdraw(int account_number, int amount);
    void deposit(int account_number, int amount);
    void transfer_money(int from_account_number, int to_account_number, int amount);
    Acc_Class* search(int account_number);
    void print_info(int account_number);
    void print_all();
    ~BankSystem();

private:
    int hash_function(int account_number);
};

#endif // BANK_SYSTEM_HPP
