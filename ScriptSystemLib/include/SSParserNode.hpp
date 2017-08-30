#ifndef SCRIPT_SYSTEM_PARSER_NODE_HPP
#define SCRIPT_SYSTEM_PARSER_NODE_HPP

#include <list>
#include <string>
#include <SharedPointer.hpp>

namespace psin
{

using std::string;

class ParserNode{
public:
	typedef shared_ptr< ParserNode > ParserNodePtr;
	typedef std::list< ParserNodePtr > ParserNodePtrList;
	typedef ParserNodePtrList::iterator ParserNodePtrIterator;

	ParserNode( const string& type, const string& name, double value );

	string& getType();
	string  getName();
	string& getName(int);
	double& getValue();
	bool getBool();
	void addChild( ParserNodePtr parserNode );
	int getNumberOfChildren();
	ParserNodePtr getChildByType( const string& parserNodeType, bool require = false );
	ParserNodePtr getChildByName( const string& parserNodeName, bool require = false );
	ParserNodePtr getChild( const string& parserNodeRef, bool require = false );
	ParserNodePtrList& getChildren(){
		return this->children;
	}
	double getChildValue( const string& parserNodeType, double defaultValue = 0.0 );

	virtual ~ParserNode();

protected:
	string type;
	string name;
	double value;
	ParserNodePtrList children;
}; //class ParserNode;

typedef ParserNode::ParserNodePtr ParserNodePtr;
typedef ParserNode::ParserNodePtrList ParserNodePtrList; 
	
} //namespace psin;

#endif