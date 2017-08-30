#define BOOST_TEST_MODULE TestModule

#include <MathExpressionParser.hpp>
#include <Test.hpp>
#include <SSParser.hpp>

using namespace psin;

string tPath = string(PROJECT_PATH) + "/ScriptSystemLibTest/";

TestCase( TestParser ){
	ParserPtr file( new Parser( tPath + "test.example" ) );

	ParserNodePtr test4 = file->getRoot()->getChildByType( "test1" )->getChildByName( "2" )->getChild( "test3" )->getChild( "test4" );

	if( !test4.get() ){

	}

	check( 4 == test4->getValue() );
}

TestCase( MathExpressionParserTimeDependentTest ){
	std::string expression = "x*exp(t)";

	MathExpressionParser parser( expression );
	double x, y, z, t;
	
	t = 1.0;
	y = 0.0;
	z = 0.0;
	for( x = -10.0 ; x <= 10.0; x = x + 1.0 ){
		checkClose( x*exp(t) , parser.compute( x, y, z, t ), 1.0e-12 );
	}
	x = 1.0;
	checkClose( 1.0 , parser.compute( x, y, z ), 1.0e-12 );
}

TestCase( MathExpressionParserTest ){
	std::string expression = "sin(x^2)*y+ln(z)";

	MathExpressionParser parser( expression );
	double x, y, z;
	// Assuming the expression "expression" is the value function for the boundary b;
	// For each face on boundary b, pass its x, y and z centroid coordinates for the 
	//    parser's compute function;

	z = 2.0;
	for( x = -10.0, y = 5.0; x <= 10.0; x = x + 1.0, y = y - 0.5 ){
		checkClose( sin(x*x)*y + log(z), parser.compute( x, y, z ), 1.0e-12 );
	}
}

TestCase( MathExpressionParserDiscontinuousTest ){
	std::string expression = "(max(0.50000001-x,0)/(0.50000001-x))*x+(max(x-0.50000001,0)/(x-0.50000001))*x^2";

	MathExpressionParser parser( expression );
	for( double x = -10.0; x < 10.0; x += 0.01 ){
		if( x < 0.50000001 ) {
			checkClose( x, parser.compute( x, 0.0, 0.0 ), 1.0e-12 );
		}else{
			checkClose( x*x, parser.compute( x, 0.0, 0.0 ), 1.0e-12 );
		}
	}
}
//
//TestCase( TypeRequireTest ){
//	ParserPtr file( new Parser( "test.example" ) );
//
//	string error;
//	try{
//		ParserNodePtr nonExistent = file->getRoot()->getChildByType( "not_a_type", true );
//	}catch( std::runtime_error& e ){
//		error = e.what();
//	}
//
//	checkEqual( "ParserNode with type equal to \"not_a_type\" not found!", error );
//}
//
//TestCase( NameRequireTest ){
//	ParserPtr file( new Parser( "test.example" ) );
//
//	string error;
//	try{
//		ParserNodePtr nonExistent = file->getRoot()->getChildByName( "not_a_name", true );
//	}catch( std::runtime_error& e ){
//		error = e.what();
//	}
//
//	checkEqual( "ParserNode with name equal to \"not_a_name\" not found!", error );
//}
//
//TestCase( GeneralRequireTest ){
//	ParserPtr file( new Parser( "test.example" ) );
//
//	string error;
//	try{
//		ParserNodePtr nonExistent = file->getRoot()->getChild( "not_a_type_or_name", true );
//	}catch( std::runtime_error& e ){
//		error = e.what();
//	}
//
//	checkEqual( "ParserNode with type or name equal to \"not_a_type_or_name\" not found!", error );
//}
//
//TestCase( GetChildValueTest ){
//	ParserPtr file( new Parser( "test.example" ) );
//
//	checkClose( 3.14, file->getRoot()->getChildValue( "existent_value", 2.71 ), 1.0e-5 );
//	checkClose( 2.71, file->getRoot()->getChildValue( "non_existent_value", 2.71 ), 1.0e-5 );
//}