#include <iostream>
#include<string>
using namespace std;

// From decimal to every base
string toX(int n,int b){
    if(n==0){
        return "0";
    }

    string result;
    for(int i=0;n!=0;i++){
        int r=n%b;   // Calculate the reminder of the division
        if(r>10){   // Reminder > 10, so it corresponds to a letter
            result.insert(result.begin(),'A'+(r-10)); // Add the character to the begining of the string because the result
        }                                           // of the division produces digits in reverse order
        else{
            result.insert(result.begin(),'0'+r);  // Same as above but for numbers
        }
        n=n/b;  // Move to the next digit in the given numeral system
    }

    return result;
}

// From every base to decimal
int toDec(string n, int b){
    int result=0,digit;
    for(int i=0;i<n.size();i++){
        char ch=n[i];
        if(ch>='0' && ch<='9'){
            digit=ch-'0'; // Convert ASCII value to a number
        }
        else{
            cyfra=znak-'A'+10; // Convert ASCII value to the corresponding letter number (B-A=1, 1+10=11)
        }
        result=result*b+digit; // Multiply the current result by the base to shift digits left, then add the current digit
    }

    return result;
}


int main(){
    int formSys, toSys;
    string number;
    cout<<"Enter a number in any numeral system and the system you want to convert it to\n";
    cout<<"Number: ";cin>>number;
    cout<<"System [2-16]: ";cin>>formSys;
    cout<<"New numeral system [2-16]: ";cin>>toSys;
    if(number.empty()){
        cout<<"No number provided.\n";
    }else if(number=="0"){
        cout<<"You entered the number 0, in every system the result is equal to 0\n";
    }else if(formSys<2 && fromSys>16){
        cout<<"The given system is not within range [2-16]";
    }else if(toSys<2 && toSys>16){
        cout<<"The given system is not within range [2-16]";
    }

    if(!number.empty() && fromSys>=2 && fromSys<=16 && toSys>=2 && toSys<=16){
        cout<<number<<"("<<fromSys<<") = "<<toX(toDec(number,fromSys),toSys)<<"("<<toSys<<")\n";
    }else if(number.empty()){
        cout<<"Please provide valid input\n";
    }

    return 0;
}
