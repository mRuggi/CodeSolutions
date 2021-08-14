#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void myswap(string & a,string & b){
string tmp=a;
a=b;
b=tmp;
}
bool ss(const string a){
return(a=="10"||a=="11"||a=="12"||a=="13"||a=="14"||a=="15");
}
bool check_solution(string grid[][4]){  //cout<<(check_solution(grid) ? "si":"no");
string solution[4][4]={{"1","2","3","4"},{"5","6","7","8"},{"9","10","11","12"},{"13","14","15"," "}};
for (int i = 0; i < 4; i++){
	for (int j = 0; j < 4; j++){
	if(grid[i][j]!=solution[i][j]) return false;
	}
}
return true;
}
void printgrid(string[][4]);
void randomizegrid(string[][4]);
void findblankpos(string[][4],int &,int &);
void findnumpos(string[][4],const string &,int &, int &);
void coutmoves(string[][4],int &,int &);

int main(int argc, char** argv) {
	srand(time(NULL));
	int i=0; //riga del posto vuoto
	int ispost=0; //riga del posto da spostare
	int j=0; //colonna del posto vuoto
	int jspost=0; //colonna del posto da spostare
	string num;
	string grid[4][4]={{" ","1","2","3"},{"4","5","6","7"},{"8","9","10","11"},{"12","13","14","15"}};
	randomizegrid(grid);
	while(!check_solution(grid)){
	printgrid(grid);
	cout<<"Puoi spostare i seguenti numeri: ";
	coutmoves(grid,i,j);
	cout<<"Inserisci numero da spostare: ";
	cin>>num;
	findnumpos(grid,num,ispost,jspost);
	myswap(grid[i][j],grid[ispost][jspost]);
	}
	cout<<endl<<"!!!!!!!!!!!!!!!!"<<endl<<"HAI VINTOOOOOOOO!"<<endl<<"!!!!!!!!!!!!!!!!"<<endl;
	printgrid(grid);
	system("PAUSE");
	return 0;
}

void printgrid(string grid[][4]){
for (int i = 0; i < 4; i++){
	cout<<"------------"<<endl;
	for (int j = 0; j < 4; j++){
		if(ss(grid[i][j])) cout<<grid[i][j]<<'|';
		else cout << grid[i][j]<<" |";
	}
	cout<<endl;
}
cout<<"------------"<<endl;
}

void randomizegrid(string grid[][4]){
for (int i = 0; i < 4; i++){
	for (int j = 0; j < 4; j++){
	int row=rand()%4;
	int column=rand()%4;
	myswap(grid[row][column],grid[i][j]);
	}
}
}

void findblankpos(string grid[][4],int & i,int & j){
for (i = 0; i < 4; i++){
	for (j = 0; j < 4; j++){
	if(grid[i][j]==" ") return;
	}
}
}

void findnumpos(string grid[][4],const string & num,int & i, int & j){
for (i = 0; i < 4; i++){
	for (j = 0; j < 4; j++){
	if(grid[i][j]==num) return;
	}
}
}

void coutmoves(string grid[][4],int & i,int & j){
findblankpos(grid,i,j);
if(j!=0) cout<<grid[i][j-1]<<' ';
if(i!=0) cout<<grid[i-1][j]<<' ';
if(j!=3) cout<<grid[i][j+1]<<' ';
if(i!=3) cout<<grid[i+1][j]<<' ';
cout<<endl;
}
