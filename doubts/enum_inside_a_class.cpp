#include <iostream>

using namespace std;

class Test
{
	private:
		enum Type { A, B, C };
	public:
		static void print(Type);
};

int main(){
	Test::print(A);
	return 0;
}

void Test::print(Type a){
	int i;
	i = a;
	cout << endl << "input: " << i << endl << endl;

	return;
}

/*	Testei se podemos ter enumerações com identificadores com mesmo nome (olhar a pasta ‘lib/doubts’). 
	Não pode. Mas podemos se colocarmos dentro de uma classe.
*/
