#ifndef NUOVA_INTERF_FUNCTIONS_HPP
#define NUOVA_INTERF_FUNCTIONS_HPP

#include "GenericException.hpp"
#include "GrammarException.hpp"
#include "Abort.hpp"


string command() {
    char c;
    string s;
    do {
        c = getchar();
        if (c == ';' && s.back() == '/') {
            s.pop_back();
            s.append(string(1, c));
            c = getchar();
        }
        s.append(string(1, c));

    } while (c != ';');
    return move(s);
}

bool equal(const string &s1, const string &s2) {
    bool error = false;
    if (s1.size() != s2.size()) error = true;
    else {
        char c1;
        char c2;
        for (int i = 0; i < s1.size(); i++) {
            c1 = toupper(s1[i]);
            c2 = toupper(s2[i]);
            if (c1 != c2) error = true;
        }
    }
    return !error;
}

bool equal(const char &c1, const char &c2) {
    char c3 = toupper(c1);
    char c4 = toupper(c2);
    bool error = c3 != c4;

    return !error;
}

void abort(const string &s) {
    if (equal(s, "QUIT()")) throw (Abort());
}

void strCmpr(string &s, const string &to_compare) {
    if (!equal(s, to_compare)) {
        throw GenericException("Errore nella dichiarazione del comando:" + to_compare + ". Digitarlo di nuovo: ");
    }
}

void cmpr(const char &elem, const char &to_compare) {
    if (elem != to_compare) {
        // cerr<<"Errore di formattazione cmpr"<<endl;
//        throw MyEx("Errore nella dichiarazione del comando",to_compare);
        throw (GrammarException());
    }
}


void cmpr(const char &c, const char &to_compare1, const char &to_compare2) {
    if (!equal(c, to_compare1) && !equal(c, to_compare2)) {
        //cerr<<"Errore di formattazione cmpr"<<endl;
        throw (GrammarException());
    }
}


void cmpr(const char &c, const char &to_compare1, const char &to_compare2, const char &to_compare3) {
    if (!equal(c, to_compare1) && !equal(c, to_compare2) && !equal(c, to_compare3)) {
        //cerr<<"Errore di formattazione cmpr"<<endl;
        throw (GrammarException());
    }
}


//sezione acquisizione stringhe

string str(istringstream &in, const char &a) {
    string s;
    char c;
    in >> c;
    while (!equal(c, a)) {
        s.append(string(1, c));
        in.get(c);
        if (c == ' ') {
            in >> c;
            cmpr(c, a);
        }
    }
    return move(s);


}

void to_upper(string &s) {
    for (char &i : s) {
        i = toupper(i);
    }
}

string str(istringstream &in, const char &a, const char &b) {
    string s;
    char c;
    in >> c;
    while (!equal(c, a) && !equal(c, b)) {
        s.append(string(1, c));
        in.get(c);
        if (c == ' ') {
            in >> c;
            cmpr(c, a, b);
        }
    }
    s.append(string(1, toupper(c)));
    return move(s);
}

string get(istringstream &in, const char &a) {
    string s;
    char c;
    do { in.get(c); }
    while (c == ' ');
    if (c == '"') {
        s.append(string(1, c));
        //
        do {
            in.get(c);
            if (c == '"' && s.back() == '/') {
                s.pop_back();
                s.append(string(1, c));
                in.get(c);
            }
            s.append(string(1, c));
        } while (c != '"');
        // s.pop_back();
        in >> c;
        cmpr(c, a);
    } else if (isdigit(c)) {
        while (!equal(c, a)) {
            s.append(string(1, c));
            in >> c;
        }
    } else {
        if (c == '/') {
            in >> c;
            if (c == '/') {
                s.append(string(1, ' '));
                in >> c;
                cmpr(c, a);
            } else if (c == a) {
                //in>>c;
                s.append(string(1, '/'));
                //in>>c;
                //cmpr(c,a);
            } else {
                s.append(string(1, c));
                in >> c;
                cmpr(c, a);
            }
        } else {
            s.append(string(1, c));
            in >> c;
            cmpr(c, a);
        }
    }
    return move(s);
}

