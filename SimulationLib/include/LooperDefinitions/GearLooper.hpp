#ifndef GEAR_LOOPER_HPP
#define GEAR_LOOPER_HPP

// JSONLib
#include <json.hpp>

// Standard
#include <utility>

namespace psin {
	
struct GearLooper
{
	template<typename Index, typename Value>
	class Time
	{
	public:
		using index_type = Index;
		using value_type = Value;

		Time(const Value & initialTime, const Value & timeStep, const Value & finalTime);

		void start();
		void update();
		bool end() const;

		std::pair<index_type, value_type> as_pair() const;
		json as_json() const;

	private:
		index_type timeIndex;
		value_type time;

		value_type initialTime;
		value_type timeStep;
		value_type finalTime;
	};
};

} // psin

#include <LooperDefinitions/GearLooper.tpp>

#endif // GEAR_LOOPER_HPP
