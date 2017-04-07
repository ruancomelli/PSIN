// ==============================================================================================================================
// ==============================================================================================================================
// PropertyDefinitions.h
// ==============================================================================================================================

Property<double> mass;
Property<double> volume;
Property<double> density;


// ----------------------------------------------------- begin NEW THINGS -----------------------------------------------------
double mass_from_v_and_rho(double v, double rho)
{
	return v * rho;
}

mass.depends(volume, density, mass_from_v_and_rho);
// ----------------------------------------------------- end NEW THINGS -----------------------------------------------------

// ==============================================================================================================================
// ==============================================================================================================================
// SphericalParticlePtrArrayKit.cpp
// ==============================================================================================================================
SphericalParticlePtrArrayKit::checkPropertyDependencies()
{
	for( auto& particle : *this )
	{
		particle.checkPropertyDependencies();
	}
}

// ==============================================================================================================================
// Somewhere after the input of particles
// ==============================================================================================================================
particleArray.checkPropertyDependencies();

// ==============================================================================================================================
// ==============================================================================================================================
// PhysicalEntity.cpp
// ==============================================================================================================================
PhysicalEntity::checkPropertyDependencies()
{
	this->propertyArray.checkDependencies();
}

// Ideia para o Property<T>::dependsOn( Property<Args>..., T (*f)(Args...) ):
// Ela pode converter f para uma função g( Any&, Any... ), em que o primeiro Any corresponde
// ao T. essa função g é:
// void g(Any& x, Any... values){
// 		x = f( values... )
// }

// ==============================================================================================================================
// ==============================================================================================================================
// ValuedPropertyContainer.cpp
// ==============================================================================================================================
ValuedPropertyContainer::checkDependencies()
{
	// Suppose that mass depends on volume and density or on radius and density. Then
	// mass.dependencyListNames == { {"Volume", "Density"}, {"Radius", "Density"} }
	// Also, if dependency == dependencyList[0], density and radius are defined, but not volume, then
	// dependency = { {"Volume", "Density"}, {false, true} }
	// but if dependency == dependencyList[1], then
	// dependency = { {"Radius", "Density"}, {true, true} }

	for( property : propertyList )
	{
		for( dependency : property.dependencyList )
		{
			if( dependecy.isEverybodyTrue() )
			{
				property.calculateFromDependencies(); // I don't know how to do this
			}
		}
	}
}

// ==============================================================================================================================
// ==============================================================================================================================
// UtilsLib/functionMasker.cpp
// ==============================================================================================================================

// See http://stackoverflow.com/questions/7858817/unpacking-a-tuple-to-call-a-matching-function-pointer
// See http://www.cplusplus.com/reference/tuple/tie/
// See http://en.cppreference.com/w/cpp/utility/functional/function
// See https://www.google.com.br/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=function+with+lambda+as+parameter+c%2B%2B&* for creating properties.
//	The user may want to pass lambda expressions to constructors and so on instead of passing function pointers. See std::function.
// See http://en.cppreference.com/w/cpp/concept/Container . Maybe we should update some of our classes to match some standard concepts.
// See http://en.cppreference.com/w/cpp/container/array
// See http://en.cppreference.com/w/cpp/utility/tuple/tuple_size
// For variadic templates, see http://eli.thegreenplace.net/2014/variadic-templates-in-c/ , http://en.cppreference.com/w/cpp/language/parameter_pack and http://www.cplusplus.com/articles/EhvU7k9E/
// For something about recursion, see http://www.informit.com/articles/article.aspx?p=30667&seqNum=4
// For initialization, see http://en.cppreference.com/w/cpp/language/aggregate_initialization , http://en.cppreference.com/w/cpp/language/initializer_list and http://en.cppreference.com/w/cpp/language/list_initialization

template<typename T, typename ... Args>
void call( std::function<T (Args...)> f, Any& x, std::vector< Any > )
{

}

template<typename T, typename ... Args>
auto masker( std::function<T (Args...)> f ) 
{
	return 
}