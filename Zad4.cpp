#include<iostream>
#include<string>
using namespace std;

struct Krazek{
    int dl;
    Krazek* prev;

    Krazek(int d){
        dl=d;
        prev=nullptr;
    }
};

struct Stos{
    Krazek* head;
    Krazek* curr;

    Stos(){     // Konstruktor stosu
        head=nullptr;
        curr=nullptr;
    }

    void addK(int dl,int n){      // Dodawanie krążka
        for(int i=0;i<n;i++){
            curr=new Krazek(dl-2*i);
            curr->prev=head;
            head=curr;
        }
    }

    void display(int nrStosu, int n){         // Wyświetlanie krążków
        Krazek* temp = head;

        cout<<"\nStos nr"<<nrStosu<<endl;
        while (temp != nullptr){
            cout<<string((n-temp->dl)/2,' ')<<string(temp->dl, '-')<<string((n-temp->dl)/2+1,' ')<<"("<<temp->dl<<")"<<endl;
            temp = temp->prev;  // Przechodzimy do następnego krążka
        }
        cout<<string((n-5)/2,' ')<<"__|__\n\n";
    }
};

void move(Stos& x, Stos& y){
    if(x.head!=nullptr){
        int dlugosc=x.head->dl;

            // ogarnąc bardziej logicznie te warunki + dodać komunikaty
        if(y.head==nullptr){
            y.head=new Krazek(dlugosc);
            x.head=x.head->prev;
        }else if(y.head!=nullptr && y.head->dl>dlugosc){
            Krazek* temp;
            temp=new Krazek(dlugosc);
            temp->prev=y.head;
            y.head=temp;
            x.head=x.head->prev;
        }else{
            cout<<"Komunikat";
        }

    }
}

bool win(Stos& S, int n){
    int ilosc=0;
    Krazek* temp=S.head; // Ustawiam zmienna pomocniczą do przejscia przez wszystkie krążki bez zmiany 'głowy'

    while(temp!=nullptr){
        ilosc++;
        temp=temp->prev;
    }

    if (ilosc==n){
        return true;
    }

    return false;
}


int main(){
    Stos Stosy[3];
    int zS, doS, n;
    cout<<"Podaj ilosc krazkow [3-10]: ";cin>>n; // sprawdzac limity
    int dl=n+3; // bardziej przemyslana dlugosc

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
        if(zS>=1 && zS<=3 && doS>=1 && zS<=3 && zS!=doS){
            move(Stosy[zS-1], Stosy[doS-1]);
        }else{
            cout<<"Wybierz numery stosow od 1 do 3 (nie przenoszac krazka na ten sam stos)";
        }
    }
    //komunikat wygranej + sleep

    return 0;
}