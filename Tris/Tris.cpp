#include <iostream>
#include <string>
#define I 3
#define J 3
using namespace std;

void visualize(string grid[I][J]){
for(int i=0; i<I; i++){
	for(int j=0; j<J; j++){
	if(grid[i][j]==""&&j!=2){cout<<"   |";} //se il valore non è stato inserito faccio solo la casella
	else if(grid[i][j]==""){cout<<"   ";}
	else{cout<<" "<<grid[i][j]; if(j!=2) cout<<" |";}
	}
	if(i!=2){cout<<endl<<"------------"<<endl;}
}
cout<<endl<<endl;
}

bool check_solution(string grid[I][J],int & numwinner,string  &wincon){
bool equal=false;
//check soluzioni righe
for(int i=0; i<I; i++){
if(grid[i][0]!=""&&grid[i][0]==grid[i][1]&&grid[i][1]==grid[i][2]) {equal=true; numwinner=i; wincon="riga";}
}
//check soluzioni colonne
for(int i=0; i<I; i++){
if(grid[0][i]!=""&&grid[0][i]==grid[1][i]&&grid[1][i]==grid[2][i]) {equal=true; numwinner=i; wincon="colonna";}
}
//check soluzioni diagonali
if(grid[1][1]!=""&&grid[1][1]==grid[0][2]&&grid[1][1]==grid[2][0]) {equal=true;  wincon="diagonale";}
if(grid[1][1]!=""&&grid[1][1]==grid[2][2]&&grid[1][1]==grid[0][0]) {equal=true;  wincon="diagonale";}
return equal;
}

void turnx(string grid[I][J]){
int i;
int j;
bool b=false;
string s="X";

while(!b){
cout<<"Inserisci riga dove mettere il tuo simbolo: ";
cin>>i;
cout<<"Inserisci colonna dove mettere il tuo simbolo: ";
cin>>j;
if(grid[i][j]=="") {b=true;}
else cout<<"ERRORE"<<endl;
}
grid[i][j]=s;
}

void turno(string grid[I][J]){
int i;
int j;
bool b=false;
string s="O";

while(!b){
cout<<"Inserisci riga dove mettere il tuo simbolo: ";
cin>>i;
cout<<"Inserisci colonna dove mettere il tuo simbolo: ";
cin>>j;
if(grid[i][j]=="") {b=true;}
else cout<<"ERRORE"<<endl;
}
grid[i][j]=s;
}

void play(string grid[I][J]){
	
int nturn=0;
int poswinner;
string wincon;
string winner;

visualize(grid);

while(!check_solution(grid,poswinner,wincon)&&nturn<9){
turnx(grid);
visualize(grid);
if(check_solution(grid,poswinner,wincon))break;
nturn++;
turno(grid);
visualize(grid);
nturn++;
}

cout<<"GIOCO TERMINATO ";

if(check_solution(grid,poswinner,wincon)){	
if(wincon=="diagonale") winner=grid[1][1];
if(wincon=="riga") winner=grid[poswinner][0];
if(wincon=="colonna") winner=grid[0][poswinner];	
cout<<"TRIS del giocatore "<<winner<<" sulla "<<wincon<<" !";
}
else cout<<"PAREGGIO!";



}

int main(){
string grid[I][J];
play(grid);

cout<<endl;
system("PAUSE");
return 0;
}
