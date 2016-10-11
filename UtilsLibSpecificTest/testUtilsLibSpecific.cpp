#include <iostream>
#include <Vector.h>

using std::cout;
using std::endl;

int main()
{
	cout << endl;
	cout << endl;
	{
		// Testing setVector templates
		double values[3] = {1.0, 2.0, 3.0};
		vector<double> vec;
		vec.resize(3);
		setVector(vec, values);


		cout << "vec = {\t";
		for (unsigned i=0 ; i<vec.size() ; ++i)
		{
			cout << vec[i] << "\t";
		}
		cout << "}" << endl << endl;
	}

	return 0;
}