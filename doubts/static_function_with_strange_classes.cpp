#include <iostream>
#include <string>
#include <set>

using namespace std;

void static_variable(const string str);


int main(){
	string words[8] = {"Oi", "Quesser", "seu", "Fiatto", "Oi", "Rohan", "seu", "Katto"};

	for( unsigned i=0 ; i < 8 ; ++i)
		static_variable(words[i]);
	
}


void static_variable(const string str)
{
	static string mtx;
	
	size_t found = mtx.find(str);
	
	if(found != string::npos)
	{
		cout << "Tem alguém aqui" << endl;
	} 
	else
	{
		cout << "Não tem ninguém aqui" << endl;
		mtx.push_back(' ');
		mtx.append(str);
	}
	
	cout << endl << mtx << endl << endl;
}
