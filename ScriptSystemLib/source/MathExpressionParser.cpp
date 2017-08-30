#include <MathExpressionParser.hpp>

// UtilsLib
#include <Mathematics.hpp>
#include <StringUtils.hpp>

namespace psin
{

MathExpressionParser::MathExpressionParser( const string& expression ){
	this->parser.DefineVar( "x", &this->x );
	this->parser.DefineVar( "y", &this->y );
	this->parser.DefineVar( "z", &this->z );
	this->parser.DefineVar( "t", &this->t );
	this->parser.DefineConst( "pi", pi<double>() );
	std::string lowerExpression = expression;
	psin::toLower( lowerExpression );
	this->parser.SetExpr( lowerExpression );
}

double MathExpressionParser::compute( double x, double y, double z, double t ){
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
	return this->parser.Eval();
}

MathExpressionParser::~MathExpressionParser(){}

} //namespace psin;