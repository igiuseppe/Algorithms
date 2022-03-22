#ifndef NEWTEST14_DATA_HPP
#define NEWTEST14_DATA_HPP

#include <string>
#include <memory>
#include "Date.hpp"
#include "Time.hpp"
#include "GenericException.hpp"

using namespace std;

class Data {


public:
    Data() {
        int_val = 0;
        float_val = 0;
        char_val = ' ';
        _empty = false;
    }

    ~Data() {}

    bool _empty;
    string text_val;
    int int_val;
    float float_val;
    char char_val;
    Date date_val;
    Time time_val;

    virtual int size() = 0;

    virtual void _print() = 0;

    virtual bool operator==(const Data &d) = 0;

    virtual bool operator>(const Data &d) = 0;

    virtual bool operator<(const Data &d) = 0;

    virtual bool operator!=(const Data &d) = 0;

    virtual bool operator<=(const Data &d) = 0;

    virtual bool operator>=(const Data &d) = 0;

    virtual const Data &operator++() = 0;

    virtual void operator=(const Data &to_compare) = 0;

    bool notEmpty() {
        return !_empty;
    }

    bool isEmpty() {
        return _empty;
    }

protected:
    virtual bool _isType(string &s) = 0;

    virtual void _control(const bool &error) = 0;

    void _error(string &s) {
        bool b = false;
        try {
            _control(_isType(s));
        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;
        }
        while (b) {
            b = false;
            cin >> s;
            try {
                _control(_isType(s));
            }
            catch (GenericException &e) {
                cout << e.what();
                b = true;

            }
        }
    }

};


#endif //NEWTEST14_DATA_HPP
