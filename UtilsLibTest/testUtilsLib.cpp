#define BOOST_TEST_MODULE TestModule

// Standard
#include <string>
#include <type_traits>

// UtilsLib
#include <Any.hpp>
#include <FileSystem.hpp>
#include <Foreach.hpp>
#include <Mathematics.hpp>
#include <Named.hpp>
#include <ProgramOptions.hpp>
#include <SharedPointer.hpp>
#include <StringUtils.hpp>
#include <Test.hpp>
#include <UniquePointer.hpp>
#include <Variant.hpp>
#include <Vector.hpp>
#include <Vector3D.hpp>
#include <Metaprogramming/bool_type.hpp>
#include <Metaprogramming/type_list.hpp>
#include <Metaprogramming/type_collection.hpp>
#include <Metaprogramming/make_unique_type_list.hpp>

using namespace std;

TestCase( CheckEqualAndCheckClose )
{
	double i = 0;
	double j = 0;

	checkClose( i , j , 1.0e-12 );
	checkEqual( i , j );
}

// ----- Any -----
TestCase(AnyTest)
{
	int i = 3;
	double d = 3.14;
	string s = "oi";

	Any any = i;
	checkEqual(anyCast<int>(any), i);

	any = d;
	checkEqual(anyCast<double>(any), d);

	any = s;
	checkEqual(anyCast<string>(any), s);

	std::vector< Any > many;
	many.push_back(i);
	many.push_back(d);
	many.push_back(s);

	checkEqual(anyCast<int>(many[0]), i);
	checkEqual(anyCast<double>(many[1]), d);
	checkEqual(anyCast<string>(many[2]), s);
}

// ----- Foreach -----
TestCase( ForeachTest ){
	DoubleVector values;
	int nValues = 5;
	double rawValues[] = { 2.71, 3.14, 0.0, -3.14, -2.71 };

	for( int i = 0; i < nValues; ++i ){
		values.push_back( rawValues[ i ] );
	}

	int counter = 0;
	foreach( double v, values ){
		checkClose( rawValues[ counter ], v, 1.0e-12 );
		++counter; 
	}
}

// ----- SharedPointer -----
TestCase(SharedPointerTest) {
	SharedPointer<Vector3D> v0( new Vector3D );

	(*v0).x() = 1.0;
	(*v0).y() = 2.0;
	(*v0).z() = 3.0;
	
	SharedPointer<Vector3D> v1(new Vector3D(*v0));

	checkEqual((*v0).x(), v1->x());
	checkEqual((*v0).y(), v1->y());
	checkEqual((*v0).z(), v1->z());
}

TestCase(UniquePointerTest)
{
	UniquePointer<Vector3D> v0( new Vector3D );

	(*v0).x() = 1.0;
	(*v0).y() = 2.0;
	(*v0).z() = 3.0;
	
	UniquePointer<Vector3D> v1 = makeUnique<Vector3D>( *v0 );

	checkEqual((*v0).x(), v1->x());
	checkEqual((*v0).y(), v1->y());
	checkEqual((*v0).z(), v1->z());
}

// StringUtils
TestCase(StringCompareTest) {
	string left("<LaTeX>");
	string right("<latex>");

	check(!stringCompare("<LaTeX>", "<latex>"));
	check(!stringCompare(left, right));
}

// Mathematics
TestCase(MathematicsTest) {

	// math define
	checkEqual(M_E, 2.71828182845904523536);
	checkEqual(M_PI, 3.14159265358979323846);

	// factorial
	checkEqual(factorial(6), 720);
}

//DoubleVector and DoubleVector2D

TestCase( DoubleVectorScalarOperatorTest ){
	DoubleVector u( 3, 0.0 );
	u[0] = 1.;
	u[1] = 2.;
	u[2] = -4.;

	double scalar = 2.5;

	DoubleVector B = scalar*u;  

	checkClose( B[0] , 2.5 , 1.0e-12 );
	checkClose( B[1] , 5. , 1.0e-12 );
	checkClose( B[2] , -10. , 1.0e-12 );
}

