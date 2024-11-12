#include <iostream>
#include<string>
using namespace std;

/*    Zadanie 5
Napisz program do przeliczania liczb pomiędzy różnymi systemami liczbowymi poczynając
od systemu dwójkowego, trójkowego poprzez ósemkowy aż do szesnastkowego. Np.
616=...=610=...=203=1102. Na wejściu programu podajemy system liczbowy oraz liczbę zapisaną
w tym systemie a także docelowy system liczbowy. Na wyjściu otrzymujemy liczbę zapisaną w
docelowym systemie liczbowym.
*/

string toX(int n,int p){
    if(n==0){
        return "0";
    }

    string wynik;
    for(int i=0;n!=0;i++){
        int r=n%p;   // Obliczamy resztę z dzielenia
        if(r>10){   // Reszta>10 czyli litera
            wynik.insert(wynik.begin(),'A'+(r-10)); // Dodajemy cyfrę na początek stringa, ponieważ wynik dzielenia resztowego
        }                                                //  zapisuje cyfry od końca – zaczynamy od ostatniej i dopisujemy kolejne z przodu
        else{
            wynik.insert(wynik.begin(),'0'+r);  // Tak jak wyżej tylko dla liczby
        }
        n=n/p;  // Przechodzimy do kolejnej cyfry w systemie docelowym
    }

    return wynik;
}

int toDec(string n, int p){
    int wynik=0,cyfra;
    for(int i=0;i<n.size();i++){
        char znak = n[i];
        if(znak>='0' && znak<='9'){
            cyfra=znak-'0'; // zamieniam wartosc ASCII na liczbe
        }
        else{
            cyfra=znak-'A'+10; // zamieniam wartosc ASCII na numer litery (B-A=1, 1+10=11)
        }
        wynik=wynik*p+cyfra; // Mnożymy bieżący wynik przez podstawę, aby przesunąć cyfry o jedno miejsce w lewo, a następnie dodajemy bieżącą cyfrę
    }

    return wynik;
}


int main(){
    int zSys, doSys;
    string liczba;
    cout<<"Podaj liczbe w dowolnym systemie oraz system na ktory chcesz ja zamienic\n";
    cout<<"Liczba: ";cin>>liczba;
    cout<<"System [2-16]: ";cin>>zSys;
    cout<<"Nowy system liczby [2-16]: ";cin>>doSys;
    cout<<liczba<<"("<<zSys<<") = "<<toX(toDec(liczba,zSys),doSys)<<"("<<doSys<<")\n";

    return 0;
}