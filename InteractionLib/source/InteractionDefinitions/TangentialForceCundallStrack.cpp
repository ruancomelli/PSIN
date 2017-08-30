#include <InteractionDefinitions/TangentialForceCundallStrack.hpp>

// EntityLib
#include <HandledEntity.hpp>

// Standard
#include <algorithm>
#include <map>
#include <utility>
#include <string>

namespace psin {

template<> const std::string NamedType<TangentialForceCundallStrack>::name = "TangentialForceCundallStrack";

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.21) (see reference)
std::map< std::pair<unsigned, unsigned>, Vector3D> TangentialForceCundallStrack::cummulativeZeta;
std::map< std::pair<unsigned, unsigned>, bool> TangentialForceCundallStrack::collisionFlag;

void TangentialForceCundallStrack::addZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta )
{
	const unsigned index1 = std::min( particle.getHandle(), neighbor.getHandle() );
	const unsigned index2 = std::max( particle.getHandle(), neighbor.getHandle() ) - index1 - 1;
	cummulativeZeta[ std::pair<unsigned, unsigned>(index1, index2) ] += zeta;
}
void TangentialForceCundallStrack::setZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta )
{
	const unsigned index1 = std::min( particle.getHandle(), neighbor.getHandle() );
	const unsigned index2 = std::max( particle.getHandle(), neighbor.getHandle() ) - index1 - 1;
	cummulativeZeta[ std::pair<unsigned, unsigned>(index1, index2) ] = zeta;
}

bool TangentialForceCundallStrack::checkCollision(const HandledEntity & particle, const HandledEntity & neighbor)
{
	unsigned handle1 = particle.getHandle();
	unsigned handle2 = neighbor.getHandle();

	if(collisionFlag.count( std::pair<unsigned, unsigned>(handle1, handle2) ) > 0)
	{
		return collisionFlag[ std::pair<unsigned, unsigned>(handle1, handle2) ];
	}
	else
	{
		return false;
	}
}

void TangentialForceCundallStrack::startCollision(const HandledEntity & particle, const HandledEntity & neighbor)
{
	unsigned handle1 = particle.getHandle();
	unsigned handle2 = neighbor.getHandle();

	collisionFlag[ std::pair<unsigned, unsigned>(handle1, handle2) ] = true;
}

void TangentialForceCundallStrack::endCollision(const HandledEntity & particle, const HandledEntity & neighbor)
{
	unsigned handle1 = particle.getHandle();
	unsigned handle2 = neighbor.getHandle();

	collisionFlag[ std::pair<unsigned, unsigned>(handle1, handle2) ] = false;
}

} // psin
