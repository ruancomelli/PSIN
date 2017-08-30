#ifndef SCRIPT_SYSTEM_PARSER_HPP
#define SCRIPT_SYSTEM_PARSER_HPP

#include <fstream>
#include <SSParserNode.hpp>

namespace psin
{

typedef std::ifstream InputFile;

class Parser{
public:
	Parser( const string& scriptFilename );

	ParserNodePtr getRoot();

	virtual ~Parser();

protected:
	ParserNodePtr root;

private:
	ParserNodePtr readParserNode( InputFile& scriptFile, string& type );
}; //class Parser;

typedef shared_ptr< Parser > ParserPtr;

} //namespace psin;

#endif