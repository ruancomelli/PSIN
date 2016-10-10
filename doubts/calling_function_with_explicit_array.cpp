#include <vector>
#include <iostream>

void display(int * vec){
	cout << endl << vec[0] << endl << vec[1] << endl << endl;
}

int main(void){
	display({0,1});
}

/*
	I tried to pass an explicit array (like {0,1}) as an argument to the function display.
	This is, however, impossible for C++ versions older than C++11.
*/