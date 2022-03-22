#ifndef NEWTEST14_TEXT_HPP
#define NEWTEST14_TEXT_HPP

#include "Data.hpp"

class TextVal : public Data {
public:
    TextVal() { text_val = ""; }

    TextVal(string &a) {
        _error(a);
        text_val = a;
    }

    ~TextVal() = default;

    TextVal(TextVal &&) {};

    TextVal(TextVal const &a) { text_val = a.text_val; }

    bool operator<(const Data &d) {
        return text_val < d.text_val;
    }

    bool operator==(const Data &d) {
        return text_val == d.text_val;
    }

    bool operator>(const Data &d) {
        return text_val > d.text_val;
    }

    bool operator!=(const Data &d) {
        return text_val != d.text_val;
    }

    bool operator>=(const Data &d) {
        return text_val >= d.text_val;
    }

    bool operator<=(const Data &d) {
        return text_val <= d.text_val;
    }

    const Data &operator++() {
        cerr << "Errore di tipo.";
        return *this;
    };

    void operator=(const Data &to_compare) {
        text_val = to_compare.text_val;
    };

    void _print() {
        cout << text_val;
    }

    int size() {
        return text_val.size();
    }

private:
    bool _isType(string &s) {
        bool error = false;
        if (s.front() != '"' || s.back() != '"') {
            error = true;
        } else {
            s.pop_back();
            s.erase(s.begin());
        }
        return error;
    }

    void _control(const bool &error) {
        if (error) {
            throw (GenericException("Errore di tipo. Digitare un nuovo text:"));
        }
    }

};


#endif //NEWTEST14_TEXT_HPP