TestCase( DoubleVectorPlusEqualLessEqualTimesEqualOperators ){
	DoubleVector v1(2,0);
	v1[0] = -2.0;
	v1[1] = +3.0;

	DoubleVector v2(2,0);
	v2[0] = +2.0;
	v2[1] = -4.0;

	DoubleVector v3(2,0);
	v3[0] = +3.0;
	v3[1] = +5.0;

	// operator +=
	v1 += v2;
	checkClose(v1[0] , 0.0 , 1.0e-12);
	checkClose(v1[1] , -1.0 , 1.0e-12);

	// operator -=
	v2 -= v3;
	checkClose(v2[0] , -1.0 , 1.0e-12);
	checkClose(v2[1] , -9.0 , 1.0e-12);

	// operator *=
	v3 *= 5;
	checkClose(v3[0] , 15.0 , 1.0e-12);
	checkClose(v3[1] , 25.0 , 1.0e-12);
}

TestCase( DoubleVector2DDoubleVectorProductOperatorTest ){
	DoubleVector2D A( 2, DoubleVector( 2, 0.0 ) );
	A[0][0] = 4.;  A[0][1] = 3.;
	A[1][0] = -4.;  A[1][1] = 1.;

	DoubleVector B( 2, 0.0 );
	B[0] = 1.;
	B[1] = 6.;

	DoubleVector C = A*B;
	checkClose( C[0] , 22. , 1.0e-12 );
	checkClose( C[1] , 2. , 1.0e-12 );
}

TestCase( DoubleVector2DScalarOperatorTest ){
	DoubleVector2D A( 2, DoubleVector( 2, 0.0 ) );
	A[0][0] = 1.;
	A[0][1] = 2.;
	A[1][0] = -4.;
	A[1][1] = -3.;

	double scalar = 2.0;

	DoubleVector2D B = scalar*A;  
	checkClose( B[0][0] , 2. , 1.0e-12 );
	checkClose( B[0][1] , 4. , 1.0e-12 );
	checkClose( B[1][0] , -8. , 1.0e-12 );
	checkClose( B[1][1] , -6. , 1.0e-12 );
}

TestCase( DoubleVector2DInnerProductOperatorTest ){
	DoubleVector2D A( 2, DoubleVector( 3, 0.0 ) );
	A[0][0] = 3.;  A[0][1] = 1.;  A[0][2] = 2.;
	A[1][0] = 5.;  A[1][1] = 8.;  A[1][2] = 3.;

	DoubleVector2D B( 3, DoubleVector( 2, 0.0 ) );
	B[0][0] = 3.;  B[0][1] = 1.;
	B[1][0] = 4.;  B[1][1] = 4.;
	B[2][0] = 5.;  B[2][1] = 8.;

	DoubleVector2D C = A*B;
	checkClose( C[0][0] , 23. , 1.0e-12 );
	checkClose( C[0][1] , 23. , 1.0e-12 );
	checkClose( C[1][0] , 62. , 1.0e-12 );
	checkClose( C[1][1] , 61. , 1.0e-12 );
}

TestCase( InnerProductOperator ){
	DoubleVector v1( 3 , 0 );
	v1[0] = +2.0;
	v1[1] = -3.0;
	v1[2] = +4.0;

	DoubleVector v2( 3 , 0 );
	v2[0] = -5.0;
	v2[1] = -9.0;
	v2[2] = +7.0;

	double inner = innerProduct(v1, v2);
	checkClose( inner, +45.0 , 1.0e-12 );
}

TestCase( NormOperator ){
	DoubleVector v1( 3 , 0 );
	v1[0] = +2.0;
	v1[1] = -3.0;
	v1[2] = +4.0;

	double nor = norm(v1);
	checkClose( nor, +5.385164807 , 1.0e-8 );
}

TestCase( NormalizeOperator ){
	DoubleVector v1( 3 , 0 );
	v1[0] = +2.0;
	v1[1] = -3.0;
	v1[2] = +4.0;

	normalize(v1);
	checkClose( v1[0], +0.371390676354104 , 1.0e-12 );
	checkClose( v1[1], -0.557086014531156 , 1.0e-12 );
	checkClose( v1[2], +0.742781352708207 , 1.0e-12 );
}

