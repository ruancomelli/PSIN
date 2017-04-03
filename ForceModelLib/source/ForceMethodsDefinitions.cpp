#include <ForceMethodsDefinitions.hpp>

// ForceModelLib
#include <ForceModel.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// Standard
#include <cmath>

using namespace PropertyDefinitions;
using std::min;
using std::max;

void resizeCummulativeZeta( std::vector< std::vector< Vector3D > > & cummulativeZeta, const int numberOfParticles )
{
	cummulativeZeta.resize( numberOfParticles - 1 );
	for( int i=0 ; i < (numberOfParticles - 1) ; ++i )
		cummulativeZeta[i].resize( numberOfParticles - 1 - i );
}
void addZeta( std::vector< std::vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta )
{
	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
	const int index2 = max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;
	cummulativeZeta[index1][index2] += zeta;
}
void setZeta( std::vector< std::vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta )
{
	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
	const int index2 = max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;
	cummulativeZeta[index1][index2] = zeta;
}

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
// normalForceViscoelasticSpheres:
//		Calculates normal forces between two spherical particles according to equation (2.14) (see reference)
Vector3D normalForceViscoelasticSpheres( SphericalParticlePtr particle, SphericalParticlePtr neighbor)
{	
	
	// Calculations
	const double overlap = particle->overlap(neighbor);
	
	if(overlap > 0)
	{
		// ---- Get physical properties and calculate effective parameters ----
		const double radius1 = particle->getGeometricParameter(RADIUS);
		const double radius2 = neighbor->getGeometricParameter(RADIUS);
		const double effectiveRadius = radius1 * radius2 / ( radius1 + radius2 );
		
		const double elasticModulus1 = particle->get( elastic_modulus );
		const double elasticModulus2 = neighbor->get( elastic_modulus );
		
		const double dissipativeConstant1 = particle->get( dissipative_constant );
		const double dissipativeConstant2 = neighbor->get( dissipative_constant );
		
		const double poissonRatio1 = particle->get( poisson_ratio );
		const double poissonRatio2 = neighbor->get( poisson_ratio );
		
		// ---- Calculate normal force ----
		const double overlapDerivative = particle->overlapDerivative( neighbor );
		const double term1 = (4/3) * sqrt(effectiveRadius);
		const double term2 = sqrt(overlap) * (overlap + 0.5 * (dissipativeConstant1 + dissipativeConstant2) * overlapDerivative );
		const double term3 = (1 - poissonRatio1*poissonRatio1)/elasticModulus1 + (1 - poissonRatio2*poissonRatio2)/elasticModulus2;
		
		const double normalForceModulus = max( term1 * term2 / term3 , 0.0 );
		
		const Vector3D normalForce = - normalForceModulus * particle->normalDirection( neighbor );
		
		particle->addContactForce( normalForce );
		neighbor->addContactForce( - normalForce );

		return normalForce;
	}
	// else, no forces are added.
	return nullVector3D();
}

