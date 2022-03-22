//
// Created by Intilla on 02/07/2020.
//

#ifndef INTERFACCIA_DATABASE_HPP
#define INTERFACCIA_DATABASE_HPP

#include "Tab.hpp"
#include "Functions.hpp"
#include <fstream>
#include "GenericException.hpp"
#include "Abort.hpp"

//tentare di usare meno cicli possibili, ad esempio non usando vettori per prendere dati ma facendolo a uno a uno

map<string, Tab> database;


void nameTab(const string &s) {
    if (database.find(s) != database.end()) {
        throw GenericException("Nome gia' in uso per un'altra tabella. Digitare un altro nome:");
    }
    nameisCommand(s);
}

void isTab(const string &s) {
    if (database.find(s) == database.end()) {
        throw GenericException("Tabella non trovata. Digitare un altro nome:");
    }
}

void errorTabExist(string &name_t) {
    bool b = false;
    try {
        nameTab(name_t);
    }
    catch (GenericException &e) {
        cout << e.what();
        b = true;
    }
    while (b) {
        b = false;
        cin >> name_t;
        abort(name_t);
        try {
            nameTab(name_t);
        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;
        }
    }
}

void errorIsNotTab(string &name_t) {
    bool b = false;
    try {
        isTab(name_t);
    }
    catch (GenericException &e) {
        cout << e.what();
        b = true;
    }
    while (b) {
        b = false;
        cin >> name_t;
        abort(name_t);
        try {
            isTab(name_t);
        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;
        }
    }
}

void errorColExist(const string &name_t, string &s) {
    bool b = false;
    try {
        database[name_t].nameCol(s);
    }
    catch (GenericException &e) {
        cout << e.what();
        b = true;
    }
    while (b) {
        b = false;
        cin >> s;
        abort(s);
        try {
            database[name_t].nameCol(s);
        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;

        }
    }
}

void errorIsAuto(const string &name_t, string &s) {
    bool b = false;
    try {
        if (database[name_t]._m[s].autoInc)
            throw (GenericException("Colonna automatica non puo' essere collegata a tabelle esterne, selezionane un'altra: "));
    }
    catch (GenericException &e) {
        cout << e.what();
        b = true;
    }
    while (b) {
        b = false;
        cin >> s;
        abort(s);
        try {
            database[name_t].isCol(s);
            if (database[name_t]._m[s].autoInc)
                throw (GenericException("Colonna automatica non puo' essere collegata a tabelle esterne, selezionane un'altra: "));

        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;

        }
    }
}

void errorIsNotCol(const string &name_t, string &s) {
    bool b = false;
    try {
        database[name_t].isCol(s);
    }
    catch (GenericException &e) {
        cout << e.what() << "Selezionare una nuova colonna." << endl;
        b = true;
    }
    while (b) {
        b = false;
        cin >> s;
        abort(s);
        try {
            database[name_t].isCol(s);
        }
        catch (GenericException &e) {
            cout << e.what() << "Selezionare una nuova colonna." << endl;
            b = true;

        }
    }
}

void errorTypeLink(const string &name_t, const string &foreign, string &linked_tab, string &linked_col) {
    bool b = false;
    try {
        if (database[name_t]._m[foreign].type() != database[linked_tab]._m[linked_col].type())
            throw (
                    GenericException("Colonna collegata collegata e' di tipo diverso."));
    }
    catch (GenericException &e) {
        cout << e.what();
        b = true;
    }
    while (b) {
        b = false;
        cout << "Nuova tabella:";
        cin >> linked_tab;
        abort(linked_tab);
        errorIsNotTab(linked_tab);
        cout << "Nuova colonna:";
        cin >> linked_col;
        abort(linked_col);
        errorIsNotCol(linked_tab, linked_col);
        try {
            if (database[name_t]._m[foreign].type() != database[linked_tab]._m[linked_col].type())
                throw (
                        GenericException("Colonna collegata è di tipo diverso."));

        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;
        }
    }
}

void errorNameisCmmnd(string &name_t) {
    bool b = false;
    try {
        nameisCommand(name_t);
    }
    catch (GenericException &e) {
        cout << e.what();
        b = true;
    }
    while (b) {
        b = false;
        cin >> name_t;
        abort(name_t);
        try {
            nameTab(name_t);
        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;

        }
    }
}

