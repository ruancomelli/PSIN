#ifndef PSIN_JSON_HPP
#define PSIN_JSON_HPP

#include <json_nlohmann.hpp>

// Standard
#include <string>

namespace psin {

using json = nlohmann::json;

json read_json(const std::string & filename);
json merge(const json & lhs, const json & rhs);

} // psin

#endif // PSIN_JSON_HPP