TestCase( NullVectorTest ){
	DoubleVector null = nullVector(5);

	for(double d : null){
		checkEqual( d , 0.0 );
	}
}

// ----- Vector3D -----

TestCase(AssigningValueToVector3D) {
	Vector3D v;
	v.x() = 1;
	v.y() = 9;
	v.z() = 4.3;

	checkEqual(v.x(), 1);
	checkEqual(v.y(), 9);
	checkEqual(v.z(), 4.3);
}

TestCase( Vector3DInitializationTest ){

	// Default constructor
	Vector3D v0;
	checkEqual( 0.0 , v0.x() );
	checkEqual( 0.0 , v0.y() );
	checkEqual( 0.0 , v0.z() );

	// Passing three arguments to constructor
	Vector3D v1(1.0 , 2.0 , 3.0 );
	checkEqual( 1.0 , v1.x() );
	checkEqual( 2.0 , v1.y() );
	checkEqual( 3.0 , v1.z() );

	// Passig a vector to constructor
	Vector3D v2( v1 );
	checkEqual( 1.0 , v2.x() );
	checkEqual( 2.0 , v2.y() );
	checkEqual( 3.0 , v2.z() );
}

TestCase( Vector3DFunctionsMembers ){
	Vector3D v1( 1.0 , 2.0 , 3.0 );

	//Vector3D::length()
	double len = v1.length();
	checkClose(len , 3.74165738677394 , 1.0e-8 );

	//Vector3D::squareLength()
	double sqrlen = v1.squaredLength();
	checkClose(sqrlen , 14.0 , 1.0e-8 );

	//Vector3D::normalize()
	v1.normalize();
	checkClose( v1.x(), +0.267261241912424 , 1.0e-12 );
	checkClose( v1.y(), +0.534522483824849 , 1.0e-12 );
	checkClose( v1.z(), +0.801783725737273 , 1.0e-12 );
}

TestCase( TestVector3D ){
	Vector3D v0( 1.0, 1.5, 2.0 );
	checkEqual( 1.0, v0.x() );
	checkEqual( 1.5, v0.y() );
	checkEqual( 2.0, v0.z() );

	Vector3D v1( 1.0, 1.0, 1.0 );

	// +=
	v0 += v1;
	checkEqual( 2.0, v0.x() );
	checkEqual( 2.5, v0.y() );
	checkEqual( 3.0, v0.z() );

	// -=
	v0-=v1;
	checkEqual( 1.0, v0.x() );
	checkEqual( 1.5, v0.y() );
	checkEqual( 2.0, v0.z() );

	// *=
	v0*=2.0;
	checkEqual( 2.0, v0.x() );
	checkEqual( 3.0, v0.y() );
	checkEqual( 4.0, v0.z() );

	// /=
	v0/=4.0;
	checkEqual( 0.5, v0.x() );
	checkEqual( 0.75, v0.y() );
	checkEqual( 1.0, v0.z() ); 
}

TestCase( Vector3DCroosDotTriple ){
	Vector3D v1( 4.0 , 2.0 , 7.0 );
	Vector3D v2( 4.0 , 5.0 , 9.0 );
	Vector3D v3( 1.0 , 8.0 , 3.0 );

	// cross
	Vector3D t1 = cross( v1 , v2 );
	checkEqual( t1.x() , -17.0 );
	checkEqual( t1.y() , -8.0 );
	checkEqual( t1.z() , 12.0 );

	// dot
	double inner = dot( v1 , v2 );
	checkEqual( inner , 89.0 );

	// triple
	double trip = triple( v1 , v2 , v3 );
	checkEqual( trip , -45.0 );
}

TestCase( Vector3DIsEqualOperator ){
	Vector3D v1( 1.0 , -3.4 , 2.5 );
	Vector3D v2( 1.0 , -3.4 , 2.5 );
	Vector3D v3( 1.0 , -3.4 , 9.0 );

	// operator=
	check( v1==v2 );
	check( v1!=v3 );
	check( nullVector3D()==nullVector3D() );
}