void errorStrCmpr(string &s, const string &to_compare) {
    bool b = false;
    try {
        // strCmpr(s,to_compare);
        strCmpr(s, to_compare);
    }
    catch (GenericException &e) {
        cout << e.what();
        b = true;
    }
    while (b) {
        b = false;
        cin >> s;
        abort(s);
        try {
            //strCmpr(s,to_compare);
            strCmpr(s, to_compare);
        }
        catch (GenericException &e) {
            cout << e.what();
            b = true;
        }
    }
}

void op(istringstream &in, char &c, vector<string> &v, bool &ciclo, bool &order) {
    string s;
    string val;
    string oper;
    if (c == '=') {
        s = string(1, c);
        //
        v.push_back(s);
        val = get(in, 'A', 'O', ';');
        if (val.back() == ';') {
            ciclo = false;
            order = false;
        } else if (equal(val.back(), 'A')) {
            order = false;
            s = cmmndCtrl(in, "AND");
            errorStrCmpr(s, "AND");
        } else if (equal(val.back(), 'O')) {
            in >> s;
            if (equal(s, "R")) {
                order = false;
                s = "OR";
            } else if (equal(s, "RDER")) {
                order = true;
                ciclo = false;
            } else throw (GrammarException("OR/ORDER"));
        } else(throw (GrammarException()));
        val.pop_back();
        v.push_back(move(val));
        if (ciclo) v.push_back(move(s));
    } else {
        oper = string(1, c);
        //in.get(c);
        in >> c;
        if (isOp(c)) {
            oper.append(string(1, c));
            v.push_back(oper);
            val = get(in, 'A', 'O', ';');
            if (val.back() == ';') {
                order = false;
                ciclo = false;
            } else if (equal(val.back(), 'a')) {
                s = cmmndCtrl(in, "AND");
                errorStrCmpr(s, "AND");
                order = false;
            } else if (equal(val.back(), 'o')) {
                in >> s;
                if (equal(s, "R")) {
                    order = false;
                    s = "OR";
                } else if (equal(s, "rder")) {
                    order = true;
                    ciclo = false;
                } else throw (GrammarException("OR/ORDER"));
            }
            val.pop_back();
            v.push_back(move(val));
            if (ciclo) v.push_back(move(s));
        } else {
            v.push_back(move(oper));
            val = get(in, c, 'A', 'O', ';');
            if (val.back() == ';') {
                ciclo = false;
                order = false;
            } else if (equal(val.back(), 'a')) {
                s = cmmndCtrl(in, "AND");
                errorStrCmpr(s, "AND");
                order = false;
            } else if (equal(val.back(), 'o')) {
                in >> s;
                if (equal(s, "r")) {
                    order = false;
                    s = "OR";
                } else if (equal(s, "rder")) {
                    order = true;
                    ciclo = false;
                } else throw (GrammarException("OR/ORDER"));
            } else throw (GrammarException("WHERE"));
            val.pop_back();
            v.push_back(move(val));
            if (ciclo) v.push_back(move(s));
        }
    }
}

vector<string> where(istringstream &in, bool order = false) {
    vector<string> v;
    char c;
    bool ciclo = true;
    string oper;
    string val;
    string s;
    while (ciclo) {
        in >> c;
        s.clear();
        while (c != '<' && c != '>' && c != '=' && c != ' ') {
            s.append(string(1, c));
            in.get(c);
        }
        if (equal(s, "not")) {
            v.push_back(move(s));
        } else {
            v.push_back(move(s));
            if (isOp(c)) {
                op(in, c, v, ciclo, order);
            } else {
                in >> c;
                if (equal(c, 'b')) {
                    ciclo = false;
                    s = cmmndCtrl(in, "BETWEEN");
                    errorStrCmpr(s, "BETWEEN");
                    v.emplace_back(move(s));
                    /*
                    if(isCommand(in,"BETWEEN")) v.emplace_back("BETWEEN");
                    else throw (MyEx("BETWEEN"));*/

                    val = get(in, 'A');
                    v.push_back(move(val));

                    s = cmmndCtrl(in, "AND");
                    errorStrCmpr(s, "AND");
                    v.emplace_back(move(s));
                    /*
                    if(isCommand(in,"AND")) v.emplace_back("AND");
                    else throw (MyEx("AND"));
                    */
                    if (order) {
                        val = get(in, ';', 'O');
                        if (val.back() == 'O') {
                            s = cmmndCtrl(in, "ORDER");
                            errorStrCmpr(s, "ORDER");
                            order = true;
                            /*
                            if(isCommand(in,"ORDER")) order=true;
                            else throw (MyEx("ORDER"));*/
                        } else order = false;
                        val.pop_back();
                    } else val = get(in, ';');
                    v.push_back(move(val));
                } else op(in, c, v, ciclo, order);
            }
        }
    }
    v.emplace_back(";");
    if (order) v.emplace_back("ORDER");
    return (move(v));
}