// normalForceLinearDashpotForce:
//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
Vector3D normalForceLinearDashpotForce( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
{
	const double overlap = particle->overlap(neighbor);
	
	if(overlap > 0)
	{
		// ---- Get physical properties and calculate effective parameters ----
		const double elasticModulus1 = particle->get( elastic_modulus );
		const double elasticModulus2 = neighbor->get( elastic_modulus );
		
		const double normalDissipativeConstant1 = particle->get( normal_dissipative_constant );
		const double normalDissipativeConstant2 = neighbor->get( normal_dissipative_constant );
		
		// ---- Calculate normal force ----
		const double overlapDerivative = particle->overlapDerivative( neighbor );
		
		const double normalForceModulus = max( (elasticModulus1 + elasticModulus2) * overlap + 
										(normalDissipativeConstant1 + normalDissipativeConstant2) * overlapDerivative , 0.0 );
		
		const Vector3D normalForce = - normalForceModulus * particle->normalDirection( neighbor );
		
		particle->addContactForce( normalForce );
		neighbor->addContactForce( - normalForce );
		return normalForce;
	}
	// else, no forces are added.
	return nullVector3D();
}

//		tangentialForce is the tangential force applied BY neighbor TO particle
// tangentialForceHaffWerner:
//		Calculates tangential forces between two spherical particles according to equation (2.18) (see reference)
void tangentialForceHaffWerner( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep )
{		
	if( particle->touches(neighbor) )
	{
		// ---- Getting particles properties and parameters ----
		const double radius1 = particle->getGeometricParameter(RADIUS);
		const double radius2 = neighbor->getGeometricParameter(RADIUS);
		const Vector3D position1 = particle->getPosition(0);
		const Vector3D position2 = neighbor->getPosition(0);
		const double tangentialDamping1 = particle->get( tangential_damping );
		const double tangentialDamping2 = neighbor->get( tangential_damping );
		const double effectiveTangentialDamping = min( tangentialDamping1 , tangentialDamping2 );
			
		const double frictionParameter1 = particle->get( friction_parameter );
		const double frictionParameter2 = neighbor->get( friction_parameter );
		const double effectiveFrictionParameter = min( frictionParameter1, frictionParameter2 );
		
		// ---- Calculate tangential force ----
		const Vector3D contactPoint = particle->contactPoint( neighbor );		
		const Vector3D relativeTangentialVelocity = particle->relativeTangentialVelocity( neighbor ) ;
		
		const Vector3D tangentialVersor = particle->tangentialVersor( neighbor );
		const Vector3D tangentialForce =	min( effectiveTangentialDamping * relativeTangentialVelocity.length() , 
			effectiveFrictionParameter * normalForce.length() ) * tangentialVersor;
		
		particle->addContactForce( tangentialForce );
		neighbor->addContactForce( - tangentialForce );
									
		particle->addTorque( cross(contactPoint - position1, tangentialForce) );
		neighbor->addTorque( cross(contactPoint - position2, - tangentialForce) );
	}
	// else, no forces and no torques are added.
}

// tangentialForceCundallStrack:
//		Calculates tangential forces between two spherical particles according to equation (2.21) (see reference)
void tangentialForceCundallStrack( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep )
{	
	static std::vector< std::vector< Vector3D > > cummulativeZeta;
	resizeCummulativeZeta( cummulativeZeta, ForceModel<SphericalParticle, SphericalParticle>::getNumberOfParticles() );
	if( particle->touches(neighbor) )
	{
		if( !ForceModel<SphericalParticle, SphericalParticle>::checkCollision(particle, neighbor) )
		{
			ForceModel<SphericalParticle, SphericalParticle>::startCollision( particle, neighbor );
			setZeta( cummulativeZeta, particle, neighbor, nullVector3D() );
		}
		// ---- Getting particles properties and parameters ----
		const Vector3D position1 = particle->getPosition(0);
		const Vector3D position2 = neighbor->getPosition(0);
		const double tangentialKappa1 = particle->get( tangential_kappa );
		const double tangentialKappa2 = neighbor->get( tangential_kappa );
		const double effectiveTangentialKappa = min( tangentialKappa1 , tangentialKappa2 );
			
		const double frictionParameter1 = particle->get( friction_parameter );
		const double frictionParameter2 = neighbor->get( friction_parameter );
		const double effectiveFrictionParameter = min( frictionParameter1, frictionParameter2 );
		
		// Calculate tangential force
		const Vector3D contactPoint = particle->contactPoint( neighbor );
		
		const Vector3D relativeTangentialVelocity = particle->relativeTangentialVelocity( neighbor );
		
		const Vector3D tangentialVersor = particle->tangentialVersor( neighbor );
		addZeta( cummulativeZeta, particle, neighbor, relativeTangentialVelocity * timeStep );
		
		const int index1 = min( particle->getHandle(), neighbor->getHandle() );
		const int index2 = max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;
		const Vector3D tangentialForce =	min( effectiveTangentialKappa * cummulativeZeta[index1][index2].length() , 
			effectiveFrictionParameter * normalForce.length() ) * tangentialVersor;
		
		particle->addContactForce( tangentialForce );
		neighbor->addContactForce( - tangentialForce );
									
		particle->addTorque( cross(contactPoint - position1, tangentialForce) );
		neighbor->addTorque( cross(contactPoint - position2, - tangentialForce) );
	}// else, no forces and no torques are added.
	else if( ForceModel<SphericalParticle, SphericalParticle>::checkCollision(particle, neighbor) )
	{
		ForceModel<SphericalParticle, SphericalParticle>::endCollision(particle, neighbor);
	}
}

void electrostaticForce( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
{
	double k = 9 * pow(10, 9);

	double charge1 = particle->get(electric_charge);
	double charge2 = neighbor->get(electric_charge);
	double r = particle->distance(neighbor);

	double force = - k * charge1 * charge2 / ( r * r );

	Vector3D electricForce = force * particle->normalDirection(neighbor);

	particle->addBodyForce( electricForce );
	neighbor->addBodyForce( - electricForce );
}