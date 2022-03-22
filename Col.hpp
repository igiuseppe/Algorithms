#ifndef NEWTEST14_COL_HPP
#define NEWTEST14_COL_HPP

#include <vector>
#include <iostream>
#include "AutoVal.hpp"
#include "Data.hpp"
#include "IntVal.hpp"
#include "TextVal.hpp"
#include "CharVal.hpp"
#include "FloatVal.hpp"
#include "DateVal.hpp"
#include "TimeVal.hpp"
#include "Empty.hpp"
#include <algorithm>
#include <memory>
#include <sstream>
#include "GenericException.hpp"
#include "GrammarException.hpp"

using namespace std;

class Col {
private:
    string _name;
    string _type;

    unique_ptr<Data> _getData(string &s, bool force = false) {
        //this
        unique_ptr<Data> p;
        if (!autoInc) {
            if (_type == "INT") {
                p = unique_ptr<Data>(new IntVal(s));
            } else if (_type == "TEXT") {
                p = unique_ptr<Data>(new TextVal(s));
            } else if (_type == "CHAR") {
                //p=unique_ptr<Data>(new CharVal(s[0]));
                p = unique_ptr<Data>(new CharVal(s));
            } else if (_type == "FLOAT") {
                /*float el=stof(s);
                p=unique_ptr<Data>(new FloatVal(el));*/
                p = unique_ptr<Data>(new FloatVal(s));
            } else if (_type == "DATE") {
                p = unique_ptr<Data>(new DateVal(s));
            } else if (_type == "TIME") {
                p = unique_ptr<Data>(new TimeVal(s));
            }
        } else if (_v.empty() || force) {
            p = unique_ptr<Data>(new AutoVal(s));
            autoi = stoi(s);
        }
        if (s.size() > maxSize) maxSize = s.size();
        return move(p);
    }


public:
    string linked_tab;
    int maxSize = 0;
    vector<unique_ptr<Data>> _v;
    bool notNull = false;
    bool autoInc = false;
    int autoi = 0;
    bool primary = false;
    bool foreign = false;
    Col *col_ptr = nullptr;

    Col() {}

    Col(const string &name, const string &type) {
        _type = type;
        _name = name;
    }

    Col(Col &&c) {
        _type = move(c._type);
        _type = move(c._type);
        maxSize = move(c.maxSize);
        _v = move(c._v);
        linked_tab = move(c.linked_tab);
        notNull = c.notNull;
        autoInc = c.autoInc;
        autoi = move(c.autoi);
        primary = c.primary;
        foreign = c.foreign;
        col_ptr = move(c.col_ptr);
    }

    ~Col() {
        _v.clear();
        col_ptr = nullptr;
        maxSize = 0;
        autoi = 0;
    }

    Col(const Col &to_copy) {
        _name = to_copy._name;
        _type = to_copy._type;
        maxSize = to_copy.maxSize;
        linked_tab = to_copy.linked_tab;
        notNull = to_copy.notNull;
        autoInc = to_copy.autoInc;
        autoi = to_copy.autoi;
        primary = to_copy.primary;
        foreign = to_copy.foreign;
        col_ptr = to_copy.col_ptr;
    }


    void addAuto() {
        //this
        if (_type != "INT") cerr << "Errore di tipo";
        autoi++;
        _v.push_back(unique_ptr<Data>(new AutoVal(autoi)));
    }

    string type() const {
        return _type;
    }

    string name() {
        return _name;
    }

    Col &operator=(Col &&c) {
        _name = move(c._name);
        _type = move(c._type);
        _v = move(c._v);
        maxSize = c.maxSize;
        linked_tab = move(c.linked_tab);
        notNull = c.notNull;
        autoInc = c.autoInc;
        autoi = c.autoi;
        primary = c.primary;
        foreign = c.foreign;
        col_ptr = c.col_ptr;
        return (*this);
    }


    void size() {
        maxSize = _name.size();
    }

    void errorPrimary(unique_ptr<Data> &p, string &s) {
        bool error = true;
        while (error) {
            cout << "Elemento gia' presente nella primary. Inserirne un altro:";
            cin >> s;
            //abort(s);
            p = _getData(s);
            bool b = false;
            for (auto &i : _v) {
                if (!i->_empty && *i == *p) b = true;
            }
            error = b;
        }
    }

    void errorForeign(unique_ptr<Data> &p, string &s) {
        bool error = true;
        while (error) {
            cout << "Elemento " << s << " inserito nella colonna " << name()
                 << " non presente nella colonna collegata. Inserirne un altro: ";
            cin >> s;
            p = _getData(s);
            bool q = false;
            for (const auto &it:col_ptr->_v) {
                if (!it->_empty && *it == *p) q = true;
            }
            error = !q;
        }
    }


    void newEl(string &el, bool force = false) {
        unique_ptr<Data> p = _getData(el);
        if (autoInc) {
            if (_v.empty()) {
                _v.push_back(move(p));
                cout << "Elemento " << el << " aggiunto con successo." << endl;
            } else {
                addAuto();
                cout << "Colonna automatica, il valore inserito non verra' aggiunto al campo: " << _name << endl;
            }
        } else {
            if (primary) {
                bool b = false;
                for (auto &i : _v) {
                    if (!i->_empty && *i == *p) b = true;
                }
                if (b) {
                    errorPrimary(p, el);
                }
            }
            if (foreign && !force) {
                if (col_ptr != nullptr) {
                    bool q = false;
                    for (const auto &it:col_ptr->_v) {
                        if (!it->_empty && *it == *p) q = true;
                    }
                    // if(q){
                    //       _v.push_back(move(p)); cout<<"Elemento "<<el<<" aggiunto con successo."<<endl;}
                    if (!q) {
                        errorForeign(p, el);
                    }
                } else throw (GrammarException("Colonna collegata nullptr."));
            }
            _v.push_back(move(p));
            cout << "Elemento " << el << " aggiunto con successo." << endl;
        }
    }


