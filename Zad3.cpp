#include<iostream>
#include<string>
#include<fstream>     // Obsluga pliku
#include <regex>     // Walidacja danych
#include<sstream>   // Wypisywanie danych
#include<cstdio>   // Usuwanie i zmiana nazwy pliku

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

    void addRecord(int nr){
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

        fstream plik("baza.txt", ios::app);
        plik<<id<<","<<imie<<","<<nazwisko<<","<<ulica<<","<<kod_p<<","<<miasto<<","<<nr_tel<<","<<email<<","<<notatka<<endl;
        plik.close();

    }

    // Walidacja danych
    void dataValidation(){
        regex ePattern(R"((\w+)(\.{0,1}(\w+))*@(\w)(\.\w+)+)");
        regex numPattern(R"((\w+)(\.{0,1}(\w+))*@(\w)(\.\w+)+)");
    }

    void delRecord(int id){
        fstream plik("baza.txt", ios::in);
        fstream temp("temp.txt",ios::out);
        string line,delLine;
        int count=-1;
        while(getline(plik,line)){
            if(count!=id){
                temp<<line<<endl;
            }
            count++;
        }
        temp.close();
        plik.close();

        remove("baza.txt");
        rename("temp.txt", "baza.txt");
    }

    void showRecord(int id){
        fstream plik("baza.txt", ios::in);
        string line, data;
        int count=0;

        getline(plik,line);
        line="";

        if(id==0){  // wypisz wszystkie
            while(getline(plik,line)){
                stringstream lineStream(line);
                while(getline(lineStream,data,',')) {
                    cout<<data<<"\t";
                }
                cout<<endl;
            }
        }else{
            while(getline(plik,line)){
                if(count==id) {
                    stringstream lineStream(line);
                    while(getline(lineStream,data,',')){
                        cout<<data<<"\t";
                    }
                    break;
                }
                count++;
            }
        }
        cout<<endl;
        plik.close();
    }

    void modifyRecord(int id){
        fstream plik("baza.txt", ios::in);
        fstream tmp("tmp.txt", ios::out);
        string line;
        int n=0;

        while(getline(plik,line)){
            n++;
            if(n!=id){
                tmp<<line;
            }else{
                addRecord(id);
            }
        }
    }

    void sortRecord(int mode){

    }
};

// Wg. struktury pliku oraz rekodru liczy co 5 linii
int countRecords(){
    fstream plik("baza.txt",ios::in);
    int n=0;
    string line;

    while(getline(plik,line)){
        n++;
    }

    return n-1;
}

int main() {
    fstream plik("baza.txt", ios::in);
    fstream temp("temp.txt", ios::out);
    char choice;
    int id;
    Rekord nR;

    if (!plik.is_open()) {
        cout <<"Plik jest uszkodzony\n";
        return 1;
    }
    int rekordy=countRecords();
    plik.close();

    while(true) {
        cout<<"\t=== Baza adresow ===\n";

        if(rekordy==0){
            cout<<"Brak rekordow w bazie\n";
        }else{
            cout<<rekordy<<" rekordow w bazie\n";
        }
        cout<<"[W] - wyswietl podany/wszystkie rekord/y, [D] - dodaj rekord, [U] - usun rekord \n";
        cout<<"[E] - edytuj rekord, [S] - sortuj rekordy, [X] - zakoncz program\n";
        cout<<"Co chcesz zrobic? ";cin>>choice;

        switch(choice){
            case 'W':
                case 'w':
                cout<<"Podaj ktory rekord chcesz wyswietlic (aby wyswietlic wszystkie podaj 0): ";cin>>id;
                nR.showRecord(id);
                plik.close();
            break;

            case 'D':
            case 'd':
                nR.addRecord(rekordy);
                rekordy++;
                plik.close();
            break;

            case 'U':
            case 'u':
                cout<<"Podaj id wiersza aby go usunac (aby anulowac wpisz 0): ";cin>>id;
                nR.delRecord(id);
            break;

            case 'E':
            case 'e':
                cout<<"Podaj ktory rekord chcesz edytowac";cin>>id;
                nR.showRecord(id);

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