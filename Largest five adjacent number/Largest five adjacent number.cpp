#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

string gen_random(const int len) {
    string tmp_s;
    static const char num[] = "0123456789";
    static const char firstnum[] ="123456789";
    
    srand( (unsigned) time(NULL) * getpid());

    tmp_s.reserve(len);
    
	tmp_s += firstnum[rand() % (sizeof(firstnum) - 1)]; //first digit can't be 0
	
    for (int i = 0; i < len-1; ++i) 
        tmp_s += num[rand() % (sizeof(num) - 1)]; //all other digits can
    return tmp_s;
}

int main(int argc, char *argv[]) {
    string fivedigit;
    string alotofdigits=gen_random(1000);
    int result=0;
    int partialresult=0;
    
    cout << alotofdigits << endl;
    
  	for(int i=0; i<alotofdigits.length()-4; i++){
	  for(int j=i; j<5+i; j++){
	  fivedigit+=alotofdigits[j];
	  }
	  stringstream intvalue(fivedigit);
	  intvalue>>partialresult;
	  if(partialresult>result){result=partialresult;}
	  fivedigit="";
	  }
	  
	  cout<<"RESULT: "<<result<<endl;
	  
    return 0;
}
