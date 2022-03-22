#ifndef NEWTEST14_TAB_HPP
#define NEWTEST14_TAB_HPP

#include "Col.hpp"
#include <map>
#include "Functions.hpp"
using namespace std;

class Tab {
private:
    string _name;
    string _primary;

public:

    Tab() {};

    Tab(Tab &&t) {
        _name = move(t._name);
        _primary = move(t._primary);
        _m = move(t._m);
    }

    Tab(const string &name, const string &primary = "") {
        _name = name;
        _primary = primary;
        cout << "Tabella " << name << " creata con successo." << endl;
    };

    ~Tab() { _m.clear(); };

    map<string, Col> _m;

    Tab &operator=(const Tab &to_be_assigned) {
        _name = to_be_assigned._name;
        _primary = to_be_assigned._primary;
        _m = to_be_assigned._m;
        return (*this);
    }

    Tab &operator=(Tab &&to_be_assigned) noexcept {
        _name = move(to_be_assigned._name);
        _primary = move(to_be_assigned._primary);
        _m = move(to_be_assigned._m);
        return (*this);
    }

    void trunc() {
        _m.clear();
        _name.clear();
        _primary.clear();
    }

    void isCol(const string &s) {
        if (_m.find(s) == _m.end()) {
            throw GenericException("Colonna non trovata.", s);
        }

    }

    void getPrimary(const string &s) {
        if (!s.empty()) {
            _primary = s;
            _m[s].primary = true;
            cout << "Colonna primaria impostata:" << s << endl;
        }
    }

    void foreignKey(string &col, const string &tab) {
        _m[col].foreign = true;
        _m[col].linked_tab = tab;
        cout << "Collegamento esterno della colonna " << col << " effettuato." << endl;
    }

    void update(const vector<string> &col_to_set, vector<string> &new_val, const vector<int> &index) {
        //vector <int> index=move(findVal(v));
        for (int i = 0; i < col_to_set.size(); i++) {
            _m[col_to_set[i]].update(new_val[i], index);
        }
        //  index.clear();
    }

