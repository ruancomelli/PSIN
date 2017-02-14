#include <iostream>

using namespace std;

void opaelaia(double hi){
	cout << "Value setted = " << hi << endl;
}

template<typename type>
class RawPhysicalProperty
{
	public:

		void (*set)(type) = NULL;
		type (*get)(void) = NULL;

	private:
		type value;
}; // class RawPhysicalProperty


int main(){
	RawPhysicalProperty<double> oi;
	oi.set = &opaelaia;

	oi.set(58);

	int a;

	cin >> a;
}