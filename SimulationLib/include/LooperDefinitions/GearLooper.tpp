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
	this->timeIndex += Index(1);
}

template<typename Index, typename Value>
bool GearLooper::Time<Index, Value>::end() const
{
	return this->time >= this->finalTime;
}

template<typename Index, typename Value>
std::pair<Index, Value> GearLooper::Time<Index, Value>::as_pair() const
{
	return std::make_pair(this->timeIndex, this->time);
}

template<typename Index, typename Value>
json GearLooper::Time<Index, Value>::as_json() const
{
	return json{
		{to_string(timeIndex), time}
	};
}

} // psin

#endif // GEAR_LOOPER_TPP
