#include <iostream>

using namespace std;

enum Type1 {A=1, B, C};
enum Type2 {A=10, B, C};

int main()
{
	enum Type1 one = A;
	enum Type2 ten = A;
	cout << endl << endl;

	return 0;
}

/*	Testei se podemos ter enumerações com identificadores com mesmo nome (olhar a pasta ‘lib/doubts’). 
	Não pode. Mas podemos se colocarmos dentro de uma classe.
*/
