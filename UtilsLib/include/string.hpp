#ifndef STRING_HPP
#define STRING_HPP

#include <string>

namespace psin {

using std::string;

int stringCompare(const string & left, const string & right, const bool caseSensitive=false);

void toUpper(string & s);
void toLower(string & s);

string asUpper(string s);
string asLower(string s);

} // psin

#endif
