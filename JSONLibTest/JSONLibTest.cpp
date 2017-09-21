#define BOOST_TEST_MODULE JSONLibTest

#include <fstream>
#include <iostream>
#include <string>

// JSONLib
#include <json.hpp>

// UtilsLib
#include <Test.hpp>

using namespace psin;
using std::ifstream;
using std::ofstream;
using std::string;

TestCase(basic_json_Test)
{
	string filename = "file.json";

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

	auto happy_value = j["happy"];
	auto list_value = j["list"];

	checkEqual(j["pi"], 3.141);
	checkEqual(happy_value, true);
	checkEqual(list_value[1], 0);

	ofstream out(filename);
	out << j.dump(4);
	out.close();

	ifstream in(filename);
	json j2;
	in >> j2;

	checkEqual(j2["name"], "Niels");
	checkEqual(j2["answer"]["everything"], 42);

	json obj = j2["object"];

	checkEqual(obj["currency"], "USD");
	checkEqual(obj["value"], 42.99);	

	json j3;
	j3["one"]["two"] = 3;
	checkEqual(j3["one"]["two"], 3);
}

namespace to_and_from_json_Test_namespace {

	struct A
	{
		void set(const int x){ this->x = x; }
		int get() const { return this->x; }
		double z;
		string name;

	private:
		int x;
	};

    void to_json(json& j, const A& a) {
        j = json{
        	{"name", a.name}, 
        	{"x", a.get()}, 
        	{"z", a.z}
        };
    }

    void from_json(const json& j, A& a) {
        a.name = j.at("name").get<std::string>();
        a.set( j.at("x").get<int>() );
        a.z = j.at("z").get<double>();
    }

} // to_and_from_json_Test_namespace

TestCase(to_and_from_json_Test)
{
	using namespace to_and_from_json_Test_namespace;

	A a1;
	A a2;
	json j;

	a1.name = "a1";
	a1.z = 3.14;
	a1.set(10);

	j = a1;

	a2 = j;

	checkEqual(a2.name, "a1");
	checkEqual(a2.z, 3.14);
	checkEqual(a2.get(), 10);
}

TestCase(json_array_Test)
{
	json j{
		{"Position", {1.0, 2.1, 3.2}}
	};

	json child{1.0, 2.1, 3.2};

	checkEqual(j["Position"], child);
	checkEqual(child.size(), 3);
	checkEqual(child[0], 1.0);
	checkEqual(child[1], 2.1);
	checkEqual(child[2], 3.2);

	std::vector<double> v = j["Position"];
	std::vector<double> v2{1.0, 2.1, 3.2};
	check(v == v2);
}

TestCase(json_merge_Test)
{
	json j1{
		{"Mass", 81.3},
		{"Color",
			{
				{"R", 5},
				{"G", 55},
				{"B", 200}
			}
		}
	};

	json j2{
		{"Position",
			{
				1.0, 2.3, 4.5
			}
		}
	};

	json j3{
		{"Mass", 81.3},
		{"Color",
			{
				{"R", 5},
				{"G", 55},
				{"B", 200}
			}
		},
		{"Position",
			{
				1.0, 2.3, 4.5
			}
		}
	};

	checkEqual(merge(j1, j2), j3);

	std::vector<json> v{j1, j2};
	checkEqual(merge(v), j3);
}

TestCase(json_type_checkers_Test)
{
	{
		json j{
			{"Dark Lord", "Sauron"}
		};
		check(j.is_object());
	}
	{
		json j{"Gandalf"};
		check(j.is_array());
	}
	{
		json j = "Tom Bombadil";
		check(j.is_string());
	}
	{
		json j{
			"Frodo", 
			"Sam",
			"Pippin", 
			"Merry"
		};
		check(j.is_array());
	}
}

TestCase(iterate_over_json_Test)
{
	{
		json shire{
			"Frodo", 
			"Sam", 
			"Pippin", 
			"Merry"
		};

		std::vector<std::string> fellowshipHobbits;
		std::vector<std::string> halflings{
			"Frodo", 
			"Sam", 
			"Pippin", 
			"Merry"
		};

		for(auto& hobbit : shire)
		{
			fellowshipHobbits.push_back(hobbit);
		}


		check( fellowshipHobbits == halflings );
	}
}