TestCase(FileSystemTest)
{
	string directoryName = "Mordor";

	createDirectory(directoryName);
	check(checkPathExists(directoryName));

	deletePath(directoryName);
	check(!checkPathExists(directoryName));
}

TestCase(ProgramOptionsTest)
{
	ProgramOptions::OptionsDescription desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("simulation", ProgramOptions::value<std::string>(), "simulation's name")
		("root", ProgramOptions::value<std::string>(), "simulation's root folder")
	;

	int argc = 3;
	const char * argv[] = { "myProgramName", "--simulation=The Lord of the Rings", "--root=Mordor" };

	ProgramOptions::VariablesMap vm = parseCommandLine(argc, argv, desc);

	checkEqual(vm.count("simulation"), 1);
	checkEqual(vm.count("root"), 1);
	checkEqual(vm.count("orcs"), 0);

	checkEqual(vm["simulation"].as<string>(), "The Lord of the Rings");
	checkEqual(vm["root"].as<string>(), "Mordor");
}

TestCase(NamedTest)
{
	string defaultName = "Nameless";
	string name = "Rohan";
	Named::NamedCompare namedCompareObject;

	Named named1;
	Named named2("Rohan");

	checkEqual(named1.getName(), defaultName);
	checkEqual(named2.getName(), name);

	named1.setName(name);

	checkEqual(named1.getName(), name);

	check(defaultName < name);
	check(namedCompareObject(defaultName, name));
}

int f(int i)
{
	return 3 * i;
}

double f(double j)
{
	return 5.6 * j;
}

struct fVisitor : public staticVisitor<>
{
	void operator()(int & i) const
	{
		i = f(i);
	}

	void operator()(double & i) const
	{
		i = f(i);
	}
};

TestCase(VariantTest)
{
	Variant<int, double> myVariant;
	int intValue = 5;
	int intAnswer = f(intValue);
	double doubleValue = 9.8;
	double doubleAnswer = f(doubleValue);

	myVariant = intValue;
	applyVisitor( fVisitor(), myVariant );
	checkEqual(getVariant<int>(myVariant), intAnswer);

	myVariant = doubleValue;
	applyVisitor(fVisitor(), myVariant);
	checkEqual(getVariant<double>(myVariant), doubleAnswer);
}

TestCase(type_list_identity_Test)
{
	check((
		std::is_same<
			type_list<char, char, int, double>::identity,
			type_list<char, char, int, double>
		>::value
	));
}

TestCase(type_list_append_and_prepend_Test)
{
	check((
		std::is_same<
			type_list<char, char, int>::append<int>,
			type_list<char, char, int, int>
		>::value
	));

	check((
		std::is_same<
			type_list<char, char, int>::prepend<double>,
			type_list<double, char, char, int>
		>::value
	));
}

TestCase(type_list_contains_and_has_repeated_types_and_is_empty_Test)
{
	check((type_list<double, int>::contains<double>));
	check(!(type_list<double, int>::contains<char>));
	check((type_list<double, int>::contains<double, double, int>));
	check(!(type_list<double, int>::contains<double, double, bool, int>));

	check(!(type_list<>::has_repeated_types));
	check(!(type_list<double>::has_repeated_types));
	check(!(type_list<double, char>::has_repeated_types));
	check((type_list<double, double>::has_repeated_types));
	
	check(!(type_list<double, int>::is_empty));
	check((type_list<>::is_empty));
}

TestCase(type_list_size_Test)
{
	std::size_t size1 = type_list<int, double, double, int, char, bool>::size;
	checkEqual(size1, 6);

	std::size_t size2 = type_list<>::size;
	checkEqual(size2, 0);
}

TestCase(type_list_get_Test)
{
	check((
		std::is_same<
			type_list<char, int>::get<0>,
			char
		>::value
	));

	check((
		std::is_same<
			type_list<char, int>::get<1>,
			int
		>::value
	));

	// Uncomment the following lines to get compilation errors:
	// check((
	// 	std::is_same<
	// 		type_list<char, int>::get<2>,
	// 		int
	// 	>::value
	// ));
}

