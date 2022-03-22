#ifndef NUOVA_INTERF_TIMEVAL_HPP
#define NUOVA_INTERF_TIMEVAL_HPP


#include <iostream>
#include "Data.hpp"

class TimeVal : public Data {
public:
    TimeVal() { time_val = 0; }

    ~TimeVal() = default;

    TimeVal(TimeVal &&) {};

    TimeVal(const TimeVal &a) { time_val = a.time_val; }

    TimeVal(string &a) {
        _error(a);
        time_val = Time(a);
    }

    bool operator<(const Data &d) {
        return time_val < d.time_val;
    }

    bool operator==(const Data &d) {
        return time_val == d.time_val;
    }

    bool operator>(const Data &d) {
        return time_val > d.time_val;
    }

    bool operator!=(const Data &d) {
        return time_val != d.time_val;
    }

    bool operator<=(const Data &d) {
        return (time_val < d.time_val) || (time_val == d.time_val);
    }

    bool operator>=(const Data &d) {
        return (time_val > d.time_val) || (time_val == d.time_val);
    }

    Data &operator++() {
        cerr << "Errore di tipo.";
        return *this;
    };

    void operator=(const Data &to_compare) {
        time_val = to_compare.time_val;
    };

    int size() {
        return 8;
    }

    void _print() {
        cout << time_val;
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
            if (x > 23 || x < 0) error = true;
            if (k > 0) {
                in >> c;
                in >> x;
                if (x > 59 || x < 0) error = true;
            }
            if (k > 1) {
                in >> c;
                in >> x;
                if (x > 59 || x < 0) error = true;
            }
        }
        return error;
    }

    void _control(const bool &error) {
        if (error) {
            throw (GenericException("Errore di tipo. Digitare un nuovo orario:"));
        }
    }

};

#endif //NUOVA_INTERF_TIMEVAL_HPP
