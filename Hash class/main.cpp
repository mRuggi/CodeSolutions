#include <iostream>
#include "Hash.h"

int main(int argc, char** argv) {
	int n;
	cout<<"Insert hash dimension: ";
	cin>>n;
	Hash a(n);
	a.initialize();
	cout<<"HASH STATUS:"<<endl<<a;
	return 0;
}
