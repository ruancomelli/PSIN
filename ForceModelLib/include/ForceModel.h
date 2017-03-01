#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H

// std
#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>
#include <stdexcept>
#include <list>
#include <set>

// UtilsLib
#include <Vector3D.h>
#include <Vector.h>
#include <Mathematics.h>
#include <SharedPointer.h>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>

// PropertyLib
#include <Property.h>
#include <PropertyList.h>
#include <PropertyContainer.h>

using namespace std;

Vector3D defaultNormalForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor );
void defaultTangentialForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );
void defaultFieldForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

class ForceModel : public EnableSharedFromThis<ForceModel>
{
	public:	
		typedef SharedPointer<ForceModel> ForceModelPtr;

		typedef Vector3D (*NormalType)( SphericalParticlePtr particle, SphericalParticlePtr neighbor );
		typedef void (*TangentialType)( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );
		typedef void (*FieldType)( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

		struct ForceModelPtrCompare{
			bool operator()( const ForceModelPtr & left, const ForceModelPtr & right ) const
			{ return left->getName() < right->getName();}
		};
		
		static set<ForceModelPtr, ForceModelPtrCompare> forceModelList;

		static vector<Vector3D> taylorPredictor( const vector<Vector3D> & currentVector, const int predictionOrder, const double dt );
		
		static void correctPosition( SphericalParticlePtr particle, const int predictionOrder, double dt );
		static void correctOrientation( SphericalParticlePtr particle, const int predictionOrder, double dt );
		
		static vector<Vector3D> gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt);
	
		static bool checkCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );
		static void startCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );
		static void endCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );

		static void setNumberOfParticles( const int nParticles );
		static int getNumberOfParticles( void );

		ForceModel();
		explicit ForceModel(const string & name);
		ForceModel( const ForceModel & fm );

		// ---- Add to List ----
		void addToList(void);

		// ---- Name ----
		string getName(void) const;
		void setName(const string & name);

		// ---- Required Properties ----
		RawPropertyContainer getRequiredProperties(void);

		template<typename interfaceType, typename storedType>
		void requireProperty( const Property<interfaceType, storedType> & property );

		// ---- Force Methods ----
		void setTimeStep( double timeStep );

		void setNormal( NormalType newNormal );
		void setTangential( TangentialType newTangential );
		void setField( FieldType newField );

		void setNormal( vector< NormalType > newNormal );
		void setTangential( vector< TangentialType > newTangential );
		void setField( vector< FieldType > newField );

		void addNormal( NormalType newNormal );
		void addTangential( TangentialType newTangential );
		void addField( FieldType newField );

		// ---- Force Calculation ----
		void calculate( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

		
	private:
		static void resizeCollisionFlag( const int nParticles );

		static vector< vector< bool > > collisionFlag;

		static int numberOfParticles; // TO-DO: undo static!!

		string name;

		RawPropertyContainer requiredProperties;

		double timeStep;

		vector< NormalType > normalForceCalculationMethod;
		vector< TangentialType > tangentialForceCalculationMethod;
		vector< FieldType > fieldForceCalculationMethod;

};

typedef ForceModel::ForceModelPtr ForceModelPtr;

#include <ForceModel.tpp>

#endif
