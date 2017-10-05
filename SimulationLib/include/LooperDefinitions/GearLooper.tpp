#ifndef GEAR_LOOPER_TPP
#define GEAR_LOOPER_TPP

#include <string.hpp>

namespace psin {

template<typename Index, typename Value>
GearLooper::Time<Index, Value>::Time(const Value & initialTime, const Value & timeStep, const Value & finalTime)
	: timeIndex(0),
	time(initialTime),
	initialTime(initialTime),
	timeStep(timeStep),
	finalTime(finalTime)
{}

template<typename Index, typename Value>
void GearLooper::Time<Index, Value>::start()
{
	this->time = this->initialTime;
	this->timeIndex = Index(0);
}

template<typename Index, typename Value>
void GearLooper::Time<Index, Value>::update()
{
	this->time += this->timeStep;
	++this->timeIndex;
}

template<typename Index, typename Value>
bool GearLooper::Time<Index, Value>::end() const
{
	return this->time >= this->finalTime;
}

template<typename Index, typename Value>
auto GearLooper::Time<Index, Value>::getIndex() const
	-> index_type
{
	return this->timeIndex;
}

template<typename Index, typename Value>
auto GearLooper::Time<Index, Value>::getTimeStep() const
	-> value_type
{
	return this->timeStep;
}

template<typename Index, typename Value>
auto GearLooper::Time<Index, Value>::as_pair() const
	-> time_pair
{
	return std::make_pair(this->timeIndex, this->time);
}

template<typename Index, typename Value>
json GearLooper::Time<Index, Value>::as_json() const
{
	return json{
		{"timeInstant", time},
		{"timeIndex", timeIndex}
	};
}

} // psin

#endif // GEAR_LOOPER_TPP
