#include <iostream>
using namespace std;

/*Zadanie 1
Napisz program implementujący dynamiczną listę dwukierunkową zawierającą struktury
przechowujące informacje o nazwach figur geometrycznych, ich polach oraz obwodach
Program powinien pozwalać na:
    > dodawanie elementów do isty,
    > na ich usuwanie,
    > nawigację.
*/

// Tworzenie struktury węzła - pojedynczego elementu listy dwukierunkowej
struct Node {
    string nazwa;
    int pole;
    int obw;

    // Wskaźniki do poprzedniego i następnego węzła
    Node* prev;
    Node* next;
};


struct List {
    // Wskaźniki na pierwszy, ostatni oraz aktualny węzeł
    Node* head;
    Node* tail;
    Node* currNode;

    // Konstruktor listy ustawiający wszystkie węzły na puste
    List(){
        head=nullptr;
        tail=nullptr;
        currNode=nullptr;
    }

    // Dodawanie nowego węzła na koniec listy
    void addNode(string n,int p,int o) {
        Node* newNode=new Node; // Tworzenie wskaźnika nowego węzła

        // Ustawianie danych figury
        newNode->nazwa=n;
        newNode->pole=p;
        newNode->obw=o;

        if(head == nullptr){    // Sprawdzenie czy lista jest pusta
            // Nowy węzeł staje się jedynym elementem listy, jeśli lista jest pusta
            head=newNode;
            tail=newNode;
            currNode=newNode;

            newNode->next = nullptr;  // Ustawiam wskaźniki na puste wartości ponieważ
            newNode->prev = nullptr; // jest to jedyny węzeł w liście
        }else{
            newNode->next=nullptr; // Brak następnego węzła - pusty wskaźnik
            newNode->prev=tail;   // Ustawianie wskaźnika poprzedniego węzła na niezaktualizowany ogon (aktualnie przeodstatni węzeł)
            tail->next=newNode;  // Ustawienie wskaźnika `next` poprzedniego ogona na nowo utworzony węzeł
            tail=newNode;       // Aktualizacja wskaźnika ogonu
        }
    }

    // Poruszanie się po liście w lewo lub prawo
    bool moveInList(char direction){
        bool moved=false;  // Udany ruch będziemy aktualizować listę w głównej funckji
        if(direction=='J' || direction=='j'){   // Poruszanie się w lewo
            if(currNode->prev!=nullptr) {
                currNode=currNode->prev;  // Przejście do poprzedniego węzła
                moved=true;              // Ruch udany
            }else{
                cout<<"\n\nPoprzedni element nie istnieje\n\n";
            }
        }

        if(direction=='L' || direction=='l'){   // Poruszanie się w prawo
            if(currNode->next!=nullptr){
                currNode=currNode->next;  // Przejście do następnego węzła
                moved=true;              // Ruch udany
            }else{
                cout<<"\n\nNastepny element nie istnieje\n\n";
            }
        }
        return moved;   // Zwracamy czy ruch był udany
    }

    void displayData(){
        if(currNode!=nullptr){ // Sprawdzenie czy węzeł istnieje
            cout<<"\n  Nazwa: "<<currNode->nazwa<<endl;
            cout<<"  Pole: "<<currNode->pole<<endl;
            cout<<"  Obowd: "<<currNode->obw<<endl;
        }else {
            cout<<"\n\nWezel nie istnieje\n\n";
        }
    }

    // Usuwanie węzła (łączenie ze sobą sąsiednich węzłów oraz aktualizowanie głowy lub ogona w razie potrzeby)
    void deleteNode() {
        Node* temp=currNode; // Zapisanie wskaźnika do aktualnego węzła

        if(currNode!=nullptr){
            // Aktualizowanie wskaźnika głowy i ogona
            if(currNode==head){
                head=currNode->next;
            }else if(currNode==tail){
                tail=currNode->prev;
            }

            // Łączenie wskaźników węzłów między aktualnym
            if(currNode->prev!=nullptr){
                currNode->prev->next=currNode->next;
            }
            if(currNode->next!=nullptr){
                currNode->next->prev=currNode->prev;
            }

            // Ustawianie nowego aktualnego węzła (preferując poprzednika usuwanego węzła)
            if(currNode->prev!=nullptr){
                currNode=currNode->prev;
            }else if(currNode->next!=nullptr) {
                currNode=currNode->next;
            }

            delete temp;    // Usunięcie węzła
        }
    }
};


int main(){
    int p, o, now=1, all=3;
    char choice;
    string n;
    List list;

    // Dodanie testowych wartości do listy
    list.addNode("Kwadrat",120,55);
    list.addNode("Prostokat",12,12);
    list.addNode("Kolo",20,25);

    while(true){
        cout<<"---------- Baza figur ----------\nIlosc figur ["<<all<<"]";

        if(all==0){
            cout<<"\nBrak figur w bazie, aby dodac figure wpisz [A]\nAby wyjsc z programu wpisz [X]";
        }else{
            cout<<"   |   Aktualna figura ["<<now<<"]";
            list.displayData();
            cout<<"------------------------------\n";
            cout<<"[J] poprzednia figura | [L] nastepna figura \n[A] Dodaj figure \n[D] Usun figure \n[X] Wyjscie z programu\n";
        }

        cin>>choice;

        switch(choice) {
            case 'J':
            case 'j':
                if(list.moveInList(choice)){
                    now-=1; // Zmniejszamy index gdy ruch udany
                }
            break;

            case 'L':
            case 'l':
                if(list.moveInList(choice)) {
                    now+=1; // Zwiększamy index gdy ruch udany
                }
            break;

            case 'A':
            case 'a':
                cout<<"\n\nPodaj nazwe figury: ";cin>>n;
                cout<<"Podaj pole "<<n<<": ";cin>>p;
                cout<<"Podaj obwod "<<n<<": ";cin>>o;
                list.addNode(n,p,o);

                all+=1;
            break;

            case 'D':
            case 'd':
                list.deleteNode();

                all-=1;
                if(now>1){
                    now-=1;
                }
            break;

            case 'X':
            case 'x':
                return 0;

            default:
                cout<<"Wprowadzony niepoprawny znak, wpisz jeden z tych znakow [J,j,L,l,A,a,D,d,X,x]\n";
        }
    }
}