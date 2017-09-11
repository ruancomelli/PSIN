#ifndef TANGENTIAL_FORCE_CUNDALL_STRACK_HPP
#define TANGENTIAL_FORCE_CUNDALL_STRACK_HPP

// EntityLib
#include <HandledEntity.hpp>
#include <SphericalParticle.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <Vector3D.hpp>
#include <mp/bool_constant.hpp>

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
			P1::template has_property<TangentialKappa>::value
			and P1::template has_property<FrictionParameter>::value
			and is_spherical<P1>::value

			and P2::template has_property<TangentialKappa>::value
			and P2::template has_property<FrictionParameter>::value
			and is_spherical<P2>::value
			>
		{};

		template<typename...Ts, typename...Us>
		static void calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Vector3D normalForce, double timeStep);

	private:
		static std::map< std::pair<unsigned, unsigned>, Vector3D> cummulativeZeta;
		static std::map< std::pair<unsigned, unsigned>, bool> collisionFlag;
		
		static void addZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta );
		static void setZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta );

		static void startCollision(const HandledEntity & particle, const HandledEntity & neighbor);
		static bool checkCollision(const HandledEntity & particle, const HandledEntity & neighbor);
		static void endCollision(const HandledEntity & particle, const HandledEntity & neighbor);
};

} // psin

#include <InteractionDefinitions/TangentialForceCundallStrack.tpp>

#endif
