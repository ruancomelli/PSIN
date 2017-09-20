#define BOOST_TEST_MODULE TestModule

// Standard
#include <tuple>
#include <type_traits>

// UtilsLib
#include <Any.hpp>
#include <FileSystem.hpp>
#include <Foreach.hpp>
#include <Mathematics.hpp>
#include <Named.hpp>
#include <NamedType.hpp>
#include <NamedGroup.hpp>
#include <ProgramOptions.hpp>
#include <SharedPointer.hpp>
#include <string.hpp>
#include <Test.hpp>
#include <UniquePointer.hpp>
#include <Variant.hpp>
#include <Vector.hpp>
#include <Vector3D.hpp>
#include <metaprogramming.hpp>

// using namespace std;
using namespace psin;
using namespace mp;

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
	string s = "The Winter is coming.";

	Any any = i;
	checkEqual(any_cast<int>(any), i);

	any = d;
	checkEqual(any_cast<double>(any), d);

	any = s;
	checkEqual(any_cast<string>(any), s);

	std::vector< Any > many;
	many.push_back(i);
	many.push_back(d);
	many.push_back(s);

	checkEqual(any_cast<int>(many[0]), i);
	checkEqual(any_cast<double>(many[1]), d);
	checkEqual(any_cast<string>(many[2]), s);
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

// ----- shared_ptr -----
TestCase(shared_ptr_Test) {
	shared_ptr<Vector3D> v0( new Vector3D );

	(*v0).x() = 1.0;
	(*v0).y() = 2.0;
	(*v0).z() = 3.0;
	
	shared_ptr<Vector3D> v1(new Vector3D(*v0));

	checkEqual((*v0).x(), v1->x());
	checkEqual((*v0).y(), v1->y());
	checkEqual((*v0).z(), v1->z());
}

TestCase(unique_ptr_Test)
{
	unique_ptr<Vector3D> v0( new Vector3D );

	(*v0).x() = 1.0;
	(*v0).y() = 2.0;
	(*v0).z() = 3.0;
	
	unique_ptr<Vector3D> v1 = make_unique<Vector3D>( *v0 );

	checkEqual((*v0).x(), v1->x());
	checkEqual((*v0).y(), v1->y());
	checkEqual((*v0).z(), v1->z());
}

// string
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

