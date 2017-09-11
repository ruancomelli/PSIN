#include <SSParserNode.hpp>

// UtilsLib
#include <string.hpp>

// Standard
#include <stdexcept>

namespace psin
{

ParserNode::ParserNode( const string& type, const string& name, double value )
	: type( type ), name( name ), value( value ){}

string& ParserNode::getType(){
	return this->type;
}

string ParserNode::getName(){
	string name = this->name;
	toUpper(name);
	return name;
}

string& ParserNode::getName(int lower){
	return this->name;
}

double& ParserNode::getValue(){
	return this->value;
}

bool ParserNode::getBool(){
	if( this->name == "true" or this->name == "TRUE" ){
		return true;
	}else if( this->name == "false" or this->name == "FALSE" ){
		return false;
	}
	throw std::runtime_error( "ParserNode " + this->type + " doesn't have a bool parameter!" );
}

void ParserNode::addChild( ParserNodePtr parserNode ){
	this->children.push_back( parserNode );
}

int ParserNode::getNumberOfChildren(){
	return this->children.size();
}

ParserNodePtr ParserNode::getChildByType( const string& parserNodeType, bool require ){
	string type = parserNodeType;
	toUpper( type );
	for( ParserNodePtrList::iterator child = this->children.begin();
		child != this->children.end(); ++child )
	{
		if( ( *child )->type == type ){
			return *child;
		}
	}
	if( require ){
		throw std::runtime_error( "ParserNode with type equal to \"" + parserNodeType + "\" not found!" );
	}
	return ParserNodePtr();
}

ParserNodePtr ParserNode::getChildByName( const string& parserNodeName, bool require ){
	string name = parserNodeName;
	toUpper( name );
	for( ParserNodePtrList::iterator child = this->children.begin();
		child != this->children.end(); ++child )
	{
		string oName = ( *child )->name;
		toUpper(oName);
		if( oName == name ){
			return *child;
		}
	}
	if( require ){
		throw std::runtime_error( "ParserNode with name equal to \"" + parserNodeName + "\" not found!" );
	}
	return ParserNodePtr();
}

ParserNodePtr ParserNode::getChild( const string& parserNodeRef, bool require ){
	string ref = parserNodeRef;
	toUpper( ref );
	ParserNodePtr child = this->getChildByType( ref );
	if( child.get() ){
		return child;
	}
	child = this->getChildByName( ref );
	if( !child.get() ){
		if( require ){
			throw std::runtime_error( "ParserNode with type or name equal to \"" + parserNodeRef + "\" not found!" );
		}
	}
	return child;
}

double ParserNode::getChildValue( const string& parserNodeType, double defaultValue ) {
	ParserNodePtr child = this->getChildByType( parserNodeType );
	if( !child.get() ){
		return defaultValue;
	}
	return child->getValue();
}

ParserNode::~ParserNode(){}

} //namespace psin;
