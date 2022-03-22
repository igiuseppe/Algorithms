#ifndef PROJECT_GENERICEXCEPTION_HPP
#define PROJECT_GENERICEXCEPTION_HPP

#include <string>
#include <utility>

using namespace std;


class GenericException {
private:
    const string message;
public:
    GenericException() : message("Errore nella dichiarazione dei comandi.\n") {};

    explicit GenericException(string s) : message(move(s) + '\n') {};

    GenericException(const string &s1, const string &s2) : message(s1 + ": " + s2 + '\n') {};

    GenericException(const string &s1, const char &s2) : message(s1 + ": " + s2 + '\n') {};

    string what() { return message; }
};


#endif //PROJECT_GENERICEXCEPTION_HPP