vector<int> findIndex(istringstream &in,
                      const string &name_t) { //è true per il comando select cosi poi posso fare un controllo e se è vero fare order
    return database[name_t].findVal(where(in));
}


void create() {
    istringstream in(command());
    bool primary = false;
    string s;
    in >> s;
    errorStrCmpr(s, "TABLE");
    string name_t = str(in, '(');
    errorNameisCmmnd(name_t);
    errorTabExist(name_t);
    database[name_t] = move(Tab(name_t));
    char c;
    s.clear();
    vector<string> v;
    in >> c;
    while (c != ';') {
        while (c != ',' && c != ')') {
            s.append(string(1, c));
            in.get(c);
            if (c == ' ' || c == '\n') {
                if (equal(s, "PRIMARY")) {
                    if (primary) {
                        s = str(in, '(');
                        s = str(in, ')');
                        in >> c;
                        cout << "Colonna primaria gia' selezionata." << endl;
                    } else {
                        s = str(in, '(');
                        errorStrCmpr(s, "KEY");
                        s = str(in, ')');
                        errorIsNotCol(name_t, s);
                        database[name_t].getPrimary(s);
                        in >> c;
                    }
                    primary = true;

                } else if (equal(s, "foreign")) {
                    //FOREIGN KEY (COUNTRY_ID) REFERENCES COUNTRIES (ID)
                    s = str(in, '(');
                    // strCmpr(s,"KEY");
                    errorStrCmpr(s, "KEY");
                    string foreign = str(in, ')');
                    errorIsNotCol(name_t, foreign);
                    errorIsAuto(name_t, foreign);
                    in >> s;
                    errorStrCmpr(s, "REFERENCES");
                    string linked_tab = str(in, '(');
                    errorIsNotTab(linked_tab);
                    string linked_col = str(in, ')');
                    errorIsNotCol(linked_tab, linked_col);
                    errorTypeLink(name_t, foreign, linked_tab, linked_col);
                    database[name_t]._m[foreign].col_ptr = &database[linked_tab]._m[linked_col];
                    database[name_t].foreignKey(foreign, linked_tab);
                    in >> c;
                } else {
                    in >> c;
                    if (!v.empty()) {
                        to_upper(s);
                    }
                    v.push_back(s);
                    s.clear();
                }
            } else if (c == ',' || c == ')') {
                //errorNameisCmmnd(s);
                //errorColExist(name_t,s);
                if (!v.empty()) {
                    to_upper(s);
                }
                v.push_back(s);
                s.clear();
            }

        }
        if (!v.empty()) {
            errorNameisCmmnd(v[0]);
            errorColExist(name_t, v[0]);
            database[name_t].addCol(v);
            database[name_t].size(v[0]);
        }
        v.clear();
        s.clear();
        in >> c;
    }


}

