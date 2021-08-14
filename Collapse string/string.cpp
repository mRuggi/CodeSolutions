#include <iostream>
#include <fstream>
#include <string>

main(){
using namespace std;
string s;
fstream f;

f.open("input.txt",ios::in);

while(getline(f,s)){
	cout<<s<<endl;
	for(int i=0; i<s.size(); i++){
		if(s[i]!=s[i+1]) cout<<s[i];
	}
	cout<<endl;
}

f.close();
system("PAUSE");
return 0;
}
