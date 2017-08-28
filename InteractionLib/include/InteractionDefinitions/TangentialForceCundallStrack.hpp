#ifndef TANGENTIAL_FORCE_CUNDALL_STRACK_HPP
#define TANGENTIAL_FORCE_CUNDALL_STRACK_HPP

// EntityLib
#include <HandledEntity.hpp>
#include <SphericalParticle.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <Vector3D.hpp>
#include <MP/bool_type.hpp>

// Standard
#include <map>
#include <utility>

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.21) (see reference)
struct TangentialForceCundallStrack
{
	public:
		using TangentialKappa = PropertyDefinitions::TangentialKappa;
		using FrictionParameter = PropertyDefinitions::FrictionParameter;

		template<typename P1, typename P2>
		struct check : bool_type<
			P1::template has_property<TangentialKappa>::value
			&& P1::template has_property<FrictionParameter>::value
			&& is_spherical<P1>::value

			&& P2::template has_property<TangentialKappa>::value
			&& P2::template has_property<FrictionParameter>::value
			&& is_spherical<P2>::value
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

template<> const std::string NamedType<TangentialForceCundallStrack>::name = "TangentialForceCundallStrack";

#include <InteractionDefinitions/TangentialForceCundallStrack.tpp>

#endif
