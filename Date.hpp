#ifndef NUOVA_INTERF_DATE_HPP
#define NUOVA_INTERF_DATE_HPP

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {

public:
    Date() {
        _day = 0;
        _month = 0;
        _year = 0;
    }

    Date(const string &s) {
        istringstream stream;
        stream.str(s);
        char c;
        stream >> _day;
        stream >> c;
        stream >> _month;
        stream >> c;
        stream >> _year;
    }

    Date(const Date &to_copy) {
        *this = to_copy;
    }

    Date(const int &d, const int &m, const int &y) {
        _day = d;
        _month = m;
        _year = y;
    }

    std::string str() const {
        std::ostringstream stream;

        stream << std::setfill('0') << std::setw(2) << _day << "/"
               << std::setfill('0') << std::setw(2) << _month << "/"
               << std::setfill('0') << std::setw(4) << _year;
        return stream.str();
    }

    Date &operator=(const Date &to_assign) {
        _day = to_assign._day;
        _month = to_assign._month;
        _year = to_assign._year;
        return (*this);
    }

    Date &operator=(const int &to_assign) {
        _day = to_assign;
        _month = to_assign;
        _year = to_assign;
        return (*this);
    }

    bool operator==(const Date &to_compare) const {
        return ((_day == to_compare._day) &&
                (_month == to_compare._month) &&
                (_year == to_compare._year));
    }

    bool operator!=(const Date &to_compare) const {
        return !(*this == to_compare);
    }

    Date operator+(const Date &to_add) const {
        Date ret(to_add);
        ret._day += _day;
        ret._month += _month;
        ret._year += _year;
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Date &d) {
        stream << d.str();
        return stream;
    }

    bool operator<(const Date &to_compare) const {
        if (_year < to_compare._year) {
            return true;
        } else if (_year == to_compare._year && _month < to_compare._month) {
            return true;
        } else if (_year == to_compare._year && _month == to_compare._month) {
            return _day < to_compare._day;
        } else return false;
    }

    bool operator>(const Date &to_compare) const {
        if (_year > to_compare._year) {
            return true;
        } else if (_year == to_compare._year && _month > to_compare._month) {
            return true;
        } else if (_year == to_compare._year && _month == to_compare._month) {
            return _day > to_compare._day;
        } else return false;
    }


private:
    int _year;
    int _month;
    int _day;
};


#endif //NUOVA_INTERF_DATE_HPP
