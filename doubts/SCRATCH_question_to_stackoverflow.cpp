
// ======================================================================
// Property class:

template<typename T>
class Property;

// ======================================================================
// Interface:

#include <functional>

template <typename T, typename ... Args>
void Property<T>::addDependency( Property<Args>... , std::function< T(Args...) > );

// ======================================================================
// Usage:

double densityFromMassAndVolume( double m, double v)
{
	return m/v;
}

int main()
{
	Property<double> mass;
	Property<double> volume;
	Property<double> density;

	density.addDependency(mass, volume, densityFromMassAndVolume);
}


// ======================================================================
// Possible implementation

#include <vector>
#include <string>

template<typename T>
class Property
{
	using std::vector;
	using std::string;

	public:
		string name;

		template< typename ... Args >
		void addDependency( Property<Args>... , std::function< T(Args...) > );

		void calculateValue

	private:
		vector< vector< string > > dependencyNames;
		MyMagicalType dependencyCalculators;	// What is MyMagicalType?

		T value;
}

template <typename T, typename ... Args >
void Property<T>::addDependency( Property<Args>... propertyArgs, std::function< T(Args...) > calculator )
{
	this->addDependencyNames(propertyArgs...);
		// This does
		// denpendencyNames.push_back( { propertyArgs.name ... } );

	this->dependencyCalculators.push_back(calculator);
}

// ======================================================================
// Particle

#include <vector>
#include <boost/any.hpp>

class Particle
{
	using std::vector;
	using boost::any;

	public:
		void correctDependencies();

	private:
		vector< any > properties;
		vector< string > propertyValues;	// 
		vector< bool > settedFlags;	// settedFlags[n] is true when propertyValues[n] has a proper value
}

void Particle::correctDependencies()
{
	for( auto& property : this->properties )
	{
		
	}
}