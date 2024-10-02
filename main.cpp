//Alessandro Lovadina U68384795
//Joshua Delton U01326281
//Vaibhavi Patel U37850718

// This file contains the main function to run the bank system
// It displays the main menu and calls the appropriate functions based on the user's choice

#include "acc_class.hpp"
#include "bank_system.hpp"
#include <iostream>
#include <string>

// Function to display the customer menu
void customerMenu(BankSystem& bank, int account_number) {
    int choice;
    int amount;
    int to_account_number;
    while(true){
        std::cout << "=== Customer Menu ===" << std::endl;
        std::cout << "1. View Account Information" << std::endl;
        std::cout << "2. Withdraw Money" << std::endl;
        std::cout << "3. Deposit Money" << std::endl;
        std::cout << "4. Transfer Money" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Process the user's choice
        switch (choice) {
            case 1:
                // View account information
                bank.print_info(account_number);
                break;
            case 2:
                // Withdraw money
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                bank.withdraw(account_number, amount);
                break;
            case 3:
                // Deposit money
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                bank.deposit(account_number, amount);
                std::cout << "Money deposited successfully!" << std::endl << std::endl;
                break;
            case 4:
                // Transfer money
                std::cout << "Enter destination account number: ";
                std::cin >> to_account_number;
                std::cout << "Enter amount to transfer: ";
                std::cin >> amount;
                bank.transfer_money(account_number, to_account_number, amount);
                break;
            case 5:
                // Exit
                std::cout << "Exiting..." << std::endl << std::endl;
                return;
            default:
                // Invalid choice
                std::cout << "Invalid choice! Please try again." << std::endl << std::endl;
                break;
        }
    }
}

// Function to display the admin menu
void adminMenu(BankSystem& bank) {
    int choice;
    int account_number;
    std::string name, address;
    std::string password;
    int initial_balance;
    while(true){
        std::cout << "=== Admin Menu ===" << std::endl;
        std::cout << "1. View All Accounts" << std::endl;
        std::cout << "2. Create Account" << std::endl;
        std::cout << "3. Modify Account" << std::endl;
        std::cout << "4. Delete Account" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice) {
            case 1:
                // View all accounts
                std::cout << "=== All Accounts ===" << std::endl;
                bank.print_all();
                break;
            case 2:
                // Create account
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter address: ";
                // Added to make sure the address is read correctly (with spaces)
                std::cin.ignore();
                std::getline(std::cin, address);
                std::cout << "Enter account number: ";
                std::cin >> account_number;
                std::cout << "Enter password: ";
                std::cin >> password;
                std::cout << "Enter initial balance: ";
                std::cin >> initial_balance;
                bank.add_Account(name, address, password, initial_balance);
                std::cout << "Account created successfully!" << std::endl << std::endl;
                break;
            case 3:
                // Modify account
                std::cout << "Enter account number to modify: ";
                std::cin >> account_number;
                if (bank.search(account_number) != nullptr) {
                    // If the account exists, then modify it
                    std::cout << "Enter new name: ";
                    std::cin >> name;
                    std::cout << "Enter new address: ";
                    // Added to make sure the address is read correctly (with spaces)
                    std::cin.ignore();
                    std::getline(std::cin, address);
                    std::cout << "Enter new password: ";
                    std::cin >> password;
                    bank.modify_Account(account_number, name, address, password);
                    std::cout << "Account modified successfully!" << std::endl << std::endl;
                } else {
                    // If the account doesn't exist, then display error message
                    std::cout << "Account does not exist! Unable to modify." << std::endl << std::endl;
                }
                break;
            case 4:
                // Delete account
                std::cout << "Enter account number to delete: ";
                std::cin >> account_number;
                bank.delete_Account(account_number);
                std::cout << "Account deleted successfully!" << std::endl << std::endl;
                break;
            case 5:
                // Exit
                std::cout << "Exiting..." << std::endl << std::endl;
                return;
            default:
                // Invalid choice
                std::cout << "Invalid choice! Please try again." << std::endl << std::endl;
                break;
        }
    }  
}

// Function to authenticate the customer
bool authenticateCustomer(BankSystem& bank, int account_number, std::string password) {
    // Search for the account in the hashtable
    Acc_Class* account = bank.search(account_number);
    if (account != nullptr && account->password == password) {
        return true; // Authentication successful
    }
    return false; // Authentication failed
}

// Function to authenticate the admin
bool authenticateAdmin(int admin_id, std::string password) {
    const int ADMIN_ID = 12345; // Admin ID
    const std::string ADMIN_PASSWORD = "password"; // Admin password
    // Check if the admin ID and password match and return true if they do
    return (admin_id == ADMIN_ID && password == ADMIN_PASSWORD);
}

int main() {
    BankSystem bank;
    //Customer Variables
    int selection;
    int account_number;
    std::string password;
    //Admin Variables
    int admin_id;
    std::string admin_password;
    // New Account variables
    std::string name, address;
    int new_account_number;
    std::string new_password;
    // Main menu
    do{
        std::cout << "=== Bank Home Page ===" << std::endl;
        std::cout << "1. Customer" << std::endl;
        std::cout << "2. Admin" << std::endl;
        std::cout << "3. Create Account" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> selection;

        switch (selection) {
            case 1: {
                // Customer login
                std::cout << "Enter account number: ";
                std::cin >> account_number;
                std::cout << "Enter password: ";
                std::cin >> password;
                std::cout << std::endl;
                // Authenticate the customer
                if (authenticateCustomer(bank, account_number, password)) {
                    customerMenu(bank, account_number);
                } else {
                    std::cout << "Invalid credentials! Exiting..." << std::endl << std::endl;
                }
                break;
            }
            case 2:
                // Admin login
                std::cout << "Enter admin ID: ";
                std::cin >> admin_id;
                std::cout << "Enter password: ";
                std::cin >> admin_password;
                // Authenticate the admin
                if (authenticateAdmin(admin_id, admin_password)) {
                    adminMenu(bank);
                } else {
                    std::cout << "Invalid credentials! Please try again." << std::endl;
                }
                break;
            case 3:
                // Create account
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter address: ";
                // Added to make sure the address is read correctly (with spaces)
                std::cin.ignore();
                std::getline(std::cin, address);
                std::cout << "Enter new password: ";
                std::cin >> new_password;
                new_account_number = bank.add_Account(name, address, new_password, 0); // Create account with initial balance 0
                std::cout << "Account created successfully!" << std::endl << std::endl;
                std::cout << "Your unique account number is: " << new_account_number << "."<< std::endl << std::endl;
                break;
            case 4:
                // Quit
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                // Invalid selection
                std::cout << "Invalid selection! Exiting..." << std::endl;
                break;
        }
    }while(selection != 4);

    return 0;
}
