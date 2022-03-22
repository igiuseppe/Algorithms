#ifndef NUOVA_INTERF_TIME_HPP
#define NUOVA_INTERF_TIME_HPP

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Time {
public:
    Time() {
        _hour = 0;
        _minute = 0;
        _second = 0;
    }

    Time(const Time &to_copy) {
        *this = to_copy;
    }

    Time(const int &h, const int &m = 0, const int &s = 0) {
        _hour = h;
        _minute = m;
        _second = s;
    }

    Time(const string &s) {
        istringstream stream;
        stream.str(s);
        char c;
        int j = 0;
        for (int i = 0; i < s.size(); i++) {
            if (!isalnum(s[i])) j++;
        }
        stream >> _hour;
        _minute = 0;
        _second = 0;
        if (j == 1) {
            stream >> c;
            stream >> _minute;
        } else if (j == 2) {
            stream >> c;
            stream >> _second;
        }
    }

    std::string str() const {
        std::ostringstream stream;

        stream << std::setfill('0') << std::setw(2) << _hour << ":"
               << std::setfill('0') << std::setw(2) << _minute << ":"
               << std::setfill('0') << std::setw(2) << _second;
        return stream.str();
    }

    Time &operator=(const Time &to_assign) {
        _hour = to_assign._hour;
        _minute = to_assign._minute;
        _second = to_assign._second;
        return (*this);
    }

    bool operator==(const Time &to_compare) const {
        return ((_hour == to_compare._hour) &&
                (_minute == to_compare._minute) &&
                (_second == to_compare._second));
    }

    bool operator!=(const Time &to_compare) const {
        return !(*this == to_compare);
    }

    friend std::ostream &operator<<(std::ostream &stream, const Time &d) {
        stream << d.str();
        return stream;
    }

    bool operator<(const Time &to_compare) const {
        if (_hour < to_compare._hour) {
            return true;
        } else if (_hour == to_compare._hour && _minute < to_compare._minute) {
            return true;
        } else if (_hour == to_compare._hour && _minute == to_compare._minute) {
            return _second < to_compare._second;
        } else return false;
    }

    bool operator>(const Time &to_compare) const {
        if (_hour > to_compare._hour) {
            return true;
        } else if (_hour == to_compare._hour && _minute > to_compare._minute) {
            return true;
        } else if (_hour == to_compare._hour && _minute == to_compare._minute) {
            return _second > to_compare._second;
        } else return false;
    }


private:
    int _hour;
    int _minute;
    int _second;
};


#endif //NUOVA_INTERF_TIME_HPP
