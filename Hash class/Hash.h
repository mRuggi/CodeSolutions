#ifndef HASH_
#define HASH_
#include <string>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::string;

class Hash{

friend ostream& operator<<(ostream &, const Hash &);

private:
int dim;
string* arr1;
string* arr2;

public:
Hash(int d):dim(d){
	arr1=new string[dim];
	arr2=new string[dim];
}
void initialize(){
for(int i=0; i<dim; i++){
cin>>arr1[i];
cin>>arr2[i];
}
}
~Hash(){delete[] arr1; delete[] arr2;}

};







#endif
