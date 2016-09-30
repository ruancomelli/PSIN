/*
   I said to you, Ruan, you cannot have a function member
   inside a structure, nor use C++ comments type.
*/

#include <stdio.h>
#include <stdlib.h>

struct foo
{
	void print();
};

int main(){
	struct foo foo1;

	foo1.print();

	return 0;
}

void print()
{
	printf("\n\nworking!!!\n\n");

	return;
}
