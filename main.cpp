#include <iostream>
#include <string>
#include "Database.hpp"

/*
 caratteri speciali:
 ; deve essere preceduto senza spazi da / -> /; -> in tutti i campi
 " deve essere preceduto senza spazi da / -> /" -> solo nei campi text
 "spazio" deve essere compreso senza spazi da / -> / / -> solo nei campi char
*/


using namespace std;

int main() {
    import_data();
    cout<<"Scrivere un comando oppure QUIT() per terminare il programma."<<endl;
    string s;
    cin >> s;
    while (!equal(s, "quit()")) {
        getCommand(s);
        if (!equal(s, "select")) {
            export_data();
            cout << "Comando eseguito e dati memorizzati con successo." << endl;
            cout<<"Scrivere un nuovo comando oppure QUIT() per terminare il programma."<<endl;
        }
        cin >> s;
    }


    return 0;
}
