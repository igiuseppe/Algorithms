#ifndef NUOVA_INTERF_DATEVAL_HPP
#define NUOVA_INTERF_DATEVAL_HPP


#include <iostream>
#include "Data.hpp"

class DateVal : public Data {
public:
    DateVal() { date_val = 0; }

    DateVal(const int &a) { date_val = a; }

    DateVal(string &a) {
        _error(a);
        date_val = Date(a);
    }

    ~DateVal() = default;
    //DateVal(DateVal &&){};

    DateVal(const DateVal &a) { date_val = a.date_val; }

    bool operator<(const Data &d) {
        return date_val < d.date_val;
    }

    bool operator==(const Data &d) {
        return date_val == d.date_val;
    }

    bool operator>(const Data &d) {
        return date_val > d.date_val;
    }

    bool operator!=(const Data &d) {
        return date_val != d.date_val;
    }

    bool operator<=(const Data &d) {
        return (date_val < d.date_val) || (date_val == d.date_val);
    }

    bool operator>=(const Data &d) {
        return (date_val > d.date_val) || (date_val == d.date_val);
    }

    Data &operator++() {
        cerr << "Errore di tipo.";
        return *this;
    };

    void operator=(const Data &to_compare) {
        date_val = to_compare.date_val;
    };

    void _print() {
        cout << date_val;
    }

    int size() {
        return 10;
    }


private:
    bool _isType(string &s) {
        bool error = false;
        int i;
        for (i = 0; i < s.size(); i++) {
            if (s[i] == ' ' || s[i] == '\n') {
                s.erase(s.begin() + i);
            }
        }
        bool b = true;
        i = 0;
        int k = 0;
        while (b) {
            if (isdigit(s[i])) {
                while (isdigit(s[i]) && i < s.size() - 1) {
                    i++;
                }
                if (!isdigit(s[i])) k++;
            } else {
                b = false;
                error = true;
            }
            i++;
            if (i == s.size()) {
                b = false;
                if (!isdigit(s[i - 1])) error = true;
            }
            if (k > 2) {
                b = false;
                error = true;
            }
        }
        if (!error) {
            istringstream in(s);
            int x;
            char c;
            in >> x;
            if (x > 31 || x < 1) error = true;
            in >> c;
            in >> x;
            if (x > 12 || x < 1) error = true;
        }
        return error;
    }

    void _control(const bool &error) {
        if (error) {
            throw (GenericException("Errore di tipo. Digitare una nuova data:"));
        }
    }

};


#endif //NUOVA_INTERF_DATEVAL_HPP
