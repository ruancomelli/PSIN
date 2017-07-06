#ifndef INTERACTION_HPP
#define INTERACTION_HPP

// Standard
#include <functional>

// UtilsLib
#include <Named.hpp>
#include <SharedPointer.hpp>
#include <Vector3D.hpp>

// EntityLib
#include <SphericalParticle.hpp>

// PropertyLib
#include <Property.hpp>

Vector3D defaultNormalForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor );
void defaultTangentialForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );
void defaultFieldForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor );


template<typename ...>
class Interaction;

template<>
class Interaction <SphericalParticle, SphericalParticle> : public Named
{
	// public:	
	// 	using NormalType = std::function< Vector3D(SphericalParticlePtr, SphericalParticlePtr)>;
	// 	using TangentialType = std::function< void(SphericalParticlePtr, SphericalParticlePtr, Vector3D, double)>;
	// 	using FieldType = std::function< void(SphericalParticlePtr, SphericalParticlePtr)>;


	// 	static vector<Vector3D> taylorPredictor( const vector<Vector3D> & currentVector, const int predictionOrder, const double dt );
		
	// 	static void correctPosition( SphericalParticlePtr particle, const int predictionOrder, double dt );
	// 	static void correctOrientation( SphericalParticlePtr particle, const int predictionOrder, double dt );
		
	// 	static vector<Vector3D> gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt);
	
	// 	static void startCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );
	// 	static void endCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );

	// 	static void setNumberOfParticles( const int nParticles );
	// 	static int getNumberOfParticles( void );

	// 	Interaction();
	// 	explicit Interaction(const string & name);
	// 	Interaction( const Interaction<SphericalParticle, SphericalParticle> & fm );

	// 	// ---- Required Properties ----
	// 	PropertyContainer getRequiredProperties(void);

	// 	template<typename InterfaceType, typename StoredType>
	// 	void requireProperty( const Property<InterfaceType, StoredType> & property );

	// 	// ---- Force Methods ----
	// 	void setTimeStep( double timeStep );

	// 	void setNormal( NormalType newNormal );
	// 	void setTangential( TangentialType newTangential );
	// 	void setField( FieldType newField );

	// 	void setNormal( vector< NormalType > newNormal );
	// 	void setTangential( vector< TangentialType > newTangential );
	// 	void setField( vector< FieldType > newField );

	// 	void addNormal( NormalType newNormal );
	// 	void addTangential( TangentialType newTangential );
	// 	void addField( FieldType newField );

	// 	// ---- Force Calculation ----
	// 	void calculate( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

		
	// private:
	// 	static void resizeCollisionFlag( const int nParticles );

	// 	static vector< vector< bool > > collisionFlag;

	// 	static int numberOfParticles; // TO-DO: undo static!!

	// 	PropertyContainer requiredProperties;

	// 	double timeStep;

	// 	vector< NormalType > normalForceCalculationMethod;
	// 	vector< TangentialType > tangentialForceCalculationMethod;
	// 	vector< FieldType > fieldForceCalculationMethod;
};

#include <Interaction.tpp>

#endif