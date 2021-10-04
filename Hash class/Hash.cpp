#include "Hash.h"

ostream& operator<<(ostream & out, const Hash & h){
for(int i=0; i<h.dim; i++){
out<<h.arr1[i]<<'-'<<h.arr2[i]<<endl;
}
return out;
}
