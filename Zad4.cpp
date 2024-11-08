#include<iostream>
#include<string>
using namespace std;

struct Krazek{
    int dl;
    Krazek* next;

    Krazek(int d){
        dl=d;
        next=nullptr;
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
            curr->next=head;
            head=curr;
        }
    }

    void display(int nrStosu, int n){         // Wyświetlanie krążków
        Krazek* temp = head;

        cout<<"Stos nr"<<nrStosu<<endl;
        while (temp != nullptr){
            cout<<string((n-temp->dl)/2,' ')<<string(temp->dl, '-')<<string((n-temp->dl)/2+1,' ')<<"("<<temp->dl<<")"<<endl;
            temp = temp->next;  // Przechodzimy do następnego krążka
        }
        cout<<string((n-5)/2,' ')<<"__|__\n";
    }
};

void przenoszenie(Stos& x, Stos& y){

}

bool wygrana(Stos& S, int n){
    int ilosc=0;
    Krazek* temp=S.head; // Ustawiam zmienna pomocniczą do przejscia przez wszystkie krążki bez zmiany 'głowy'

    while(temp!=nullptr){
        ilosc++;
        temp=temp->next;
    }

    if (ilosc==n){
        return true;
    }

    return false;
}


int main(){
    Stos Stosy[3];
    int zS, doS, n;
    cout<<"Podaj ilosc krazkow [3-10]: ";cin>>n;
    int dl=n+3;
    Stosy[0].addK(dl,n);

    while(!wygrana(Stosy[2],n)){
        Stosy[0].display(1,dl);
        Stosy[1].display(2,dl);
        Stosy[2].display(3,dl);

        cout<<"\n\nZ jakiego stosu chcesz przelozyc krazek? ";cin>>zS;
        cout<<"Na jaki stos chcesz polozyc krazek X.k ze stosu X? ";cin>>doS;
        if(zS>=1 && zS<=3 && doS>=1 && zS<=3 && zS!=doS){
            przenoszenie(Stosy[zS-1], Stosy[doS-1]);
        }else{
            cout<<"Wybierz numery stosow od 1 do 3 (nie przenoszac krazka na ten sam stos)";
        }
    }

    return 0;
}