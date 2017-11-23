#ifndef SURROUNDING_FLUID_TPP
#define SURROUNDING_FLUID_TPP

// UtilsLib
#include <NamedType.hpp>

namespace psin {

template<typename...Prs>
void from_json(const json& j, SurroundingFluid<Prs...> & fluid)
{
	fluid = SurroundingFluid<Prs...>( j.get<typename SurroundingFluid<Prs...>::BaseFixedBoundary>() );
}

template<typename...Prs>
void to_json(json& j, const SurroundingFluid<Prs...> & fluid)
{
	j = static_cast<typename SurroundingFluid<Prs...>::BaseFixedBoundary>(fluid);
}

template<typename...Prs>
struct NamedType<SurroundingFluid<Prs...>>
{
	const static std::string name;
}; //struct NamedType

template<typename...Prs>
const string NamedType<SurroundingFluid<Prs...>>::name = "SurroundingFluid";

template<typename...Prs>
SurroundingFluid<Prs...>::SurroundingFluid(const BaseFixedBoundary & boundary)
	: BaseFixedBoundary(boundary)
{}

template<typename...Prs>
SurroundingFluid<Prs...>::SurroundingFluid(BaseFixedBoundary && boundary)
	: BaseFixedBoundary(std::move(boundary))
{}

} // psin

#endif // SURROUNDING_FLUID_TPP
