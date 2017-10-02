#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

// EntityLib
#include <PhysicalEntity.hpp>

// UtilsLib
#include <Named.hpp>

namespace psin {
	
template<typename ... PropertyTypes>
class Boundary : 
    public Named,
    public PhysicalEntity<PropertyTypes...>
{
	public:
		using BasePhysicalEntity = PhysicalEntity<PropertyTypes...>;

		Boundary() = default;
		explicit Boundary(const Named & named, const BasePhysicalEntity & physical = BasePhysicalEntity());
		Boundary(Named&& named, BasePhysicalEntity&& physical);

		template<typename Time>
		void update(const Time & t);
};

template<typename ... PropertyTypes>
void from_json(const json& j, Boundary<PropertyTypes...> & b);
template<typename ... PropertyTypes>
void to_json(json& j, const Boundary<PropertyTypes...> & b);

} // psin

#include <Boundary.tpp>

#endif
