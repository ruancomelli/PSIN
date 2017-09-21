#ifndef NAMED_HPP
#define NAMED_HPP

// UtilsLib
#include <json.hpp>
#include <string.hpp>

namespace psin {

class Named
{
public:
	using string = std::string;

	static const string defaultName;

	struct NamedCompare
	{
		bool operator()( const Named & left, const Named & right ) const
		{ return left.getName() < right.getName();}
	};

	Named();
	Named(const string & name);

	void setName(const string & name);
	string getName(void) const;

private:
	string name;
}; //class Named

bool operator<(const Named & left, const Named & right);

void from_json(const json & j, Named & named);
void to_json(json & j, const Named & named);

} // psin

#endif // NAMED_HPP