void ins() {
    istringstream in(command());
    //string name;
    char c;
    string s;
    vector<string> col;
    in >> s;
    errorStrCmpr(s, "INTO");
    string name_t = str(in, '(');
    errorIsNotTab(name_t);
    s = str(in, ',', ')');
    while (!equal(s, "VALUES")) {
        if (s.back() == ')') {
            s.pop_back();
            errorIsNotCol(name_t, s);
            col.push_back(move(s));
            //  database[name_t].errorAuto(s);
            //errorcolautoinc
            s = str(in, '(');
        } else {
            s.pop_back();
            errorIsNotCol(name_t, s);

            //errorcolautoinc
            col.push_back(move(s));
            s = str(in, ',', ')');
        }
    }
    for (int i = 0; i < col.size(); i++) {
        if (i != col.size() - 1) s = get(in, ',');
        else s = get(in, ')');
        database[name_t].newEl(col[i], s);
    }
    in >> c;
    cmpr(c, ';');
    database[name_t].errorEmpty(col);
    // database[name_t].errorAuto();
    //database[name_t]._empty(col);


}

void drop() {
    istringstream in(command());
    string s;
    in >> s;
    errorStrCmpr(s, "TABLE");
    s = str(in, ';');
    errorIsNotTab(s);
    database.erase(s);
    cout << "Tabella " << s << " eliminata con successo." << endl;

}

void del() {
    istringstream in(command());
    string s;
    in >> s;
    errorStrCmpr(s, "FROM");
    string name_t;
    in >> name_t;
    errorIsNotTab(name_t);
    in >> s;
    errorStrCmpr(s, "WHERE");
    database[name_t].delRec(findIndex(in, name_t));

}

void trunc() {
    istringstream in(command());
    string s;
    in >> s;
    errorStrCmpr(s, "TABLE");
    string name = str(in, ';');
    errorIsNotTab(name);
    database[name].trunc();
    cout << "Tabella " << name << " svuotata con successo." << endl;


}

void update() {
    istringstream in(command());
    vector<string> col_set;
    vector<string> data_set;
    string name_t;
    in >> name_t;
    errorIsNotTab(name_t);
    string s;
    in >> s;
    errorStrCmpr(s, "SET");
    s = str(in, '=');
    while (!equal(s, "WHERE")) {
        errorIsNotCol(name_t, s);
        //database[name_t].isCol(s);
        col_set.push_back(move(s));
        s = get(in, ',', 'W');
        if (s.back() == 'W') {
            s.pop_back();
            data_set.push_back(move(s));
            // commandCtrl(s,"WHERE");
            s = cmmndCtrl(in, "WHERE");
            errorStrCmpr(s, "WHERE");
        } else {
            s.pop_back();
            data_set.push_back(move(s));
            s = str(in, '=');
        }
    }
    database[name_t].update(col_set, data_set, findIndex(in, name_t));
    col_set.clear();
    data_set.clear();

}

void sel() {
    istringstream in(command());
    vector<string> col;
    string s;
    char c;
    s = str(in, ',', 'F');
    while (!equal(s, "FROM")) {
        if (s.back() == 'F') {
            s.pop_back();
            col.push_back(move(s));
            s = cmmndCtrl(in, "FROM");
            errorStrCmpr(s, "FROM");
        } else {
            s.pop_back();
            col.push_back(move(s));
            s = str(in, ',', 'F');
        }
    }
    string name_t;
    in >> name_t;
    if (name_t.back() == ';') {
        name_t.pop_back();
        errorIsNotTab(name_t);
        database[name_t].print(col);
    } else {
        in >> c;
        if (c == ';') {
            errorIsNotTab(name_t);
            database[name_t].print(col);
        } else if (equal(c, 'W')) {
            in >> s;
            s = string(1, c).append(s);
            errorStrCmpr(s, "WHERE");
            vector<string> v = where(in, true);
            if (v[v.size() - 1] == "ORDER") {
                v.pop_back();
                in >> s;
                errorStrCmpr(s, "BY");
                string col_ord;
                in >> col_ord;
                errorIsNotCol(name_t, col_ord);
                string order = str(in, ';');
                while (!equal(order, "asc") && !equal(order, "desc")) {
                    cout << "Errore nella dichiarazione del comando di ordinamento, riprovare: ";
                    cin >> order;
                }
                to_upper(order);
                database[name_t].print(col_ord, order, col, v);
            } else {
                database[name_t].print(col, v);
            }
            v.clear();
        } else if (equal(c, 'o')) {
            in >> s;
            errorStrCmpr(s, "RDER");
            in >> s;
            errorStrCmpr(s, "BY");
            string col_ord;
            in >> col_ord;
            errorIsNotCol(name_t, col_ord);
            string order = str(in, ';');
            while (!equal(order, "asc") && !equal(order, "desc")) {
                cout << "Errore nella dichiarazione del comando di ordinamento, riprovare: ";
                cin >> order;
            }
            to_upper(order);
            database[name_t].sort(col_ord, order, col);
        }
    }
    col.clear();
}

