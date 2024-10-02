// Implementations of the BankSystem class

#include "bank_system.hpp"

int BankSystem::add_Account(std::string name, std::string address, std::string password, int total) {
    // Generate the new account number automatically
    int new_account_number = generateNextAccountNumber();

    // Create a new account object
    Acc_Class* new_account = new Acc_Class(name, address, new_account_number, password, total);
    int key = hash_function(new_account_number);
    // Add the new account to the hashtable
    accounts[key].push_back(new_account);
    return new_account_number;
}

int BankSystem::generateNextAccountNumber() {
    if (accounts.empty()) {
        return 1000; // Starting account number
    } else {
        // Find the maximum account number and increment it by 1 to generate next account number
        int max_account_number = 0;
        for (const auto& pair : accounts) {
            for (const auto& account : pair.second) {
                max_account_number = std::max(max_account_number, account->acc_num);
            }
        }
        return max_account_number + 1;
    }
}

void BankSystem::modify_Account(int account_number, std::string name, std::string address, std::string password) {
    // Search for the account in the hashtable
    int key = hash_function(account_number);
    auto& account_list = accounts[key];
    for (auto& account : account_list) {
        if (account->acc_num == account_number) {
            // Modify account details
            account->name = name;
            account->address = address;
            account->password = password;
            return;
        }
    }
}

void BankSystem::delete_Account(int account_number) {
    int key = hash_function(account_number);
    auto& account_list = accounts[key];
    for (auto it = account_list.begin(); it != account_list.end(); ++it) {
        // Find the account with the given account number and delete it
        if ((*it)->acc_num == account_number) {
            delete *it;
            account_list.erase(it);
            return;
        }
    }
}

void BankSystem::withdraw(int account_number, int amount) {
    int key = hash_function(account_number);
    auto& account_list = accounts[key];
    for (auto& account : account_list) {
        // Find the account with the given account number and withdraw the amount
        if (account->acc_num == account_number) {
            if (account->total >= amount) {
                account->total -= amount;
                std::cout << "Money withdrawn successfully!" << std::endl << std::endl;
                return;
            } else {
                // Insufficient balance
                std::cout << "Insufficient balance!" << std::endl << std::endl;
                return;
            }
        }
    }
}

void BankSystem::deposit(int account_number, int amount) {
    int key = hash_function(account_number);
    auto& account_list = accounts[key];
    for (auto& account : account_list) {
        // Find the account with the given account number and deposit the amount
        if (account->acc_num == account_number) {
            account->total += amount;
            return;
        }
    }
}

void BankSystem::transfer_money(int from_account_number, int to_account_number, int amount) {
    // Check if both accounts exist
    Acc_Class* from_account = search(from_account_number);
    Acc_Class* to_account = search(to_account_number);

    if (from_account && to_account) {
        // Check if the balance of the first account is sufficient
        if (from_account->total >= amount) {
            // Withdraw money from the first account
            withdraw(from_account_number, amount);
            // Deposit money into the second account
            deposit(to_account_number, amount);
            std::cout << "Transfer successful!" << std::endl << std::endl;
        } else {
            // Insufficient balance in the source account
            std::cout << "Insufficient balance in the source account." << std::endl << std::endl;
        }
    } else {
        // The destination account does not exist
        std::cout << "The account you selected does not exist." << std::endl << std::endl;
    }
}


Acc_Class* BankSystem::search(int account_number) {
    int key = hash_function(account_number);
    auto& account_list = accounts[key];
    for (auto& account : account_list) {
        if (account->acc_num == account_number) {
            return account;
        }
    }
    return nullptr;
}

// Customer function to print account information
void BankSystem::print_info(int account_number) {
    int key = hash_function(account_number);
    auto& account_list = accounts[key];
    for (auto& account : account_list) {
        // Find the account with the given account number and print its details
        if (account->acc_num == account_number) {
            std::cout << "Name: " << account->name << std::endl;
            std::cout << "Address: " << account->address << std::endl;
            std::cout << "Account Number: " << account->acc_num << std::endl;
            std::cout << "Password: " << account->password << std::endl;
            std::cout << "Balance: " << account->total << std::endl << std::endl;
            return;
        }
    }
    std::cout << "Account not found!" << std::endl;
}

// Admin function to print all account information
void BankSystem::print_all() {
    for (const auto& pair : accounts) {
        for (auto& account : pair.second) {
            std::cout << "Name: " << account->name << std::endl;
            std::cout << "Address: " << account->address << std::endl;
            std::cout << "Account Number: " << account->acc_num << std::endl;
            std::cout << "Password: " << account->password << std::endl;
            std::cout << "Balance: " << account->total << std::endl << std::endl;
        }
    }
}

// Destructor
BankSystem::~BankSystem() {
    for (auto& pair : accounts) {
        for (auto& account : pair.second) {
            delete account;
        }
    }
    accounts.clear();
}

// Hash function
int BankSystem::hash_function(int account_number) {
    return account_number % 101; // Using a prime number for better distribution
}