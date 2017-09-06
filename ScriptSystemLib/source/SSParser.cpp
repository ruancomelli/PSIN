#include <SSParser.hpp>

// UtilsLib
#include <FileSystem.hpp>
#include <StringUtils.hpp>

namespace psin
{

using std::string;
using std::runtime_error;

Parser::Parser( const string& scriptFilename )
{
	if ( !checkPathExists(scriptFilename) ){
		throw runtime_error( "ScriptSystem::Parser - File " + scriptFilename + " was not found" );
	}
	
	InputFile scriptFile( scriptFilename.c_str() );
	this->root = make_shared<ParserNode>("root", "root", 0.0f);

	string type;
	scriptFile >> type;
	while( type == "//" or (type[ 0 ] == '/' and type[ 1 ] == '/') ){
		getline( scriptFile, type );
		scriptFile >> type;
	}
	while( !scriptFile.eof() ){
		this->root->addChild( this->readParserNode( scriptFile, type ) );
	}
}

ParserNodePtr Parser::getRoot(){
	return this->root;
}

Parser::~Parser(){}

ParserNodePtr Parser::readParserNode( InputFile& scriptFile, string& type ){
	string name;
	scriptFile >> name;
	bool isBracketOpen = false;
	if( name[ name.size() - 1 ] == '{' ){
		name.erase( name.size() - 1 );
		isBracketOpen = true;
	}

	double value = double( atof( name.c_str() ) );

	toUpper( type );
	//toUpper( name );
	ParserNodePtr parserNode( new ParserNode( type, name, value ) );
	scriptFile >> type;
	if( isBracketOpen or type == "{" ){
		if( !isBracketOpen ){
			scriptFile >> type;
		}
		while( type != "}" ){
			parserNode->addChild( this->readParserNode( scriptFile, type ) );
		}
		scriptFile >> type;
	}
	while( type == "//" or (type[ 0 ] == '/' and type[ 1 ] == '/') ){
		getline( scriptFile, type );
		scriptFile >> type;
	}
	return parserNode;
}

} //namespace psin;