TestCase(type_list_append_if_new_types_Test)
{
	check((
		std::is_same<
			type_list<char, int>::append_if_new_types<char, double, int, bool>,
			type_list<char, int, double, bool>
		>::value
	));

	check((
		std::is_same<
			type_list<int, double>::append_if_new_types<>,
			type_list<int, double>
		>::value
	));

	check((
		std::is_same<
			type_list<int, double>::append_if_new_types<int>,
			type_list<int, double>
		>::value
	));

	check((
		std::is_same<
			type_list<int, double>::append_if_new_types<int, char, double>,
			type_list<int, double, char>
		>::value
	));

	check((
		std::is_same<
			type_list<>::append_if_new_types<int, double, double, char>,
			type_list<int, double, char>
		>::value
	));
}

TestCase(type_list_concatenate_Test)
{
	check((
		std::is_same<
			type_list<>::concatenate< type_list<int, int, bool, int> >,
			type_list<int, int, bool, int>
		>::value
	));

	check((
		std::is_same<
			type_list<char, int>::concatenate< type_list<int, int, bool, int> >,
			type_list<char, int, int, int, bool, int>
		>::value
	));

	check((
		std::is_same<
			type_list<char, int>::concatenate< type_list<> >,
			type_list<char, int>
		>::value
	));
}

TestCase(make_unique_type_list_Test)
{
	check((
		std::is_same<
			make_unique_type_list<int, int, double, int>,
			type_list<int, double>
		>::value
	));

	check((
		std::is_same<
			make_unique_type_list<int, int, double, int, double, char, double>,
			type_list<int, double, char>
		>::value
	));
}

TestCase(specialize_from_list_Test)
{
	check((
		std::is_same<
			type_list<int, double, double, char>::specialize<type_list>,
			type_list<int, double, double, char>
		>::value
	));

	check((
		std::is_same<
			type_collection<int, double, double, int, int, char>::specialize<type_list>,
			type_list<int, double, char>
		>::value
	));
}

TestCase(type_collection_identity_Test)
{
	check((
		std::is_same<
			type_collection<char, char, int, double>::identity,
			type_collection<char, char, int, double>
		>::value
	));
}

TestCase(type_collection_contains_Test)
{
	check((type_collection<double, int>::contains<double>));
	check(!(type_collection<double, int>::contains<char>));
}

TestCase(type_collection_is_empty_Test)
{
	check(!(type_collection<double, int>::is_empty));
	check((type_collection<>::is_empty));
}

TestCase(type_collection_size_Test)
{
	std::size_t size1 = type_collection<int, double, double, int, char, bool>::size;
	checkEqual(
		size1,
		4
	);

	std::size_t size2 = type_collection<>::size;
	checkEqual(
		size2,
		0
	);
}

TestCase(type_collection_is_superset_of_Test)
{
	check((
		type_collection<int, int, double, char>::is_superset_of< type_collection<int, double, double, double> >
	));
	check((
		type_collection<int, int, double, char>::is_superset_of< type_collection<> >
	));
	check(!(
		type_collection<>::is_superset_of< type_collection<int> >
	));
	check(!(
		type_collection<int, double>::is_superset_of< type_collection<int, char> >
	));
}

TestCase(type_collection_is_subset_of_Test)
{
	check((
		type_collection<int, double, double, double>::is_subset_of< type_collection<int, int, double, char> >
	));
	check((
		type_collection<>::is_subset_of< type_collection<int, int, double, char> >
	));
	check(!(
		type_collection<int>::is_subset_of< type_collection<> >
	));
	check(!(
		type_collection<int, char>::is_subset_of< type_collection<int, double> >
	));
}

TestCase(type_collection_is_equal_to_Test)
{
	check((
		type_collection<int, double, double>::is_equal_to< type_collection<int, int, double> >
	));
	check((
		type_collection<>::is_equal_to< type_collection<> >
	));
	check(!(
		type_collection<int, double, double>::is_equal_to< type_collection<int, char, double> >
	));
}

TestCase(bool_type_Test)
{
	check((
			bool_type<true>::value
		));

	check(!(
			bool_type<false>::value
		));
}