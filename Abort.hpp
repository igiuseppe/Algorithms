#ifndef PROJECT_ABORT_HPP
#define PROJECT_ABORT_HPP


#include <string>

using namespace std;

class Abort : public exception {
private:
    const char *message;
public:
    Abort() : message("Comando annullato, uscita dal programma.\n") {};

    explicit Abort(const char *c) : message(c) {};

    const char *what() const noexcept {
        return message;
    }
};


#endif //PROJECT_ABORT_HPP
