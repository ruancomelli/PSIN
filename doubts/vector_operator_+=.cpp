#include <iostream>
#include "Containers.h"
#include "MatrixVectorOperations.h"

int main(){
	vector<double> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector<double> w;

	w.push_back(4);
	w.push_back(5);
	w.push_back(6);

	v += w;

	cout << endl;
	cout << endl;
	for(unsigned i=0 ; i<v.size() ; i++){
		cout << " " << v[i] << ", ";
	}
	cout << endl;
	cout << endl;

	return 0;
}
