#ifndef MATH_EXPRESSION_PARSER_HPP
#define MATH_EXPRESSION_PARSER_HPP

#include <string>

#include <muParser.h>
// #include <Constants.h>
#include <SharedPointer.hpp>

namespace psin{

using std::string;

class MathExpressionParser{
public:
	MathExpressionParser( const string& expression );

	double compute( double x, double y, double z, double t = 0.0 );

	virtual ~MathExpressionParser();

protected:
	mu::Parser parser;
	double x;
	double y;
	double z;
	double t;
}; //class MathExpressionParser;

typedef shared_ptr< MathExpressionParser > MathExpressionParserPtr;

} //namespace psin;

#endif