void getCommand(string &s) {
    if (equal(s, "create")) {
        create();
    } else if (equal(s, "insert")) {
        ins();
    } else if (equal(s, "drop")) {
        drop();
    } else if (equal(s, "delete")) {
        del();
    } else if (equal(s, "truncate")) {
        trunc();
    } else if (equal(s, "update")) {
        update();
    } else if (equal(s, "select")) {
        sel();
    } else {
        throw GrammarException("Comando non riconosciuto");
    }
}

void export_data() {
    ofstream out("Input.txt", ios::out | ios::trunc);
    out << database.size() << endl << endl;
    for (const auto &it:database) {
        out << it.second;
    }
    out.close();
}


void import_data() {
    ifstream in("Input.txt", ios::in);
    int size = 0;
    in >> size;
    for (int i = 0; i < size; i++) {
        string primary;
        string s;
        string name;
        in >> name;
        database[name] = Tab(name);
        in >> s;
        if (s != ";") {
            in >> s;
            primary = s;
            in >> s;
        }
        in >> s;
        string linked_col;
        string linked_tab;
        bool foreign = false;
        vector<string> col;
        while (s != ";") {
            while (s != ",") {
                if (s == "FOREIGN") {
                    foreign = true;
                    in >> linked_tab;
                    in >> linked_col;
                } else {
                    col.push_back(move(s));
                }

                in >> s;
            }
            database[name].addCol(col);
            if (foreign) {
                database[name].foreignKey(col[0], linked_tab);
                database[name]._m[col[0]].col_ptr = &database[linked_tab]._m[linked_col];
            }
            database[name].size(col[0]);
            col.clear();
            foreign = false;
            in >> s;
        }
        linked_tab.clear();
        linked_col.clear();
        for (auto &it:database[name]._m) {
            if (it.second.type() == "TEXT") {
                char c;
                in >> c;
                while (c != ',') {
                    if (c == '"') {
                        s.clear();
                        s.append(string(1, c));
                        c = in.get();

                        while (c != '"') {
                            s.append(string(1, c));
                            c = in.get();
                            if (c == '"' && s.back() == '/') {
                                s.pop_back();
                                s.append(string(1, c));
                                c = in.get();
                            }
                        }
                        s.append(string(1, c));
                        it.second.newEl(s, true);
                        in >> c;
                    } else if (c == '/') {
                        if (in.get() == c) {
                            if (!it.second.notNull) it.second.addEmpty();
                            else cerr << "Campo not null lasciato vuoto.";
                        }
                        in >> c;
                    }
                }
            } else if (it.second.autoInc) {
                in >> s;
                if (s != ",") {
                    it.second.newEl(s, true);
                    in >> s;
                    while (s == "//") {
                        it.second.addAuto();
                        in >> s;
                    }
                }
            } else if (it.second.type() == "CHAR") {
                in >> s;
                while (s != ",") {
                    if (s != "//") {
                        if (s == ",,") {
                            s = " ";
                        } else if (s == ";;") {
                            s = "\n";
                        }
                        it.second.newEl(s, true);
                    } else {
                        if (!it.second.notNull) it.second.addEmpty();
                        else cerr << "Campo not null lasciato vuoto.";
                    }
                    in >> s;
                }
            } else {
                in >> s;
                while (s != ",") {
                    if (s != "//") it.second.newEl(s, true);
                    else {
                        if (!it.second.notNull) it.second.addEmpty();
                        else cerr << "Campo not null lasciato vuoto.";
                    }
                    in >> s;
                }
            }
        }
        if (!primary.empty()) database[name].getPrimary(primary);
    }
    in.close();
}

#endif //INTERFACCIA_DATABASE_HPP