    void errorIsNotCol(string &s) {
        bool b = false;
        try {
            isCol(s);
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
                isCol(s);
            }
            catch (GenericException &e) {
                cout << e.what() << "Selezionare una nuova colonna." << endl;
                b = true;

            }
        }
    }


    vector<int> findVal(const vector<string> &v) {
        bool b = true;
        vector<vector<int>> ind;
        string col;
        string op;
        string val;
        vector<string> key;
        int i = 0;
        while (b) {
            if (equal(v[i], "not")) {
                key.push_back(v[i]);
                i++;
                col = v[i];
                errorIsNotCol(col);
            } else {
                //  isCol(v[i]);
                col = v[i];
                errorIsNotCol(col);
            }
            i++;
            op = v[i];
            if (equal(op, "between")) {
                b = false;
                i++;
                val = v[i];
                i++;
                i++;
                string val2 = v[i];
                ind.push_back(_m[col].getIndex(op, val, val2));
                if (!key.empty() && equal(v[0], "not")) notVec(ind[0]);
            } else {
                i++;
                val = v[i];
                i++;
                if (v[i] == ";") {
                    b = false;
                } else {
                    key.push_back(v[i]);
                }
                ind.push_back(_m[col].getIndex(val, op));
            }
            i++;
        }
        if (ind.size() > 1) {
            for (i = 0; i < key.size(); i++) {
                if (equal(key[i], "not")) {
                    notVec(ind[i]);
                    // key.erase(key.begin()+i);
                }
            }
            for (i = 0; i < key.size(); i++) {
                if (equal(key[i], "and")) {
                    andVec(ind[i], ind[i + 1]);
                    // key.erase(key.begin()+i);
                    ind.erase(ind.begin() + i + 1);
                }
            }

            for (i = 0; i < key.size(); i++) {
                if (equal(key[i], "or")) {
                    orVec(ind[i], ind[i + 1]);
                    //  key.erase(key.begin()+i);
                    ind.erase(ind.begin() + i + 1);
                }
            }
        }
        if (ind[0].empty()) cout << "Nessun elemento rispetta le condizioni richieste." << endl;
        return move(ind[0]);
    }

    void andVec(vector<int> &v1, const vector<int> &v2) {
        vector<int> v;
        if (v1.size() > v2.size()) {
            for (int i = 0; i < v2.size(); i++) {
                if (find(v1.begin(), v1.end(), v2[i]) != v1.end()) v.push_back(v2[i]);
            }
        } else {
            for (int i = 0; i < v1.size(); i++) {
                if (find(v2.begin(), v2.end(), v1[i]) != v2.end()) v.push_back(v1[i]);
            }
        }
        v1 = move(v);
        ::sort(v1.begin(), v1.end());
    }

    void orVec(vector<int> &v1, const vector<int> &v2) {
        for (int i = 0; i < v2.size(); i++) {
            if (find(v1.begin(), v1.end(), v2[i]) == v1.end()) v1.push_back(v2[i]);
        }
        //sort
        ::sort(v1.begin(), v1.end());
    }

    void notVec(vector<int> &v) {
        map<string, Col>::iterator it = _m.begin();
        int size = it->second._v.size();
        vector<int> ind;
        for (int i = 0; i < size; i++) {
            if (find(v.begin(), v.end(), i) == v.end()) {
                ind.push_back(i);
            }
        }
        v = move(ind);
    }

    void addCol(const string &name, const string &type) {
        nameCol(name);
        _m[name] = move(Col(name, type));
        cout << "Colonna " << name << " inserita con successo nella tabella." << endl;
    }

    void size(const string &col) {
        _m[col].size();
    }

    void addCol(const vector<string> &v) {
        nameCol(v[0]);
        addCol(v[0], v[1]);
        if (find(v.begin(), v.end(), "NOT") != v.end() && find(v.begin(), v.end(), "NULL") != v.end()) {
            _m[v[0]].notNull = true;
        }
        if (find(v.begin(), v.end(), "AUTO_INCREMENT") != v.end()) {
            if (_m[v[0]].type() == "INT") _m[v[0]].autoInc = true;
            else cout << "Colonna di tipo non intero non può essere automatica." << endl;
        }
    }

    void nameCol(const string &s) {
        if (_m.find(s) != _m.end()) {
            // cerr<<"Nome gia' in uso per un'altra colonna.";
            throw GenericException("Nome gia' in uso per un'altra colonna.\n");
        }

    }

    void errorEmpty(const vector<string> &v) {
        for (auto &it:_m) {
            if (find(v.begin(), v.end(), it.first) == v.end()) {
                if ((!it.second.autoInc && it.second.notNull) ||
                    (it.second.autoInc && it.second.notNull && it.second._v.empty())) {
                    cout << "Campo not null lasciato vuoto " << it.first << endl;
                }
            }
        }
        for (auto &it:_m) {
            if (find(v.begin(), v.end(), it.first) == v.end()) {

                if (!it.second.notNull && !it.second.autoInc) {
                    it.second.addEmpty();
                } else if (!it.second.notNull && it.second.autoInc) {
                    it.second.addAuto();
                } else if (it.second.notNull && it.second.autoInc && !it.second._v.empty()) {
                    it.second.addAuto();
                }
            }
        }
        for (auto &it:_m) {
            if (find(v.begin(), v.end(), it.first) == v.end()) {
                if ((!it.second.autoInc && it.second.notNull) ||
                    (it.second.autoInc && it.second.notNull && it.second._v.empty())) {
                    cout << "Immettere valore per il campo " << it.first << ":";
                    string val;
                    cin >> val;
                    abort(val);
                    it.second.newEl(val);
                }
            }
        }
    }

    void newEl(const string &name, string &el) {
        _m[name].newEl(el);
    }

    void delRec(const vector<int> &ind) {
        //  vector <int> ind= move(findVal(v));
        for (auto &it:_m) {
            it.second.delEl(ind);
        }
        if (ind.size() > 1) cout << "Record eliminati." << endl;
        else if (ind.size() == 1) cout << "Record eliminato." << endl;
    }


    void errorIsNotCol(vector<string> &v) {
        for (auto &it:v) {
            bool b = false;
            try {
                isCol(it);
            }
            catch (GenericException &e) {
                cout << e.what() << "Selezionare una nuova colonna." << endl;
                b = true;
            }
            while (b) {
                b = false;
                cin >> it;
                abort(it);
                try {
                    isCol(it);
                }
                catch (GenericException &e) {
                    cout << e.what() << "Selezionare una nuova colonna." << endl;
                    b = true;

                }
            }
        }
    }

    void spaces(const int &max, const int &size) const {
        for (int i = 0; i < max - size + 3; i++) {
            cout << ' ';
        }
    }


    void print() {
        auto a = _m.begin();
        int size = a->second._v.size();
        int j = 0;
        for (const auto &it:_m) {
            cout << it.first;
            spaces(it.second.maxSize, it.first.size());
        }
        cout << endl;
        for (int i = 0; i < size; i++) {
            for (const auto &it:_m) {
                it.second._v[i]->_print();
                spaces(it.second.maxSize, it.second._v[i]->size());
                j++;
                if (j == _m.size()) cout << endl;
            }
            j = 0;
        }
    }


    void print(vector<string> &to_print) {

        if (to_print[0] == "*") print();
        else {
            errorIsNotCol(to_print);

            bool p = false;
            bool np = false;
            int size = _m[to_print[0]]._v.size();
            int j = 0;
            int k = 0;

            for (int i = 0; i < size; i++) {
                for (const auto &it:to_print) {
                    if (_m[it]._v[i]->isEmpty()) k++;
                }
                if (k != to_print.size()) {
                    np = true;
                    for (const auto &it:to_print) {
                        _m[it]._v[i]->_print();
                        spaces(_m[it].maxSize, _m[it]._v[i]->size());
                        j++;
                        if (j == to_print.size()) cout << endl;
                    }
                    j = 0;
                } else p = true;
                k = 0;
            }
            if (p && !np) cout << "Nessun record da stampare." << endl;
        }
    }
    //

    void print(vector<string> &to_print, const vector<string> &v) {
        vector<int> ind = move(findVal(v));
        if (!ind.empty()) {
            if (to_print[0] == "*") {
                to_print.clear();
                for (auto &it:_m) {
                    to_print.push_back(it.first);
                }
            }
            errorIsNotCol(to_print);
            int j = 0;
            int k = 0;
            int x = 0;
            for (const auto &a:ind) {
                for (const auto &it:to_print) {
                    if (_m[it]._v[a]->isEmpty()) k++;
                }
                if (k != to_print.size()) {
                    for (const auto &it:to_print) {
                        _m[it]._v[a]->_print();
                        spaces(_m[it].maxSize, _m[it]._v[a]->size());
                        // if(_m[it]._v[a]->notEmpty())
                        //  cout<<"\t\t";
                        j++;
                        if (j == to_print.size()) cout << endl;
                    }
                    j = 0;
                } else {
                    //cout<<"Nessun elemento da stampare nel record."<<endl;
                    x++;
                }
                k = 0;
            }

            if (x == ind.size())cout << "Nessun record da stampare." << endl;
        }
    }

    void print(const string &col, const string &order, vector<string> &to_print, const vector<string> &v) {
        vector<int> index_to_print = move(findVal(v));
        if (!index_to_print.empty()) {
            if (to_print[0] == "*") {
                to_print.clear();
                for (auto &it:_m) {
                    to_print.push_back(it.first);
                }
            }
            errorIsNotCol(to_print);
            vector<int> new_order = _m[col].order(order);
            int z = 0;
            int size = _m[to_print[0]]._v.size();
            int j = 0;
            vector<int> to_erase;
            for (int i = 0; i < index_to_print.size(); i++) {
                for (const auto &y:to_print) {
                    if (_m[y]._v[index_to_print[i]]->_empty) {
                        z++;
                    }
                }
                if (z == to_print.size()) to_erase.push_back(i);
                z = 0;
            }
            for (int i = to_erase.size() - 1; i >= 0; i--) {
                index_to_print.erase(index_to_print.begin() + to_erase[i]);
            }


            if (index_to_print.empty()) {
                cout << "Nessun record da stampare." << endl;
            } else {
                for (const auto &k:new_order) {
                    for (const auto &it:to_print) {
                        for (const auto &a:index_to_print) {
                            if (a == k) {
                                _m[it]._v[k]->_print();
                                spaces(_m[it].maxSize, _m[it]._v[k]->size());
                                // cout<<"\t\t";
                                j++;
                                if (j == to_print.size()) cout << endl;
                            }
                        }
                    }
                    j = 0;
                }
            }
        }
    }

    //
    void sort(const string &col, const string &order, vector<string> &to_print) {
        if (to_print[0] == "*") {
            to_print.clear();
            for (auto &it:_m) {
                to_print.push_back(it.first);
            }
        }
        errorIsNotCol(to_print);
        vector<int> new_order = _m[col].order(order);
        int x = 0;
        int z = 0;
        for (int a = 0; a < _m[to_print[0]]._v.size(); a++) {
            for (const auto &it:to_print) {
                if (_m[it]._v[a]->isEmpty()) z++;
            }

            if (z == to_print.size()) {
                x++;
            }
            z = 0;
        }
        if (x == _m[to_print[0]]._v.size()) {
            cout << "Nessun record da stampare." << endl;
        } else {
            int j = 0;
            for (const auto &k:new_order) {
                for (const auto &it:to_print) {
                    _m[it]._v[k]->_print();
                    spaces(_m[it].maxSize, _m[it]._v[k]->size());
                    j++;
                    if (j == to_print.size()) cout << endl;
                }
                j = 0;
            }
        }

    }


    std::string str() const {
        std::ostringstream stream;
        stream << _name << " ";
        if (!_primary.empty()) stream << ", " << _primary << " ";
        stream << ";" << endl;
        int i = 0;
        for (const auto &it:_m) {
            stream << it.first << " " << it.second.type() << " ";
            if (it.second.autoInc) stream << "AUTO_INCREMENT ";
            if (it.second.notNull) stream << "NOT NULL ";
            if (it.second.foreign) {
                stream << "FOREIGN " << it.second.linked_tab << " " << it.second.col_ptr->name() << ' ';
            }
            stream << ",";
            if (i == _m.size() - 1) stream << " ;";
            stream << endl;
            i++;
        }

        for (const auto &it:_m) {

            if (it.second.type() == "INT") {
                if (!it.second.autoInc) {
                    for (i = 0; i < it.second._v.size(); i++) {
                        if (it.second._v[i]->notEmpty()) stream << it.second._v[i]->int_val;
                        else stream << "//";
                        stream << "\t";
                        //   if(i==it.second._v.size()-1) stream<<',';
                    }
                } else if (!it.second._v.empty()) {
                    stream << it.second._v[0]->int_val;
                    stream << "\t";
                    for (i = 1; i < it.second._v.size(); i++) {
                        stream << "//" << "\t";
                        //     if(i==it.second._v.size()-1) stream<<',';
                    }
                }
                stream << ',';
            }
            if (it.second.type() == "CHAR") {
                for (i = 0; i < it.second._v.size(); i++) {
                    if (it.second._v[i]->notEmpty()) {
                        if (it.second._v[i]->char_val == ' ') {
                            stream << ",,";
                        } else if (it.second._v[i]->char_val == '\n') {
                            stream << ";;";
                        } else stream << it.second._v[i]->char_val;
                    } else stream << "//";
                    stream << "\t";
                    //   if(i==it.second._v.size()-1) stream<<',';
                }
                stream << ',';
            }
            if (it.second.type() == "TEXT") {
                for (i = 0; i < it.second._v.size(); i++) {
                    if (it.second._v[i]->notEmpty()) {
                        string s = it.second._v[i]->text_val;
                        stream << '"';
                        for (int j = 0; j < s.size(); j++) {
                            if (s[j] == '"') {
                                stream << '/';
                            }
                            stream << s[j];
                        }
                        stream << '"';
                    } else stream << "//";
                    stream << "\t";
                    //    if(i==it.second._v.size()-1) stream<<',';
                }
                stream << ',';
            }
            if (it.second.type() == "FLOAT") {
                for (i = 0; i < it.second._v.size(); i++) {
                    if (it.second._v[i]->notEmpty()) stream << it.second._v[i]->float_val;
                    else stream << "//";
                    stream << "\t";
                    //       if(i==it.second._v.size()-1) stream<<',';
                }
                stream << ',';
            }
            if (it.second.type() == "DATE") {
                for (i = 0; i < it.second._v.size(); i++) {
                    if (it.second._v[i]->notEmpty()) stream << it.second._v[i]->date_val;
                    else stream << "//";
                    stream << "\t";
                    //     if(i==it.second._v.size()-1) stream<<',';
                }
                stream << ',';
            }
            if (it.second.type() == "TIME") {
                for (i = 0; i < it.second._v.size(); i++) {
                    if (it.second._v[i]->notEmpty()) stream << it.second._v[i]->time_val;
                    else stream << "//";
                    stream << "\t";
                    //   if(i==it.second._v.size()-1) stream<<',';
                }
                stream << ',';
            }
            stream << endl;
        }
        stream << endl;
        return stream.str();
    }

    friend std::ostream &operator<<(std::ostream &stream, const Tab &t) {
        stream << t.str();
        return stream;
    }

};

#endif //NEWTEST14_TAB_HPP