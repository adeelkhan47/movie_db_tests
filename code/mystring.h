#ifndef MYSTRING_H
#define MYSTRING_H

#include <string>
#include <iostream>

class MyString {
private:
    std::string data;

public:
    // Default constructor
    MyString() : data("") {}

    // Constructor with a std::string
    MyString(const std::string& str) : data(str) {}

    // Copy constructor
    MyString(const MyString& other) : data(other.data) {}

    // Assignment operator
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Convert to std::string
    std::string toString() const {
        return data;
    }

    // Overload comparison operator for sorting
    bool operator<(const MyString& other) const {
        return data < other.data;
    }

    // Overload equality operator
    bool operator==(const MyString& other) const {
        return data == other.data;
    }

    // Overload inequality operator
    bool operator!=(const MyString& other) const {
        return data != other.data;
    }

    // Stream output operator
    friend std::ostream& operator<<(std::ostream& os, const MyString& myStr) {
        os << myStr.data;
        return os;
    }

    // Stream input operator
    friend std::istream& operator>>(std::istream& is, MyString& myStr) {
        is >> myStr.data;
        return is;
    }

    // Get the size of the string
    size_t size() const {
        return data.size();
    }
};

#endif