TestCase(Vector3D_access_operator_Test)
{
	double tolerance = 1e-12;
	double x = 5;
	double y = -3.14;
	double z = 0.12;

	Vector3D v;

	v[0] = x;
	v[1] = y;
	v[2] = z;

	checkClose(v[0], x, tolerance);
	checkClose(v[1], y, tolerance);
	checkClose(v[2], z, tolerance);
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

namespace Vector3D_json_Test_namespace {
	template<> const string NamedType<Vector3D>::name = "Vector3D";
} // Vector3D_json_Test_namespace

TestCase(Vector3D_json_Test)
{
	using namespace Vector3D_json_Test_namespace;

	{
		json j;
		j[NamedType<Vector3D>::name] = 0;
		checkEqual(j[NamedType<Vector3D>::name], 0);
	}
	{
		json j{3.14, 15.9, 11.5};
		Vector3D v = j;
		json j2 = v;
		checkEqual(v, Vector3D(3.14, 15.9, 11.5));
		checkEqual(j, j2);
	}
	{
		json j{
			{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0}
		};
		vector<Vector3D> v = j;
		vector<Vector3D> v2{
			{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0}
		};
		json j2 = v;
		check(v == v2);
		checkEqual(j, j2);
	}
	{
		json j{
			{"Position", 
				{{1.0, 2.0, 3.0},
				{4.0, 5.0, 6.0}}
			}
		};
		vector<Vector3D> v = j["Position"];
		vector<Vector3D> v2{
			{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0}
		};
		json j2;
		j2["Position"] = v;
		check(v == v2);
		checkEqual(j, j2);
	}
	{
		json j{
			{"Position", 
				{{1.0, 2.0, 3.0},
				{4.0, 5.0, 6.0}}
			},
			{"Orientation", 
				{{7.0, 8.0, 9.0},
				{10.0, 11.0, 12.0}}
			}
		};
		vector<Vector3D> v = j["Position"];
		vector<Vector3D> v2 = j["Orientation"];
		vector<Vector3D> v3{
			{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0}
		};
		vector<Vector3D> v4{
			{7.0, 8.0, 9.0},
			{10.0, 11.0, 12.0}
		};
		json j2;
		j2["Position"] = v;
		j2["Orientation"] = v2;
		check(v == v3);
		check(v2 == v4);
		checkEqual(j, j2);
	}
}


// ---- FileSystem ----

TestCase(FileSystemTest)
{
	string directoryName = "Mordor";

	createDirectory(directoryName);
	check(checkPathExists(directoryName));

	deletePath(directoryName);
	check(!checkPathExists(directoryName));
}

TestCase(program_options_Test)
{
	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("simulation", program_options::value<std::string>(), "simulation's name")
		("root", program_options::value<std::string>(), "simulation's root folder")
	;

	int argc = 3;
	char * argv[] = { (char*) "myProgramName", (char*) "--simulation=The Lord of the Rings", (char*) "--root=Mordor" };

	program_options::variables_map vm = parseCommandLine(argc, argv, desc);

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

namespace NamedType_Test_namespace {
	struct A 
	{};

	template<typename T>
	struct B
	{};

	template<> const std::string NamedType<A>::name("A");
	template<> const std::string NamedType<B<int>>::name = "B_int";
} // NamedType_Test_namespace

TestCase(NamedType_Test)
{
	using namespace NamedType_Test_namespace;

	check(NamedType<A>::name == "A");
	check(NamedType<B<int>>::name == "B_int");
}

namespace NamedGroup_Test_namespace {
	template<typename T>
	struct A 
	{};

	template<> const std::string NamedGroup<A>::name = "A";

	template<typename T, typename U>
	struct B
	{};

	template<> const std::string NamedGroup<B>::name = "B";
} // NamedType_Test_namespace

TestCase(NamedGroup_Test)
{
	using namespace NamedGroup_Test_namespace;

	check(NamedGroup<A>::name == "A");
	check(NamedGroup<B>::name == "B");
}

int f(int i)
{
	return 3 * i;
}

double f(double j)
{
	return 5.6 * j;
}

struct fVisitor : public variant::static_visitor<>
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
	variant::variant<int, double> myVariant;
	int intValue = 5;
	int intAnswer = f(intValue);
	double doubleValue = 9.8;
	double doubleAnswer = f(doubleValue);

	myVariant = intValue;
	variant::apply_visitor( fVisitor(), myVariant );
	checkEqual(variant::get<int>(myVariant), intAnswer);

	myVariant = doubleValue;
	variant::apply_visitor(fVisitor(), myVariant);
	checkEqual(variant::get<double>(myVariant), doubleAnswer);
}

TestCase(bool_constant_Test)
{
	check((
			bool_constant<true>::value
		));

	check(!(
			bool_constant<false>::value
		));
}

TestCase(metafunction_Test)
{
	check((
		std::is_same<
			metafunction<double>::type,
			double
		>::value
	));
}

TestCase(get_Test)
{
	check((
		std::is_same<
			mp::get<1, type_list<int, double, double> >::type,
			double
		>::value
	));

	check((
		std::is_same<
			mp::get<2, std::tuple<int, double, char> >::type,
			char
		>::value
	));
}

TestCase(concatenate_Test)
{
	check((
		std::is_same<
			mp::concatenate< type_list<int, double>, type_list<double, char, char, bool> >::type,
			type_list<int, double, double, char, char, bool>
		>::value
	));

	check((
		std::is_same<
			mp::concatenate< type_list<int, double>, type_list<> >::type,
			type_list<int, double>
		>::value
	));

	check((
		std::is_same<
			mp::concatenate< std::tuple<int, double>, std::tuple<double, char, char, bool> >::type,
			std::tuple<int, double, double, char, char, bool>
		>::value
	));

	check((
		std::is_same<
			mp::concatenate< index_sequence<2, 3>, index_sequence<3, 0, 0, 1> >::type,
			index_sequence<2, 3, 3, 0, 0, 1>
		>::value
	));
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
	size_t size1 = type_list<int, double, double, int, char, bool>::size;
	checkEqual(size1, 6);

	size_t size2 = type_list<>::size;
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
	size_t size1 = type_collection<int, double, double, int, char, bool>::size;
	checkEqual(
		size1,
		4
	);

	size_t size2 = type_collection<>::size;
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

TestCase(make_constant_index_sequence_Test)
{
	check((
		std::is_same<
			detail::make_constant_index_sequence<>::type,
			std::index_sequence<>
		>::value
	));

	check((
		std::is_same<
			detail::make_constant_index_sequence<0>::type,
			std::index_sequence<>
		>::value
	));

	check((
		std::is_same<
			detail::make_constant_index_sequence<2>::type,
			std::index_sequence<0, 0>
		>::value
	));

	check((
		std::is_same<
			detail::make_constant_index_sequence<3, 5>::type,
			std::index_sequence<5, 5, 5>
		>::value
	));
}

TestCase(format_indexes_based_on_limits_Test)
{
	check((
		std::is_same<
			detail::format_indexes_based_on_limits<
				std::index_sequence<>,
				std::index_sequence<>
			>::type,
			std::index_sequence<>
		>::value
	));
	size_t remainder1 = detail::format_indexes_based_on_limits<
			std::index_sequence<>,
			std::index_sequence<>
		>::remainder;
	checkEqual(remainder1, 0);

	check((
		std::is_same<
			detail::format_indexes_based_on_limits<
				std::index_sequence<7, 4, 1>,
				std::index_sequence<5, 5, 3>
			>::type,
			std::index_sequence<2, 0, 2>
		>::value
	));
	size_t remainder2 = detail::format_indexes_based_on_limits<
			std::index_sequence<7, 4, 1>,
			std::index_sequence<5, 5, 3>
		>::remainder;
	checkEqual(remainder2, 0);

	check((
		std::is_same<
			detail::format_indexes_based_on_limits<
				std::index_sequence<5, 4, 2>,
				std::index_sequence<5, 5, 3>
			>::type,
			std::index_sequence<0, 0, 0>
		>::value
	));
	size_t remainder3 = detail::format_indexes_based_on_limits<
			std::index_sequence<5, 5, 3>,
			std::index_sequence<5, 5, 3>
		>::remainder;
	checkEqual(remainder3, 1);
}

TestCase(last_combination_indexes_Test)
{
	check((
		std::is_same<
			detail::last_combination_indexes<
				type_list<int, double, double, char>,
				std::tuple<std::string>,
				std::tuple<int, char>,
				type_list<int, double, bool, char>
			>::type,
			std::index_sequence<3, 0, 1, 3>
		>::value
	));
}

TestCase(next_combination_indexes_Test)
{
	check((
		std::is_same<
			detail::next_combination_indexes<
				std::index_sequence<1, 3, 2>,
				std::index_sequence<3, 4, 5>
			>::type,
			std::index_sequence<2, 3, 2>
		>::value
	));

	check((
		std::is_same<
			detail::next_combination_indexes<
				std::index_sequence<2, 3, 2>,
				std::index_sequence<3, 4, 5>
			>::type,
			std::index_sequence<0, 0, 3>
		>::value
	));
}

TestCase(length_Test)
{
	size_t size1 = mp::length< type_list<int, double, double, char, bool> >::value;
	checkEqual(
		size1,
		5
	);

	size_t size2 = mp::length< std::tuple<double, bool> >::value;
	checkEqual(
		size2,
		2
	);

	size_t size3 = mp::length< std::tuple<> >::value;
	checkEqual(
		size3,
		0
	);
}

TestCase(iterate_generate_list_Test)
{
	check((
		std::is_same<
			detail::iterate_generate_list<
				std::index_sequence<0, 0, 0>,
				type_list<int, double, char>,
				type_list<size_t, double, std::string>,
				type_list<bool, char >
			>::type,
			type_list<
				type_list<int, size_t, bool>,
				type_list<double, size_t, bool>,
				type_list<char, size_t, bool>,
				type_list<int, double, bool>,
				type_list<double, double, bool>,
				type_list<char, double, bool>,
				type_list<int, std::string, bool>,
				type_list<double, std::string, bool>,
				type_list<char, std::string, bool>,

				type_list<int, size_t, char>,
				type_list<double, size_t, char>,
				type_list<char, size_t, char>,
				type_list<int, double, char>,
				type_list<double, double, char>,
				type_list<char, double, char>,
				type_list<int, std::string, char>,
				type_list<double, std::string, char>,
				type_list<char, std::string, char>
			>
		>::value
	));

	check((
		std::is_same<
			detail::iterate_generate_list<
				std::index_sequence<2, 0, 1>,
				type_list<int, double, char>,
				type_list<size_t, double, std::string>,
				type_list<bool, char>
			>::type,
			type_list<
				type_list<char, size_t, char>,
				type_list<int, double, char>,
				type_list<double, double, char>,
				type_list<char, double, char>,
				type_list<int, std::string, char>,
				type_list<double, std::string, char>,
				type_list<char, std::string, char>
			>
		>::value
	));
}

TestCase(combinatory_generate_combination_list_Test)
{
	check((
		std::is_same<
			combinatory::generate_combination_list<
				type_list<int, double, char>,
				type_list<size_t, double, std::string>,
				type_list<bool, char>
			>::type,
			type_list<
				type_list<int, size_t, bool>,
				type_list<double, size_t, bool>,
				type_list<char, size_t, bool>,
				type_list<int, double, bool>,
				type_list<double, double, bool>,
				type_list<char, double, bool>,
				type_list<int, std::string, bool>,
				type_list<double, std::string, bool>,
				type_list<char, std::string, bool>,

				type_list<int, size_t, char>,
				type_list<double, size_t, char>,
				type_list<char, size_t, char>,
				type_list<int, double, char>,
				type_list<double, double, char>,
				type_list<char, double, char>,
				type_list<int, std::string, char>,
				type_list<double, std::string, char>,
				type_list<char, std::string, char>
			>
		>::value
	));
}

namespace purge_Test_namespace {
	template<typename T>
	struct test : std::false_type
	{};

	template<>
	struct test<bool> : std::true_type
	{};

	template<>
	struct test<int> : std::true_type
	{};
} // purge_Test_namespace

TestCase(purge_Test)
{
	using namespace purge_Test_namespace;

	check((
		std::is_same<
			typename mp::purge::apply<
				type_list<>,
				test
			>::type,
			type_list<>
		>::value
	));

	check((
		std::is_same<
			typename mp::purge::apply<
				type_list<int, char, int, double, bool, bool, int, char>,
				test
			>::type,
			type_list<int, int, bool, bool, int>
		>::value
	));
}

namespace visit_Test_namespace {
	struct A
	{
		static int x;
	};
	int A::x = 0;

	struct B
	{
		static double a;
		static double b;
		static double c;	
	};
	double B::a = 1;
	double B::b = 2;
	double B::c = 0;

	template<typename T>
	struct visitor;

	template<>
	struct visitor<A>
	{
		static void call()
		{
			A::x = 1;
		}

		template<typename T>
		static void call(T arg)
		{
			A::x = 1;
		}
	};

	template<>
	struct visitor<B>
	{
		static void call()
		{
			B::c = B::a + B::b;
		}

		static void call( const std::tuple<double, double, double> & arg )
		{
			B::a = std::get<0>(arg);
			B::b = std::get<1>(arg);
			B::c = std::get<2>(arg);
		}
	};
} // visit_Test_namespace

TestCase(visit_Test)
{
	using namespace visit_Test_namespace;

	checkEqual(A::x, 0);
	checkEqual(B::a, 1);
	checkEqual(B::b, 2);
	checkEqual(B::c, 0);

	mp::visit<
		type_list<A, B>,
		visitor
	>::call_same();

	checkEqual(A::x, 1);
	checkEqual(B::a, 1);
	checkEqual(B::b, 2);
	checkEqual(B::c, 3);

	auto arg = std::make_tuple(
			std::make_tuple(),
			std::make_tuple(
				-1.0, 3.14, 0.0
			)
		);

	mp::visit<
		type_list<A, B>,
		visitor
	>::call( arg );

	checkEqual(A::x, 1);
	checkEqual(B::a, -1.0);
	checkEqual(B::b, 3.14);
	checkEqual(B::c, 0.0);
}

TestCase(revert_Test)
{
	check((
		std::is_same<
			mp::revert< type_list<int, double, char, char, bool> >::type,
			type_list<bool, char, char, double, int>
		>::value
	));
}