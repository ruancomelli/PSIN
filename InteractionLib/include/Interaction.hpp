#ifndef INTERACTION_HPP
#define INTERACTION_HPP

// // UtilsLib
#include <Named.hpp>
// #include <SharedPointer.hpp>
#include <mp/type_collection.hpp>
#include <Vector.hpp>
#include <Vector3D.hpp>
#include <Mathematics.hpp>

// // EntityLib
// #include <SphericalParticle.hpp>

// // PropertyLib
// #include <Property.hpp>

// Standard
#include <type_traits>

// Vector3D defaultNormalForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor );
// void defaultTangentialForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );
// void defaultFieldForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

namespace psin {

template<typename...Ts>
class Interaction : public Named
{
	public:	
		using required_properties = mp::type_collection<Ts...>;

		template<typename X>
		constexpr static bool has_required_properties = X::PropertyList::template is_superset_of< required_properties >;
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

template<>
class Interaction<>
{
	template<typename...Ts>	using vector = std::vector<Ts...>;

	public:
		template<typename T>
		static T taylorPredictor(T&& currentVector, const std::size_t predictionOrder, const double dt);
		template<typename T, typename U>
		static T gearCorrector(T&& predictedVector, U&& doubleDerivative, const std::size_t predictionOrder, const double dt);
	private:

};

} // psin

#include <Interaction.tpp>

#endif
