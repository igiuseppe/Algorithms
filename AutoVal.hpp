#ifndef PROJECT_AUTOVAL_HPP
#define PROJECT_AUTOVAL_HPP

#include <iostream>
#include "Data.hpp"

class AutoVal : public Data {
public:
    AutoVal(string &a) {
        _error(a);
        int_val = stoi(a);
    }

    AutoVal() { int_val = 1; }

    ~AutoVal() = default;

    AutoVal(const int &a) { int_val = a; }

    AutoVal(const AutoVal &a) { int_val = a.int_val; }


    bool operator<(const Data &d) {
        return int_val < d.int_val;
    }

    bool operator==(const Data &d) {
        return int_val == d.int_val;
    }

    bool operator>(const Data &d) {
        return int_val > d.int_val;
    }

    bool operator!=(const Data &d) {
        return int_val != d.int_val;
    }

    bool operator<=(const Data &d) {
        return int_val <= d.int_val;
    }

    bool operator>=(const Data &d) {
        return int_val >= d.int_val;
    }

    Data &operator++() {
        int_val++;
        return *this;
    };

    void operator=(const Data &to_compare) {
        int_val = to_compare.int_val;
    };

    void _print() {
        cout << int_val;
    }

    int size() {
        return to_string(int_val).size();
    }

private:
    bool _isType(string &s) {
        bool error = false;
        for (int i = 0; i < s.size(); i++) {
            if (!isdigit(s[i])) error = true;
        }
        return error;
    }

    void _control(const bool &error) {
        if (error) {
            throw (GenericException("Errore di tipo. Digitare un nuovo valore per il campo automatico:"));
        }
    }

};


#endif //PROJECT_AUTOVAL_HPP
