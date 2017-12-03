#ifndef GEAR_LOOPER_TPP
#define GEAR_LOOPER_TPP

#include <string.hpp>

namespace psin {

template<typename Index, typename Value>
GearLooper::Time<Index, Value>::Time(const Value & initialInstant, const Value & timeStep, const Value & finalInstant)
	: timeIndex(0),
	time(initialInstant),
	initialInstant(initialInstant),
	timeStep(timeStep),
	finalInstant(finalInstant)
{}

template<typename Index, typename Value>
void GearLooper::Time<Index, Value>::start()
{
	this->time = this->initialInstant;
	this->timeIndex = index_type(0);
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
	return this->time >= this->finalInstant;
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
string GearLooper::Time<Index, Value>::getIndexTag() const
{
	return "timeIndex";
}

template<typename Index, typename Value>
string GearLooper::Time<Index, Value>::getTimeTag() const
{
	return "timeInstant";
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
		{this->getTimeTag(), this->time},
		{this->getIndexTag(), this->timeIndex}
	};
}

} // psin

#endif // GEAR_LOOPER_TPP
