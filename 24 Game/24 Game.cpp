#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
/*Task
Write a program that randomly chooses and displays four digits, each from 1 ──► 9 (inclusive) with repetitions allowed.
The program should prompt for the player to enter an arithmetic expression using just those, and all of those four digits,
used exactly once each. The program should check then evaluate the expression.
The goal is for the player to enter an expression that (numerically) evaluates to 24.

Only the following operators/functions are allowed: multiplication, division, addition, subtraction
Division should use floating point or rational arithmetic, etc, to preserve remainders.
Brackets are allowed, if using an infix expression evaluator.
Forming multiple digit numbers from the supplied digits is disallowed. (So an answer of 12+12 when given 1, 2, 2, and 1 is wrong).
The order of the digits when given does not have to be preserved.

Notes
The type of expression evaluator used is not mandated. An RPN evaluator is equally acceptable for example.
The task is not for the program to generate the expression, or test whether an expression is even possible.*/

void generate(int dim){
cout<<"I tuoi numeri sono: ";
for(int i=0; i<dim; i++){
int a = rand() % 9+1; //da 1 a 9
cout<<a<<' ';
}
cout<<endl<<"Usando UNA SOLA VOLTA, OGNUNO dei tuoi numeri arriva a 24!"<<endl;
}

void menu(){
cout<<"-------------------------------"<<endl;
cout<<"Cosa vuoi fare?"<<endl;
cout<<"(0) genera altri numeri!"<<endl;
cout<<"(1) somma!"<<endl;
cout<<"(2) sottrai!"<<endl;
cout<<"(3) moltiplica!"<<endl;
cout<<"(4) dividi!"<<endl;
cout<<"(5) chiudi gioco!"<<endl;
}

int main() {
	
float result=0;
int numop=0;
float a,b;
int scelta;

srand (time(NULL));
generate(4);


while(scelta!=5&&numop!=3){
menu();
cin>>scelta;
switch(scelta){
	case 0:
		generate(4);
		break;
	case 1:
		if(numop==0){
		cout<<"Inserisci numeri: ";
		cin>>a>>b;
		result=a+b;
		}
		else{
		cout<<"Inserisci numero da aggiungere al risultato precedente: ";
		cin>>a;
		result+=a;
		}
		cout<<result<<endl;
		numop++;
		break;
	case 2:
		if(numop==0){
		cout<<"Inserisci numeri: ";
		cin>>a>>b;
		result=a-b;
		}
		else{
		cout<<"Inserisci numero da sottrarre al risultato precedente: ";
		cin>>a;
		result-=a;
		}
		cout<<result<<endl;
		numop++;
		break;
	case 3:
		if(numop==0){
		cout<<"Inserisci numeri: ";
		cin>>a>>b;
		result=a*b;
		}
		else{
		cout<<"Inserisci numero per cui moltiplicare il risultato precedente: ";
		cin>>a;
		result*=a;
		}
		cout<<result<<endl;
		numop++;
		break;
	case 4:
		if(numop==0){
		cout<<"Inserisci numeri: ";
		cin>>a>>b;
		result=a/b;
		}
		else{
		cout<<"Inserisci numero per cui dividere il risultato precedente: ";
		cin>>a;
		result/=a;
		}
		cout<<result<<endl;
		numop++;
		break;
	default: 
		break;
	}

}

if(result>23.99&&result<24.01) cout<<"HAI VINTO!!"<<endl;
else cout<<"HAI PERSO!"<<endl;

system("PAUSE");
return 0;

}




