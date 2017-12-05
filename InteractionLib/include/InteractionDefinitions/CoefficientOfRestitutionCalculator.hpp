#ifndef COEFFICIENT_OF_RESTITUTION_CALCULATOR_HPP
#define COEFFICIENT_OF_RESTITUTION_CALCULATOR_HPP

// EntityLib
#include <SphericalParticle.hpp>

// UtilsLib
#include <Builder.hpp>
#include <FileSystem.hpp>
#include <NamedType.hpp>
#include <UniquePointer.hpp>
#include <Vector3D.hpp>
#include <mp/logical.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
struct CoefficientOfRestitutionCalculator
{
public:
	using name_pair = std::pair<string, string>;
	using velocities_t = std::tuple<std::size_t, std::size_t, double, double>;
	static constexpr auto initial_instant_idx = 0;
	static constexpr auto final_instant_idx = 1;
	static constexpr auto initial_velocity_idx = 2;
	static constexpr auto final_velocity_idx = 3;

	template<typename Particle, typename Neighbor>
	struct check : mp::disjunction<
			mp::conjunction<
				is_spherical<Particle>,
				is_plane<Neighbor>>,
			mp::conjunction<
				is_spherical<Particle>,
				is_spherical<Neighbor>>
		>
	{};

	template<typename Particle, typename Neighbor>
	constexpr static bool check_v = check<Particle, Neighbor>::value;

	template<typename Particle, typename Neighbor, typename Time>
	static void calculate(const Particle & particle, const Neighbor & neighbor, const Time & t);

	static void setFile(const path & filepath);

	static void finish();
private:
	template<typename Particle, typename Neighbor, typename Time>
	static void startCollision(const Particle & particle, const Neighbor & neighbor, const Time & t);

	template<typename Particle, typename Neighbor>
	static bool checkCollision(const Particle & particle, const Neighbor & neighbor);

	template<typename Particle, typename Neighbor, typename Time>
	static void endCollision(const Particle & particle, const Neighbor & neighbor, const Time & t);
	
	static std::map<name_pair, bool> collisionFlag;
	static std::map<name_pair, double> coefficientOfRestitution;
	static std::map<name_pair, velocities_t> velocities;

	static unique_ptr<std::fstream> file;

	template<typename Particle, typename Neighbor>
	static std::pair<string, string> makeNamePair(const Particle & particle, const Neighbor & neighbor);

	static bool firstPrint;
	static bool initialized;
};

template<typename I>
void initializeInteraction(const json & j);

template<>
void initializeInteraction<CoefficientOfRestitutionCalculator>(const json & j);

template<typename I>
void finalizeInteraction();

template<>
void finalizeInteraction<CoefficientOfRestitutionCalculator>();

} // psin

#include <InteractionDefinitions/CoefficientOfRestitutionCalculator.tpp>

#endif