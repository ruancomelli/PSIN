#ifndef SURROUNDING_FLUID_HPP
#define SURROUNDING_FLUID_HPP

// EntityLib
#include <FixedBoundary.hpp>

namespace psin {

template<typename ... Prs>
class SurroundingFluid : 
    public FixedBoundary<Prs...>
{
	public:
		constexpr static bool is_surrounding_fluid = true;
		
		using Indentity = SurroundingFluid<Prs...>;
		using BaseFixedBoundary = FixedBoundary<Prs...>;
		
		SurroundingFluid() = default;
		SurroundingFluid(const Indentity &) = default;
		SurroundingFluid(Indentity &&) = default;
		Indentity& operator=(const Indentity &) = default;
		Indentity& operator=(Indentity &&) = default;
		virtual ~SurroundingFluid() = default;

		SurroundingFluid(const BaseFixedBoundary & boundary);
		SurroundingFluid(BaseFixedBoundary && boundary);
};

template<typename ... Prs>
void from_json(const json& j, SurroundingFluid<Prs...> & fixed);
template<typename ... Prs>
void to_json(json& j, const SurroundingFluid<Prs...> & fixed);

template<typename T, typename SFINAE = void>
struct is_surrounding_fluid : std::false_type {};

template<typename T>
struct is_surrounding_fluid<
		T,
		std::enable_if_t<T::is_surrounding_fluid or not T::is_surrounding_fluid>
	>
	: mp::bool_constant<T::is_surrounding_fluid>
{};

} // psin

#include <SurroundingFluid.tpp>

#endif
