#define BOOST_TEST_MODULE JSONLibTest

// JSONLib
#include <json.hpp>

// UtilsLib
#include <Test.hpp>

using namespace psin;

TestCase(json_Test)
{
	using namespace nlohmann;

	json j = {
		{"pi", 3.141},
		{"happy", true},
		{"name", "Niels"},
		{"nothing", nullptr},
		{"answer", {
			{"everything", 42}
		}},
		{"list", {1, 0, 2}},
		{"object", {
			{"currency", "USD"},
			{"value", 42.99}
		}}
	};

	double pi_value = j["pi"];
	auto happy_value = j["happy"];
	auto list_value = j["list"];

	checkEqual(pi_value, 3.141);
	checkEqual(happy_value, true);
	checkEqual(list_value[1], 0);
}