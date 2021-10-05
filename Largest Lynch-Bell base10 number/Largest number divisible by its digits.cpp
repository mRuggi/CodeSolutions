/*Find the largest base 10 integer whose digits are all different,
and   is evenly divisible by each of its individual digits.
These numbers are also known as   Lynch-Bell numbers, 
numbers   n   such that the (base ten) 
digits are all different (and do not include zero)
and   n   is divisible by each of its individual digits.
Example
135   is evenly divisible by   1,   3,   and   5.*/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool checkdiffdigit(int num){

stringstream ss;
ss<<num;
string s;
ss>>s;
bool diff=true;
int dim=s.length();

//check for all different digits
for(int i=0; i<dim; i++){
for(int j=i+1; j<dim; j++){
if(s[i]==s[j]) diff=false;
}
}
return diff;
}

bool check(int num){

stringstream ss;
ss<<num;
string s;
ss>>s;
int div=0;
int dim=s.length();

//now the number is in the string
if(!checkdiffdigit(num)) return false;

for(int i=0; i<dim; i++){
char c=s[i];
int digit=(int)c-48;
if(digit==0) return false;
if(num%digit!=0) return false;
else div++;
}
if(div==dim) return true;
}

int main(){

	for(int i=987654321; i>0; i--){
	if(check(i)){cout<<i; break;}
	}
}
