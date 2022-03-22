#ifndef NUOVA_INTERF_FLOATVAL_HPP
#define NUOVA_INTERF_FLOATVAL_HPP


#include <iostream>
#include "Data.hpp"

class FloatVal : public Data {
public:
    FloatVal() { float_val = 0; }

    FloatVal(const float &a) { float_val = a; }

    ~FloatVal() = default;

    FloatVal(FloatVal &&) {};

    FloatVal(string &s) {
        _error(s);
        float_val = stof(s);
    }

    FloatVal(FloatVal const &a) { float_val = a.float_val; }

    bool operator<(const Data &d) {
        return float_val < d.float_val;
    }

    bool operator==(const Data &d) {
        return float_val == d.float_val;
    }

    bool operator>(const Data &d) {
        return float_val > d.float_val;
    }

    bool operator!=(const Data &d) {
        return float_val != d.float_val;
    }

    bool operator<=(const Data &d) {
        return float_val <= d.float_val;
    }

    bool operator>=(const Data &d) {
        return float_val >= d.float_val;
    }

    const Data &operator++() {
        float_val++;
        return *this;
    };

    void operator=(const Data &to_compare) {
        float_val = to_compare.float_val;
    };

    int size() {
        return to_string(float_val).size();
    }

    void _print() {
        cout << float_val;
    }

private:
    bool _isType(string &s) {
        bool point = false;
        bool error = false;
        for (int i = 0; i < s.size(); i++) {
            if (!isdigit(s[i])) {
                if ((s[i] == ',' || s[i] == '.') && !point) {
                    point = true;
                } else error = true;
            }
        }
        return error;
    }

    void _control(const bool &error) {
        if (error) {
            throw (GenericException("Errore di tipo. Digitare un nuovo float:"));
        }
    }

};


#endif //NUOVA_INTERF_FLOATVAL_HPP
