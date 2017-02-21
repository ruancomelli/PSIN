#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

// Standard
#include <vector>
#include <stdexcept>

// EntityLib
#include <Entity.h>

// UtilsLibSpecific
#include <Vector.h>
#include <Vector3D.h>
#include <SharedPointer.h>

// PropertyLib
#include <PropertyContainer.h>
#include <PropertyList.h>

using namespace std;
using namespace PropertyList;

namespace boost{ using many = std::vector<any>; };


enum GeometryType{
	SPHERE = 0,
	DEFAULT = SPHERE
};

// START "TO DELETE"
enum ScalarProperty{ 
  MASS = 0,        // m --- kg 
  MOMENT_OF_INERTIA,    // J --- kg * m^2 
  VOLUME,          // V --- m^3 
  SPECIFIC_MASS,      // \rho --- kg / m^3 
  DISSIPATIVE_CONSTANT,  // A --- s 
  POISSON_RATIO,      // \nu --- * 
  ELASTIC_MODULUS,    // E or Y --- N / m^2 
  TANGENTIAL_DAMPING,    // \gamma^t --- N * s / m 
  FRICTION_PARAMETER,    // \mu --- * 
  NORMAL_DISSIPATIVE_CONSTANT,    // \gamma^n --- N * s / m 
  TANGENTIAL_KAPPA,    // \kappa^t --- N / m 
  N_SCALAR_PROPERTY 
}; 
 
enum VectorialProperty{ 
  N_VECTORIAL_PROPERTY 
}; 
 
enum MatricialProperty{ 
  N_MATRICIAL_PROPERTY 
}; 
// END "TO DELETE"

class PhysicalEntity;
typedef SharedPointer<PhysicalEntity> PhysicalEntityPtr;

class PhysicalEntity: public Entity
{
	public:
		// ---- Constructors ----
		PhysicalEntity();
		explicit PhysicalEntity(const Entity & base); // Creates a PhysicalEntity based on an Entity
		PhysicalEntity(const int taylorOrder, const int dim, const int handle = -1);
		PhysicalEntity(const int taylorOrder, const int dim, const Entity & base);

		// ---- Spatial localization ----
		void setPosition(const int derivative, const double x, const double y, const double z = 0);
		void setPosition(const int derivative, const Vector3D & vec);
		void setPosition(const vector<Vector3D>  & position);
		vector<Vector3D> getPosition(void) const;
		Vector3D getPosition(const int derivative) const;
		
		void setOrientation(const int derivative, const double x, const double y, const double z);
		void setOrientation(const int derivative, const Vector3D & vec);
		void setOrientation(const vector<Vector3D> & orientation);
		vector<Vector3D> getOrientation(void) const;
		Vector3D getOrientation(const int derivate) const;
		
		// ---- Geometry ----
		void setGeometry(const GeometryType);
		GeometryType getGeometry() const;
		
		// ---- Properties ----
			// dimension
		int getDimension(void) const;

			// taylorOrder
		void setTaylorOrder(const int taylorOrder);
		int getTaylorOrder(void) const;

			// set property
		template< typename interfaceType, typename storedType, typename implicitInterfaceType >
		void set( const RawProperty<interfaceType, storedType> & raw, const implicitInterfaceType & value );

			// get property
		template<typename interfaceType, typename storedType>
		interfaceType get(const RawProperty<interfaceType, storedType> & raw) const;

		// START "TO DELETE"
	    void setScalarProperty(const int scalarPropertyIdentifier, const double scalarPropertyValue); 
	    void setScalarProperty(const DoubleVector scalarPropertyVector); 
	    double getScalarProperty(const int scalarPropertyIdentifier) const; 
	    DoubleVector getScalarProperty() const; 
    	DoubleVector2D getVectorialProperty() const;
    	vector < DoubleVector2D > getMatricialProperty() const;
	    // END "TO DELETE"
		
	private:
		int			 taylorOrder; // Number of derivates. If zero, there is just the position (not the velocity)
		static int	 dimension; // Dimension of simulation. ( = 2 ) or ( = 3 )
		GeometryType geometry;
		
		vector<Vector3D>	position;
		vector<Vector3D>	orientation;

		static void setDimension(const int dim);

		// memory functions
		void resizePositionOrientation(void);

		// set spatial positions
		void setSpatial(vector<Vector3D> & spatial, const int derivative, const double x, const double y, const double z = 0);
		void setSpatial(vector<Vector3D> & spatial, const int derivative, const Vector3D & vec);
		void setSpatial(vector<Vector3D> & spatialToSet, const vector<Vector3D> & spatial);

		// properties
		PropertyContainer propertyContainer;
};

#include <PhysicalEntity.tpp>


#endif
