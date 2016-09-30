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
