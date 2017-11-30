#ifndef COEFFICIENT_OF_RESTITUTION_CALCULATOR_TPP
#define COEFFICIENT_OF_RESTITUTION_CALCULATOR_TPP

// EntityLib
#include <SphericalParticle.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// Standard
#include <algorithm>

namespace psin {

template<typename Particle, typename Neighbor, typename Time>
void CoefficientOfRestitutionCalculator::calculate(const Particle & particle, const Neighbor & neighbor, const Time & t)
{
	std::cout << "Entering CoefficientOfRestitutionCalculator --------------------------------------------------" << std::endl; // DEBUG
	std::cout << "checkCollision: " << checkCollision(particle, neighbor) << std::endl; // DEBUG
	std::cout << "checkCollision: " << checkCollision(particle, neighbor) << std::endl; // DEBUG

	if(checkCollision(particle, neighbor))
	{
		if(not touch(particle, neighbor))
		{
			std::cout << "Ending Collision ===============================================================" << std::endl; // DEBUG
			endCollision(particle, neighbor, t);
		}
		else
		{
			std::get<final_velocity_idx>(velocities[ std::make_pair(particle.getName(), neighbor.getName()) ]) = psin::relativeNormalSpeedContactPoint(particle, neighbor);
		}
	}
	else if(touch(particle, neighbor))
	{
		std::cout << "Beginning Collision ===============================================================" << std::endl; // DEBUG
		startCollision(particle, neighbor, t);
	}
}

template<typename Particle, typename Neighbor>
bool CoefficientOfRestitutionCalculator::checkCollision(const Particle & particle, const Neighbor & neighbor)
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

template<typename Particle, typename Neighbor, typename Time>
void CoefficientOfRestitutionCalculator::startCollision(const Particle & particle, const Neighbor & neighbor, const Time & t)
{
	string name1 = particle.getName();
	string name2 = neighbor.getName();

	auto timeIndex = t.getIndex();
	auto relativeNormalVelocity = psin::relativeNormalSpeedContactPoint(particle, neighbor);

	collisionFlag[ std::make_pair(name1, name2) ] = true;
	velocities[ std::make_pair(name1, name2) ] = std::make_tuple(timeIndex, timeIndex, relativeNormalVelocity, relativeNormalVelocity);
}

template<typename Particle, typename Neighbor, typename Time>
void CoefficientOfRestitutionCalculator::endCollision(const Particle & particle, const Neighbor & neighbor, const Time & t)
{
	string name1 = particle.getName();
	string name2 = neighbor.getName();
	auto namePair = std::make_pair(name1, name2);

	collisionFlag[ namePair ] = false;
	std::get<final_instant_idx>(velocities[ namePair ]) = t.getIndex();
	coefficientOfRestitution[namePair] = - std::get<final_velocity_idx>(velocities[ namePair ]) / std::get<initial_velocity_idx>(velocities[ namePair ]);

	json j{
		{"pair", vector<string>{name1, name2}},
		{"velocities", vector<double>{
			std::get<initial_velocity_idx>(velocities[ namePair ]),
			std::get<final_velocity_idx>(velocities[ namePair ])}},
		{"timeIndices", vector<typename Time::index_type>{
			std::get<initial_instant_idx>(velocities[ namePair ]),
			std::get<final_instant_idx>(velocities[ namePair ])}},
		{"coefficientOfRestitution", coefficientOfRestitution[namePair]}
	};

	std::cout << "Writing" << std::endl
		<< j.dump(4) << std::endl
		<< "to file." << std::endl; // DEBUG
	*file << j.dump(4);
}

} // psin

#endif