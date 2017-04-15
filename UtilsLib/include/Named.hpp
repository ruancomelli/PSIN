#ifndef NAMED_H
#define NAMED_H

#include <string>

class Named{
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

#endif // NAMED_H
