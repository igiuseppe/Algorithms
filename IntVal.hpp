#ifndef NEWTEST14_INT_HPP
#define NEWTEST14_INT_HPP

#include "Data.hpp"


class IntVal : public Data {
public:
    IntVal() { int_val = 0; }

    IntVal(const int &a) { int_val = a; }

    ~IntVal() = default;

    IntVal(IntVal &&) {};

    IntVal(IntVal const &a) { int_val = a.int_val; }

    IntVal(string &s) {
        _error(s);
        int_val = stoi(s);
    }


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

    int size() {
        return to_string(int_val).size();
    }

    void _print() {
        cout << int_val;
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
            throw (GenericException("Errore di tipo. Digitare un nuovo int:"));
        }
    }
};


#endif //NEWTEST14_INT_HPP
