#ifndef TANGENTIAL_FORCE_CUNDALL_STRACK_HPP
#define TANGENTIAL_FORCE_CUNDALL_STRACK_HPP

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.21) (see reference)
struct TangentialForceCundallStrack
{
	public:
		template<typename...Ts, typename...Us>
		static void calculate(SphericalParticle<Ts...> particle1, SphericalParticle<Us...> particle2, Vector3D normalForce, double timeStep)
		{
			resizeCummulativeZeta( Interaction<SphericalParticle, SphericalParticle>::getNumberOfParticles() );
			if( particle->touches(neighbor) )
			{
				if( !Interaction<SphericalParticle, SphericalParticle>::checkCollision(particle, neighbor) )
				{
					Interaction<SphericalParticle, SphericalParticle>::startCollision( particle, neighbor );
					setZeta( particle, neighbor, nullVector3D() );
				}
				// ---- Getting particles properties and parameters ----
				const Vector3D position1 = particle->getPosition(0);
				const Vector3D position2 = neighbor->getPosition(0);
				const double tangentialKappa1 = particle->get( tangential_kappa );
				const double tangentialKappa2 = neighbor->get( tangential_kappa );
				const double effectiveTangentialKappa = std::min( tangentialKappa1 , tangentialKappa2 );
					
				const double frictionParameter1 = particle->get( friction_parameter );
				const double frictionParameter2 = neighbor->get( friction_parameter );
				const double effectiveFrictionParameter = std::min( frictionParameter1, frictionParameter2 );
				
				// Calculate tangential force
				const Vector3D contactPoint = particle->contactPoint( neighbor );
				
				const Vector3D relativeTangentialVelocity = particle->relativeTangentialVelocity( neighbor );
				
				const Vector3D tangentialVersor = particle->tangentialVersor( neighbor );
				addZeta( particle, neighbor, relativeTangentialVelocity * timeStep );
				
				const int index1 = std::min( particle->getHandle(), neighbor->getHandle() );
				const int index2 = std::max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;
				const Vector3D tangentialForce =	std::min( effectiveTangentialKappa * cummulativeZeta[index1][index2].length() , 
					effectiveFrictionParameter * normalForce.length() ) * tangentialVersor;
				
				particle->addContactForce( tangentialForce );
				neighbor->addContactForce( - tangentialForce );
											
				particle->addTorque( cross(contactPoint - position1, tangentialForce) );
				neighbor->addTorque( cross(contactPoint - position2, - tangentialForce) );
			}// else, no forces and no torques are added.
			else if( Interaction<SphericalParticle, SphericalParticle>::checkCollision(particle, neighbor) )
			{
				Interaction<SphericalParticle, SphericalParticle>::endCollision(particle, neighbor);
			}
		}

	private:
		static void resizeCummulativeZeta( const int & numberOfParticles )
		{
			cummulativeZeta.resize( numberOfParticles - 1 );
			for( int i=0 ; i < (numberOfParticles - 1) ; ++i )
				cummulativeZeta[i].resize( numberOfParticles - 1 - i );
		}
		static void addZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta )
		{
			const unsigned index1 = std::min( particle->getHandle(), neighbor->getHandle() );
			const unsigned index2 = std::max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;
			cummulativeZeta[ std::pair<unsigned, unsigned>(index1, index2) ] += zeta;
		}
		static void setZeta( const HandledEntity & particle, const HandledEntity & neighbor, const Vector3D & zeta )
		{
			const unsigned index1 = std::min( particle->getHandle(), neighbor->getHandle() );
			const unsigned index2 = std::max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;
			cummulativeZeta[ std::pair<unsigned, unsigned>(index1, index2) ] = zeta;
		}

		static std::map< std::pair<unsigned, unsigned>, double> cummulativeZeta;
};

#endif
