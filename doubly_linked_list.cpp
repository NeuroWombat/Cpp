#include <iostream>
using namespace std;

// Creating a node structure - a single element of a doubly linked list
struct Node{
    string name;
    int area;
    int circut;

    // Pointers to the previous and next nodes
    Node* prev;
    Node* next;
};


struct List{
    // Pointers to the first, last, and current node
    Node* head;
    Node* tail;
    Node* currNode;

    // Constructor initializing all nodes to null
    List(){
        head=nullptr;
        tail=nullptr;
        currNode=nullptr;
    }

    // Adding a new node to the end of the list
    void addNode(string n, int a, int c){
        Node* newNode = new Node; // Creating a pointer for the new node

        // Setting the figure data
        newNode->name = n;
        newNode->area = a;
        newNode->circut = c;

        if(head == nullptr){    // Checking if the list is empty
            // The new node becomes the only element in the list if the list is empty
            head = newNode;
            tail = newNode;
            currNode = newNode;

            newNode->next = nullptr;  // Setting the next pointer to null as it's the only node in the list
            newNode->prev = nullptr; // Setting the prev pointer to null as it's the only node in the list
        }else{
            newNode->next = nullptr; // No next node - empty pointer
            newNode->prev = tail;    // Setting the previous pointer to the current tail (the last node)
            tail->next = newNode;    // Updating the 'next' pointer of the current tail to the newly created node
            tail = newNode;          // Updating the tail pointer to the new node
        }
    }

    // Moving through the list left or right
    bool moveInList(char direction){
        bool moved = false;  // Successful movement will be updated in the main function
        if(direction == 'J' || direction == 'j'){   // Moving left
            if(currNode->prev != nullptr) {
                currNode = currNode->prev;  // Moving to the previous node
                moved = true;              // Movement successful
            }else{
                cout << "\n\nPrevious element does not exist\n\n";
            }
        }

        if(direction == 'L' || direction == 'l'){   // Moving right
            if(currNode->next != nullptr){
                currNode = currNode->next;  // Moving to the next node
                moved = true;              // Movement successful
            }else{
                cout << "\n\nNext element does not exist\n\n";
            }
        }
        return moved;   // Returning whether the movement was successful
    }

    void displayData(){
        if(currNode != nullptr){ // Checking if the node exists
            cout << "\n  Name: " << currNode->name << endl;
            cout << "  Area: " << currNode->area << endl;
            cout << "  Circut: " << currNode->circut << endl;
        }else {
            cout << "\n\nNode does not exist\n\n";
        }
    }

    // Deleting a node (linking the neighboring nodes and updating the head or tail if necessary)
    void deleteNode(){
        Node* temp = currNode; // Storing the current node pointer

        if(currNode != nullptr){
            // Updating the head and tail pointers
            if(currNode == head){
                head = currNode->next;
            }else if(currNode == tail){
                tail = currNode->prev;
            }

            // Linking the neighboring nodes to bypass the current node
            if(currNode->prev != nullptr){
                currNode->prev->next = currNode->next;
            }
            if(currNode->next != nullptr){
                currNode->next->prev = currNode->prev;
            }

            // Setting the new current node (preferably the previous node of the deleted node)
            if(currNode->prev != nullptr){
                currNode = currNode->prev;
            }else if(currNode->next != nullptr) {
                currNode = currNode->next;
            }

            delete temp;    // Deleting the node
        }
    }
};


int main(){
    int a, c, now = 1, all = 3;
    char choice;
    string n;
    List list;

    // Adding test values to the list
    list.addNode("Square", 120, 55);
    list.addNode("Rectangle", 12, 12);
    list.addNode("Circle", 20, 25);

    while(true){
        cout << "---------- Figures Database ----------\nTotal figures [" << all << "]";

        if(all == 0){
            cout << "\nNo figures in the database, to add a figure press [A]\nTo exit the program press [X]";
        }else{
            cout << "   |   Current figure [" << now << "]";
            list.displayData();
            cout << "------------------------------\n";
            cout << "[J] previous figure | [L] next figure \n[A] Add figure \n[D] Delete figure \n[X] Exit program\n";
        }

        cin >> choice;

        switch(choice){
            case 'J':
            case 'j':
                if(list.moveInList(choice)){
                    now -= 1; // Decreasing index if movement is successful
                }
            break;

            case 'L':
            case 'l':
                if(list.moveInList(choice)){
                    now += 1; // Increasing index if movement is successful
                }
            break;

            case 'A':
            case 'a':
                cout << "\n\nEnter the name of the figure: "; cin >> n;
                cout << "Enter the area of " << n << ": "; cin >> p;
                cout << "Enter the circut of " << n << ": "; cin >> o;
                list.addNode(n, p, o);

                all += 1;
            break;

            case 'D':
            case 'd':
                list.deleteNode();

                all -= 1;
                if(now > 1){
                    now -= 1;
                }
            break;

            case 'X':
            case 'x':
                return 0;

            default:
                cout << "Invalid character entered, please enter one of these characters [J,j,L,l,A,a,D,d,X,x]\n";
        }
    }
}
