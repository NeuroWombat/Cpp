#include<iostream>
#include<chrono>
using namespace std;

//universalize code (resize_mode, base_size, increment_size)
//change curr to make less resize callouts

struct Stos{
	int* tab;
	int N;
	int curr;

	Stos(int base_size=1000) {
		N=base_size;
		curr=0;
		tab=new int[N];
	}

	~Stos(){
		delete[] tab;
	}

	void push(int value){
		if(curr<N){
			tab[curr]=value;
		}else{
			resizeDouble();
			tab[curr] = value;
		}
		curr++;
	}

	void pop(){
		if(curr>0){
			tab[curr-1]=0;
			curr--;
		}
	}

	int top(){
		return tab[curr-1];
	}

	bool isEmpty(){
		if(curr==0){
			return true;
		}
		return false;
	}

	int size(){
		return curr;
	}

	void resizeIncrement(){
		int* newTab=new int[N+N/2];

		for(int i=0;i<N;i++){
			newTab[i]=tab[i];
		}

		N+=20;
		delete[] tab;
		tab=newTab;

	}

	void resizeDouble(){
		int* newTab=new int[N*2];

		for(int i=0;i<N;i++){
			newTab[i]=tab[i];
		}

		N*=2;
		delete[] tab;
		tab=newTab;
	}
	
};

int main(){
	Stos stos;
	int tests[3]={10000, 100000, 1000000};
	double time[3];

	// Testing
	for(int j=0;j<3;j++){
		auto start=chrono::high_resolution_clock::now();
		for(int i=0;i<tests[j];i++){
			stos.push(i);
		}
		auto end=chrono::high_resolution_clock::now();
		chrono::duration<double> duration=end-start;
		time[j]=duration.count();

	}

	// Printing duration time for every test
	cout<<"\t---Test results---\n";
	for(int j=0;j<3;j++){
		cout<<"For "<<tests[j]<<" push operations: "<<time[j]<<" seconds"<<endl;
	}
	return 0;
}