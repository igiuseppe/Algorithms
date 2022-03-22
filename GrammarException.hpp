#ifndef PROJECT_GRAMMAREXCEPTION_HPP
#define PROJECT_GRAMMAREXCEPTION_HPP

#include <string>

using namespace std;

class GrammarException : public exception {
private:
    const char *message;
public:
    GrammarException() : message("Errore nella dichiarazione dei comandi.\n") {};

    explicit GrammarException(const char *c) : message(c) {};

    const char *what() const noexcept {
        return message;
    }
};


#endif //PROJECT_GRAMMAREXCEPTION_HPP
