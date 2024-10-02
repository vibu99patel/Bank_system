// Acc_Class implementation

#ifndef ACC_CLASS_HPP
#define ACC_CLASS_HPP

#include <string>

class Acc_Class {
public:
    std::string name;
    std::string address;
    int acc_num;
    std::string password;
    int total;

    Acc_Class(std::string name, std::string address, int acc_num, std::string password, int total) {
        this->name = name;
        this->address = address;
        this->acc_num = acc_num;
        this->password = password;
        this->total = total;
    }
};

#endif // ACC_CLASS_HPP
