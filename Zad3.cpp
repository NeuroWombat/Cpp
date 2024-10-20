#include<iostream>
#include<string>
#include<fstream>     // Obsluga pliku
#include <regex>     // Walidacja danych
#include<sstream>   // Wypisywanie danych

using namespace std;

/*Zadanie 3
Napisz program, który utworzy bazę danych adresowych i będzie nią zarządzać. Program
powinien pozwolić na:
    -> wyświetlanie,
    -> dopisywanie,
    -> modyfikację,
    -> kasowanie,
    -> sortowanie
    Dodatkowo :
    -> błędy operatora,
    -> awaria zasilania
    Nie uszkadzają istniejącej bazy.
*/

const int LINIE=5;

struct Rekord{
    int id;
    string imie;
    string nazwisko;
    string ulica;
    string kod_p;
    string miasto;
    string nr_tel;
    string email;
    string notatka;

    Rekord() = default;

    void addRecord(fstream &plik, int nr){
        id=nr+1;
        cout<<"\t --- Dodawanie rekordu do bazy ---\n";
        cout<<"Podaj imie: ";getline(cin,imie);
        cout<<"Podaj nazwisko: ";getline(cin,nazwisko);
        cout<<"Podaj ulice i numer: ";getline(cin,ulica);
        cout<<"Podaj kod pocztowy: ";getline(cin,kod_p);
        cout<<"Podaj miasto: ";getline(cin,miasto);
        cout<<"Podaj numer telefonu: ";getline(cin,miasto);
        cout<<"Podaj adres e-mail: ";getline(cin,email);
        cout<<"Mozesz dodac notatke lub pominac ten krok, wpisujac '-' : ";getline(cin,notatka);

        dataValidation();

        plik.open("baza.txt", ios::app);
        plik<<id<<endl;
        plik<<imie<<" "<<nazwisko<<endl;
        plik<<ulica<<" "<<kod_p<<" "<<miasto<<endl;
        plik<<nr_tel<<" "<<email<<endl;
        plik<<notatka<<endl;
        plik.close();

    }

    // Walidacja danych
    void dataValidation(){
        regex ePattern(R"((\w+)(\.{0,1}(\w+))*@(\w)(\.\w+)+)");
        regex numPattern(R"((\w+)(\.{0,1}(\w+))*@(\w)(\.\w+)+)");
    }

    void delRecord(fstream &plik){

    }

    void showRecord(fstream &plik, int id){
        plik.open("baza.txt", ios::in);
        string line;
        int count=0;

        if(id==0){  // wypisz wszystkie
            while(getline(plik,line)){
                count++;
                cout<<line<<endl;
                if(count%LINIE==0){
                    cout<<endl<<"------------------------"<<endl<<endl;
                }
            }
        }else{
            while(getline(plik,line)){
                count++;
                if(count>=(id-1)*LINIE && count<=(id-1)*LINIE+LINIE){
                    cout<<line<<endl;
                }
            }
        }
        plik.close();
    }

    void modifyRecord(fstream &plik, int id){

    }

    void sortRecord(fstream &plik, int mode){

    }
};

// Wg. struktury pliku oraz rekodru liczy co 5 linii
int countRecords(fstream& plik){
    int lineC=0, n=0;
    string line;

    while(getline(plik,line)){
        lineC++;
        if(lineC%LINIE==0){
            n++;
        }
    }

    return n;
}

int main() {
    fstream plik("baza.txt", ios::in);
    char choice;
    int id;
    Rekord* nR=new Rekord();

    if (!plik.is_open()) {
        cout <<"Plik jest uszkodzony\n";
        return 1;
    }
    int rekordy=countRecords(plik);
    plik.close();

    while(true) {
        cout<<"\t=== Baza adresow ===\n";

        if(rekordy==0){
            cout<<"Brak rekordow w bazie\n";
        }else{
            cout<<rekordy<<" rekordow w bazie\n";
        }
        cout<<"[W] - wyswietl podany/wszystkie rekord/y, [D] - dodaj rekord, [U] - usun rekord \n";
        cout<<"[M] - modyfikuj rekord, [S] - sortuj rekordy, [X] - zakoncz program\n";
        cout<<"Co chcesz zrobic? ";cin>>choice;

        switch(choice){
            case 'W':
                case 'w':
                cout<<"Podaj ktory rekord chcesz wyswietlic (aby wyswietlic wszystkie podaj 0): ";cin>>id;
                nR->showRecord(plik,id);
                plik.close();
            break;

            case 'D':
            case 'd':
                nR->addRecord(plik, rekordy);
                rekordy++;
                plik.close();
            break;

            case 'U':
            case 'u':
                nR->delRecord(plik);
            break;

            default:
                cout<<"Komunikat";
            break;

            case 'X':
            case 'x':
                return 0;
        }
    }
}