string get(istringstream &in, const char &a, const char &b) {
    string s;
    char c;
    do { in.get(c); }
    while (c == ' ');
    if (c == '"') {
        s.append(string(1, c));
        do {
            in.get(c);
            if (c == '"' && s.back() == '/') {
                s.pop_back();
                s.append(string(1, c));
                in.get(c);
            }
            s.append(string(1, c));
        } while (c != '"');
        //    s.pop_back();
        in >> c;
        cmpr(c, a, b);
    } else if (isdigit(c)) {
        while (!equal(c, a) && !equal(c, b)) {
            s.append(string(1, c));
            in >> c;
        }
    } else {
        if (c == '/') {
            in >> c;
            if (c == '/') {
                s.append(string(1, ' '));
                in >> c;
                cmpr(c, a, b);
            } else if (c == a || c == b) {
                //in>>c;
                s.append(string(1, '/'));
                //in>>c;
                //cmpr(c,a);
            } else {
                s.append(string(1, c));
                in >> c;
                cmpr(c, a, b);
            }
        } else {
            s.append(string(1, c));
            in >> c;
            cmpr(c, a, b);
        }
    }
    s.append(string(1, toupper(c)));
    return move(s);
}


string get(istringstream &in, const char &a, const char &b, const char &d) {
    string s;
    char c;
    do { in.get(c); }
    while (c == ' ');
    if (c == '"') {
        s.append(string(1, c));
        do {
            in.get(c);
            if (c == '"' && s.back() == '/') {
                s.pop_back();
                s.append(string(1, c));
                in.get(c);
            }
            s.append(string(1, c));
        } while (c != '"');
        //  s.pop_back();
        in >> c;
        cmpr(c, a, b, d);
    } else if (isdigit(c)) {
        while (!equal(c, a) && !equal(c, b) && !equal(c, d)) {
            s.append(string(1, c));
            in >> c;
        }
        cmpr(c, a, b, d);
    } else {
        if (c == '/') {
            in >> c;
            if (c == '/') {
                s.append(string(1, ' '));
                in >> c;
                cmpr(c, a, b, d);
            } else if (c == a || c == b || c == d) {
                //in>>c;
                s.append(string(1, '/'));
                //in>>c;
                //cmpr(c,a);
            } else {
                s.append(string(1, c));
                in >> c;
                cmpr(c, a, b, d);
            }
        } else {
            s.append(string(1, c));
            in >> c;
            cmpr(c, a, b, d);
        }
    }
    s.append(string(1, toupper(c)));
    return move(s);
}


string get(istringstream &in, char &c, const char &a, const char &b, const char &d) {
    string s;
    if (c == '"') {
        s.append(string(1, c));
        do {
            in.get(c);
            if (c == '"' && s.back() == '/') {
                s.pop_back();
                s.append(string(1, c));
                in.get(c);
            }
            s.append(string(1, c));
        } while (c != '"');
        // s.pop_back();
        in >> c;
        cmpr(c, a, b, d);
    } else if (isdigit(c)) {
        while (!equal(c, a) && !equal(c, b) && !equal(c, d)) {
            s.append(string(1, c));
            in >> c;
        }
        //cmpr(c,a,b,d);
    } else {
        if (c == '/') {
            in >> c;
            if (c == '/') {
                s.append(string(1, ' '));
                in >> c;
                cmpr(c, a, b, d);
            } else if (c == a || c == b || c == d) {
                //in>>c;
                s.append(string(1, '/'));
                //in>>c;
                //cmpr(c,a);
            } else {
                s.append(string(1, c));
                in >> c;
                cmpr(c, a, b, d);
            }
        } else {
            s.append(string(1, c));
            in >> c;
            cmpr(c, a, b, d);
        }
    }
    s.append(string(1, toupper(c)));
    return move(s);
}

//sezione controllo comandi

bool isCommand(const string &s) {
    return (equal(s, "create") || equal(s, "insert") || equal(s, "drop") || equal(s, "truncate") ||
            equal(s, "delete") || equal(s, "update") || equal(s, "select") || equal(s, "findIndex") ||
            equal(s, "and") ||
            equal(s, "or") || equal(s, "order") || equal(s, "from") || equal(s, "table") || equal(s, "primary") ||
            equal(s, "foreign") || equal(s, "into") || equal(s, "values") || equal(s, "not") || equal(s, "null") ||
            equal(s, "auto_increment"));
}

void nameisCommand(const string &s) {
    if (isCommand(s)) {
        throw (GenericException(
                "Impossibile utilizzare i comandi nei campi di testo di tabelle e colonne. Digitare un altro nome: "));
    }
}

string cmmndCtrl(istringstream &in, const string &s) {
    int i = 0;
    string test;
    char c;
    while (i < s.size() - 1) {
        in.get(c);
        test.append(1, c);
        i++;
    }

    test = string(1, s.front()).append(test);
    return test;
}

bool isOp(const char &c) {
    return (c == '=' || c == '<' || c == '>');
}


#endif //NUOVA_INTERF_FUNCTIONS_HPP
