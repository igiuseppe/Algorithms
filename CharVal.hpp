#ifndef NUOVA_INTERF_CHARVAL_HPP
#define NUOVA_INTERF_CHARVAL_HPP


#include <iostream>
#include "Data.hpp"

class CharVal : public Data {
public:
    CharVal(const char &a) { char_val = a; }

    CharVal() { char_val = ' '; }

    ~CharVal() = default;
    // CharVal(CharVal && c){char_val=move(c.char_val);};

    CharVal(string &s) {
        _error(s);
        char_val = s[0];
    }

    CharVal(const CharVal &a) { char_val = a.char_val; }


    bool operator<(const Data &d) {
        return char_val < d.char_val;
    }

    bool operator==(const Data &d) {
        return char_val == d.char_val;
    }

    bool operator>(const Data &d) {
        return char_val > d.char_val;
    }

    bool operator!=(const Data &d) {
        return char_val != d.char_val;
    }

    bool operator<=(const Data &d) {
        return char_val <= d.char_val;
    }

    bool operator>=(const Data &d) {
        return char_val >= d.char_val;
    }

    const Data &operator++() {
        cerr << "Errore di tipo.";
        return *this;
    };

    void operator=(const Data &to_compare) {
        char_val = to_compare.char_val;
    };

    int size() {
        return 1;
    }

    void _print() {
        cout << char_val;
    }

private:
    bool _isType(string &s) {
        return (s.size() != 1);
    }

    void _control(const bool &error) {
        if (error) throw (GenericException("Errore di tipo. Digitare un nuovo char:"));
    }


};


#endif //NUOVA_INTERF_CHARVAL_HPP
