#ifndef TANGENTIAL_FORCE_CUNDALL_STRACK_HPP
#define TANGENTIAL_FORCE_CUNDALL_STRACK_HPP

// EntityLib
#include <HandledEntity.hpp>
#include <SphericalParticle.hpp>

// UtilsLib
#include <Builder.hpp>
#include <NamedType.hpp>
#include <string.hpp>
#include <Vector3D.hpp>
#include <mp/bool_constant.hpp>

// JSONLib
#include <json.hpp>

// Standard
#include <map>
#include <utility>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.21) (see reference)
struct TangentialForceCundallStrack
{
	public:
		template<typename P1, typename P2>
		struct check : mp::bool_constant<
			has_property<P1, TangentialKappa>::value
			and has_property<P1, FrictionParameter>::value
			and is_spherical<P1>::value

			and has_property<P2, TangentialKappa>::value
			and has_property<P2, FrictionParameter>::value
			and is_spherical<P2>::value
			>
		{};

		template<typename...Ts, typename...Us, typename Time>
		static void calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Time&& time);

	private:
		static std::map< std::pair<string, string>, Vector3D> cummulativeZeta;
		static std::map< std::pair<string, string>, bool> collisionFlag;
		
		static void addZeta( const Named & particle, const Named & neighbor, const Vector3D & zeta );
		static void setZeta( const Named & particle, const Named & neighbor, const Vector3D & zeta );

		static void startCollision(const Named & particle, const Named & neighbor);
		static bool checkCollision(const Named & particle, const Named & neighbor);
		static void endCollision(const Named & particle, const Named & neighbor);
};

template<>
struct Builder<TangentialForceCundallStrack>
{
	static void setup(const json & j);
};

} // psin

#include <InteractionDefinitions/TangentialForceCundallStrack.tpp>

#endif
