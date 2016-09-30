#include <iostream>
#include <string>
#include <set>

using namespace std;

void static_variable(const string str);


int main(){
	string words[8] = {"Oi", "Quesser", "seu", "Fiatto", "Oi", "Rohan", "seu", "Katto"};
	
	set <string> storage;
	
	for( unsigned i=0 ; i < 8 ; ++i)
		if(storage.find(words[i]) == storage.end()){
			cout << endl << "Palavra inserida:" << words[i] << endl;
			storage.insert(words[i]);
			cout << endl << "Storage set:" << endl;
			for( set <string>::iterator k = storage.begin() ; k != storage.end() ; ++k)
				cout << *k << endl;
		}
	
	
	
	for( set <string>::iterator k = storage.begin() ; k != storage.end() ; ++k)
		cout << endl << *k << endl;
}

//	Conclusions:
//		* The elements in the container follow a strict order at all times. All inserted elements are given a position in this order.