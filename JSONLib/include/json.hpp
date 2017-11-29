#ifndef PSIN_JSON_HPP
#define PSIN_JSON_HPP

#include <json_nlohmann.hpp>

// Standard
#include <string>

namespace psin {

using json = nlohmann::json;

json read_json(const std::string & filename);
json merge(const json & lhs, const json & rhs);
json merge(json && lhs, const json & rhs);
void merge_into(json& lhs, const json & rhs);

template<typename JsonContainer>
json merge(const JsonContainer & container);

} // psin

#include <json.tpp>

#endif // PSIN_JSON_HPP