    void update(string &el, const vector<int> &ind) {
        unique_ptr<Data> p = move(_getData(el));
        if (autoInc) {
            cout << "Errore, campo automatico. L'elemento non verra' inserito alla colonna: " << _name << endl;
        } else if (primary) {
            bool b = false;
            for (auto &i : _v) {
                if (!i->_empty && *i == *p) b = true;
            }
            if (!b) {
                for (int i = 0; i < ind.size(); i++) {
                    if (_v[ind[i]]->_empty) {
                        _v.erase(_v.begin() + ind[i]);
                        _v.insert(_v.begin() + ind[i], move(p));
                    } else *_v[ind[i]] = *p;
                    cout << "Elemento aggiornato con ";
                    _v[ind[i]]->_print();
                    cout << "." << endl;
                }
            } else {
                errorPrimary(p, el);
            }
        } else if (foreign) {
            if (col_ptr != nullptr) {
                bool q = false;
                for (const auto &it:col_ptr->_v) {
                    if (!it->_empty && *it == *p) q = true;
                }
                if (q) {
                    for (int i = 0; i < ind.size(); i++) {
                        if (_v[ind[i]]->_empty) {
                            _v.erase(_v.begin() + ind[i]);
                            _v.insert(_v.begin() + ind[i], move(p));
                        } else *_v[ind[i]] = *p;
                        cout << "Elemento aggiornato con ";
                        _v[ind[i]]->_print();
                        cout << "." << endl;
                    }
                } else {
                    errorForeign(p, el);
                }
            } else throw (GrammarException("Colonna collegata nullptr."));
        } else {
            for (int i = 0; i < ind.size(); i++) {
                if (_v[ind[i]]->_empty) {
                    _v.erase(_v.begin() + ind[i]);
                    _v.insert(_v.begin() + ind[i], move(p));
                } else {
                    *_v[ind[i]] = *p;
                }
                cout << "Elemento aggiornato con ";
                _v[ind[i]]->_print();
                cout << "." << endl;
            }
        }
    }

    void addEmpty() {
        _v.push_back(move(unique_ptr<Data>(new Empty)));
    }

    vector<int> getIndex(const string &op, string &val1, string &val2) {
        unique_ptr<Data> p1 = move(_getData(val1, true));
        unique_ptr<Data> p2 = move(_getData(val2, true));
        vector<int> ind;
        if (*p1 > *p2) {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] <= *p1 && *_v[i] >= *p2) ind.push_back(i);
            }
        } else if (*p1 < *p2) {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] >= *p1 && *_v[i] <= *p2) ind.push_back(i);
            }
        } else {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] == *p1) ind.push_back(i);
            }
        }
        return move(ind);
    }

    vector<int> getIndex(string &el, const string &op) {
        unique_ptr<Data> p = move(_getData(el, true));
        vector<int> ind;
        if (op == "=") {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] == *p) ind.push_back(i);
            }
        } else if (op == "<") {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] < *p) ind.push_back(i);
            }
        } else if (op == "<=") {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] <= *p) ind.push_back(i);
            }
        } else if (op == ">") {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] > *p) ind.push_back(i);
            }
        } else if (op == ">=") {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] >= *p) ind.push_back(i);
            }
        } else if (op == "<>") {
            for (int i = 0; i < _v.size(); i++) {
                if (!_v[i]->_empty && *_v[i] != *p) ind.push_back(i);
            }
        }
        // if(!ind.empty()) cout<<"Elemento "<<el<<" trovato."<<endl;
        return move(ind);
    }


    void delEl(const vector<int> &ind) {
        for (int j = 0; j < ind.size(); j++) {
            _v.erase(_v.begin() + ind[j]);
        }
    }

    void print() {
        for (const auto &i : _v) {
            i->_print();
            cout << endl;
        }
    }

    void print(const vector<int> &ind) {
        for (int i = 0; i < _v.size(); i++) {
            for (int j = 0; j < ind.size(); j++) {
                if (i == ind[j]) _v[i]->_print();
            }
        }
    }

    vector<int> order(const string &order) {
        vector<int> old_order;
        vector<int> empty;
        int k = 0;
        if (order == "ASC") {
            for (int i = 0; i < _v.size(); i++) {
                if (_v[i]->notEmpty()) {
                    for (int j = 0; j < _v.size(); j++) {
                        if (i != j && _v[j]->notEmpty() && *_v[j] <= *_v[i]) {
                            k++;
                        }
                    }
                    old_order.push_back(k);
                    k = 0;
                } else {
                    empty.push_back(i);
                    old_order.push_back(-1);
                }
            }
        } else if (order == "DESC") {

            for (int i = 0; i < _v.size(); i++) {
                if (_v[i]->notEmpty()) {
                    for (int j = 0; j < _v.size(); j++) {
                        if (i != j && _v[j]->notEmpty() && *_v[j] >= *_v[i]) {
                            k++;
                        }
                    }
                    old_order.push_back(k);
                    k = 0;
                } else {
                    empty.push_back(i);
                    old_order.push_back(-1);
                }
            }
        }
        //else throw (GrammarException("Errore nel comando order."));

        vector<int> new_order;
        for (int i = 0; i < _v.size(); i++) {
            for (int j = 0; j < _v.size(); j++) {
                if (old_order[j] == i) {
                    new_order.push_back(j);
                }

            }
        }
        old_order.clear();
        empty.clear();
        return move(new_order);
    }

};

#endif //NEWTEST14_COL_HPP