#ifndef NUOVA_INTERF_EMPTY_HPP
#define NUOVA_INTERF_EMPTY_HPP


#include <iostream>
#include "Data.hpp"


class Empty : public Data {

public:
    Empty() { _empty = true; }

    ~Empty() = default;

    bool operator<(const Data &d) {
        cerr << "Campo vuoto.";
        return _empty;
    }

    bool operator==(const Data &d) {
        return _empty == d._empty;
    }

    bool operator>(const Data &d) {
        cerr << "Campo vuoto.";
        return _empty;
    }

    bool operator!=(const Data &d) {
        return !_empty == d._empty;

    }

    bool operator<=(const Data &d) {
        cerr << "Campo vuoto.";
        return _empty;
    }

    bool operator>=(const Data &d) {
        cerr << "Campo vuoto.";
        return _empty;
    }

    Data &operator++() {
        cerr << "Campo vuoto.";
        return *this;
    };

    void operator=(const Data &to_compare) {
        _empty = to_compare._empty;
        /*_empty= false;
        int_val=to_compare.int_val;
        text_val=to_compare.text_val;
        float_val=to_compare.float_val;
        char_val=to_compare.char_val;
        date_val=to_compare.date_val;
        time_val=to_compare.time_val;*/

    };

    int size() {
        return 2;
    }

    void _print() {

       cout << "//";

    }

private:
    bool _isType(string &s) { return true; }

    void _control(const bool &error) {}

};

#endif //NUOVA_INTERF_EMPTY_HPP
