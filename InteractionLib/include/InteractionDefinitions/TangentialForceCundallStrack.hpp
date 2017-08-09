#ifndef TANGENTIAL_FORCE_CUNDALL_STRACK_HPP
#define TANGENTIAL_FORCE_CUNDALL_STRACK_HPP

// EntityLib
#include <HandledEntity.hpp>
#include <SphericalParticle.hpp>

// UtilsLib
#include <Vector3D.hpp>

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
		template<typename...Ts, typename...Us>
		static void calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Vector3D normalForce, double timeStep);

		static void startCollision(const HandledEntity & particle, const HandledEntity & neighbor);

	private:
		static std::map< std::pair<unsigned, unsigned>, Vector3D> cummulativeZeta;
		static std::map< std::pair<unsigned, unsigned>, bool> collisionFlag;
		
		static void addZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta );
		static void setZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta );

		static bool checkCollision(const HandledEntity & particle, const HandledEntity & neighbor);
		static void endCollision(const HandledEntity & particle, const HandledEntity & neighbor);
};

#include <InteractionDefinitions/TangentialForceCundallStrack.tpp>

#endif
