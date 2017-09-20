#include <InteractionDefinitions/TangentialForceCundallStrack.hpp>

// UtilsLib
#include <Named.hpp>
#include <string.hpp>

// Standard
#include <algorithm>
#include <map>
#include <utility>

namespace psin {

template<> const std::string NamedType<TangentialForceCundallStrack>::name = "TangentialForceCundallStrack";

void Builder<TangentialForceCundallStrack>::setup(json&)
{}

std::map< std::pair<string, string>, Vector3D> TangentialForceCundallStrack::cummulativeZeta;
std::map< std::pair<string, string>, bool> TangentialForceCundallStrack::collisionFlag;

void TangentialForceCundallStrack::addZeta( const Named & particle, const Named & neighbor, const Vector3D & zeta )
{
	const string name1 = std::min( particle.getName(), neighbor.getName() );
	const string name2 = std::max( particle.getName(), neighbor.getName() );
	cummulativeZeta[ std::make_pair(name1, name2) ] += zeta;
}
void TangentialForceCundallStrack::setZeta( const Named & particle, const Named & neighbor, const Vector3D & zeta )
{
	const string name1 = std::min( particle.getName(), neighbor.getName() );
	const string name2 = std::max( particle.getName(), neighbor.getName() );
	cummulativeZeta[ std::make_pair(name1, name2) ] = zeta;
}

bool TangentialForceCundallStrack::checkCollision(const Named & particle, const Named & neighbor)
{
	string name1 = particle.getName();
	string name2 = neighbor.getName();

	if(collisionFlag.count( std::pair<string, string>(name1, name2) ) > 0)
	{
		return collisionFlag[ std::make_pair(name1, name2) ];
	}
	else
	{
		return false;
	}
}

void TangentialForceCundallStrack::startCollision(const Named & particle, const Named & neighbor)
{
	string name1 = particle.getName();
	string name2 = neighbor.getName();

	collisionFlag[ std::make_pair(name1, name2) ] = true;
}

void TangentialForceCundallStrack::endCollision(const Named & particle, const Named & neighbor)
{
	string name1 = particle.getName();
	string name2 = neighbor.getName();

	collisionFlag[ std::make_pair(name1, name2) ] = false;
}

} // psin
