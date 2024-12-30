#include<iostream>
#include<string>
using namespace std;

struct Disc{
    int ln;
    Disc* prev;

    // Disc consturctor
    Disc(int size){
        ln=size;
        prev=nullptr;
    }
};

struct Stack{
    Disc* head;
    Disc* curr;

    // Stack constructor
    Stack(){
        head=nullptr;
        curr=nullptr;
    }

    // Adding disc
    void addD(int ln,int n){
        for(int i=0;i<n;i++){
            curr=new Disc(ln-2*i);
            cout<<endl<<curr->ln<<endl;
            curr->prev=head;
            head=curr;
        }
    }

    // Displaying discs
    void display(int stackNr, int n){
        Disc* temp = head;

        cout<<"\nStack nr"<<stackNr<<endl;
        while (temp != nullptr){
            cout<<string(n-(temp->ln/2),' ')<<string(temp->ln, '-')<<string(n-(temp->ln/2)+1,' ')<<"("<<temp->ln<<")"<<endl;
            temp=temp->prev;  // Moving to the next disc
        }
        cout<<string((2*n-1)/2,' ')<<"__|__\n\n";
    }
};

// Moving discs between stacks
void move(Stack& x, Stack& y){
    if(x.head!=nullptr){    // Checks if the stack from which we want to move the disc is not empty
        int length=x.head->ln;

        if(y.head==nullptr){               // Checking if the target stack is not empty
            y.head=new Disc(length);      // Adding disc to target stack
        }else if(y.head->ln>length){
            Disc* temp=new Disc(length);     //  Otherwise, create a temporary variable
            temp->prev=y.head;                 // To connect the last disk of the target stack with the new disc
            y.head=temp;                      // set the head to the new disc


        }else{
            cout<<"You can't place bigger disc on smaller";
            return;
        }
        x.head = x.head->prev; // Deletes disc from source stack
    }
}

// Win condition
bool win(Stack& S, int n){
    int i=0;
    Disc* temp=S.head; // Set auxiliary variable to go throught all discs without changing the 'head'

    while(temp!=nullptr){
        i++;
        temp=temp->prev;
    }

    if (i==n){
        cout<<"Congratulations you won!\n";
        return true;
    }

    return false;
}


int main(){
    Stack Stacks[3];
    int fromS,toS,n,ln;
    cout<<"Enter the number of discs [3-10]: ";cin>>n;
    if(n<3 || n>10){
        cout<<"Please enter a valid number od discs";
        return 0;
    }

    ln=2*n-1;   // Disc length

    Stacks[0].addD(ln,n);        // Adding the specified number of discs to the first stack
    while(!win(Stacks[2],n)){   // Check for win condition
        system("cls");

        cout<<"\t--Tower of Hanoi--\n[Place all disks on stack 3, without stacking larger disks on smaller ones]\n";

        // Display all the discs
        Stacks[0].display(1,ln);
        Stacks[1].display(2,ln);
        Stacks[2].display(3,ln);

        cout<<"\n\nWhich stack do you want to move a disc from? ";cin>>fromS;
        cout<<"Which stack do you want to place the disc on? ";cin>>toS;
        if(fromS>=1 && fromS<=3 && toS>=1 && toS<=3 && toS!=fromS){
            move(Stacks[fromS-1], Stacks[toS-1]);
        }else{
            cout<<"Select stack numbers from 1 to 3 (do not move a disk to the same stack).";
        }
    }

    system("pause");
    return 0;
}
