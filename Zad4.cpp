#include<iostream>
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

    void addK(int dl){      // Dodawanie krążka
        curr=new Krazek(dl);
        curr->next=head;
        head=curr;
    }

    void display(){         // Wyświetlanie krążków
        Krazek* temp = head;
        int a=0;
        while (temp != nullptr){
            a++;
            temp = temp->next;  // Przechodzimy do następnego krążka
        }
        cout<<"Stos nr"<< " | Ilosc elementow: "<<a<<endl;
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

    cout<<ilosc;
    if (ilosc==n){
        return true;
    }

    return false;
}


int main(){
    Stos S1, S2, S3;
    Stos* stosy[3]={&S1, &S2, &S3};
    int zStosu, doStosu, n;
    cout<<"Podaj ilosc krazkow [3-10]: ";cin>>n;

    for(int i=1;i<=n;i++){ // Wypełnianie pierwszego stosu krążkami
        S1.addK(n-i);
    }

    while(!wygrana(S3,n)){
        S1.display();
        S2.display();
        S3.display();

        cout<<"Z jakiego stosu chcesz przelozyc krazek? ";cin>>zStosu;
        cout<<"Na jaki stos chcesz polozyc krazek X.k ze stosu X? ";cin>>doStosu;
        if(zStosu>=1 && zStosu<=3 && doStosu>=1 && zStosu<=3 && zStosu!=doStosu){
            przenoszenie(*stosy[zStosu-1], *stosy[doStosu-1]);
        }else{
            cout<<"";
        }
    }

    return 0;
}