#include<iostream>
#include<string>
using namespace std;

struct Krazek{
    int dl;
    Krazek* prev;

    // Konstruktor krazka
    Krazek(int d){
        dl=d;
        prev=nullptr;
    }
};

struct Stos{
    Krazek* head;
    Krazek* curr;

    // Konstruktor stosu
    Stos(){
        head=nullptr;
        curr=nullptr;
    }

    // Dodawanie krążka
    void addK(int dl,int n){
        for(int i=0;i<n;i++){
            curr=new Krazek(dl-2*i);
            cout<<endl<<curr->dl<<endl;
            curr->prev=head;
            head=curr;
        }
    }

    // Wyświetlanie krążków
    void display(int nrStosu, int n){
        Krazek* temp = head;

        cout<<"\nStos nr"<<nrStosu<<endl;
        while (temp != nullptr){
            cout<<string(n-(temp->dl/2),' ')<<string(temp->dl, '-')<<string(n-(temp->dl/2)+1,' ')<<"("<<temp->dl<<")"<<endl;
            temp = temp->prev;  // Przechodzimy do następnego krążka
        }
        cout<<string((2*n-1)/2,' ')<<"__|__\n\n";
    }
};

// Przenoszenie krazka miedzy stosami
void move(Stos& x, Stos& y){
    if(x.head!=nullptr){    // Sprawdzanie czy stos z ktorego chcemy przeniesc krazek nie jest pusty
        int dlugosc=x.head->dl;

        if(y.head==nullptr){               // Jezeli docelowy stos jest pusty
            y.head=new Krazek(dlugosc);   // dodajemy krazek do niego
        }else if(y.head->dl>dlugosc){
            Krazek* temp=new Krazek(dlugosc);   // W przeciwnym razie tworzymy zmienna pomocnicza
            temp->prev=y.head;                 // aby moc polaczyc ostatni krazek docelowego stosu
            y.head=temp;                      // z nowym krazkiem oraz ustawienie glowy na niego

            delete temp;    // Zwolnienie pamieci
        }else{
            cout<<"Nie mozesz polozyc wiekszego krazka na mniejszy";
            return;
        }
        x.head = x.head->prev; // Usunięcie krążka ze stosu źródłowego
    }
}

// Sprawdzanie warunku wygranej
bool win(Stos& S, int n){
    int ilosc=0;
    Krazek* temp=S.head; // Ustawiam zmienna pomocniczą do przejscia przez wszystkie krążki bez zmiany 'głowy'

    while(temp!=nullptr){
        ilosc++;
        temp=temp->prev;
    }

    if (ilosc==n){
        cout<<"Gratulacje wygrales!\n";
        return true;
    }

    return false;
}


int main(){
    Stos Stosy[3];
    int zS, doS, n,dl;
    cout<<"Podaj ilosc krazkow [3-10]: ";cin>>n; // sprawdzac limity
    if(n<3 || n>10){
        cout<<"Podaj poprawna ilosc krazkow";
    }

    // Ustalam dlugosc krazkow
    dl=2*n-1;

    Stosy[0].addK(dl,n);    // Dodawanie do 1 stosu ilosc krazkow podana przez uzytkownika
    while(!win(Stosy[2],n)){
        system("cls");

        cout<<"\t--Wieza Hanoi--\n[Umiesc wszystkie krazki na stosie 3, bez ukladania dluzszych krazkow na krotszych]\n";

        // Wysietlenie wszysktich krazkow
        Stosy[0].display(1,dl);
        Stosy[1].display(2,dl);
        Stosy[2].display(3,dl);

        cout<<"\n\nZ jakiego stosu chcesz przelozyc krazek? ";cin>>zS;
        cout<<"Na jaki stos chcesz polozyc krazek X.k ze stosu X? ";cin>>doS;
        if(zS>=1 && zS<=3 && doS>=1 && doS<=3 && zS!=doS){
            move(Stosy[zS-1], Stosy[doS-1]);
        }else{
            cout<<"Wybierz numery stosow od 1 do 3 (nie przenoszac krazka na ten sam stos)";
        }
    }

    system("pause");
    return 0;
}