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

using namespace std;


enum GeometryType{
	SPHERE = 0,
	DEFAULT = SPHERE
};


enum ScalarProperty{
	MASS = 0,
	MOMENT_OF_INERTIA,		// J
	VOLUME,
	SPECIFIC_MASS,			// \rho
	DISSIPATIVE_CONSTANT,	// A
	POISSON_RATIO,			// \nu
	ELASTIC_MODULUS,		// E or Y
	TANGENTIAL_DAMPING,		// \gamma^t
	FRICTION_PARAMETER,		// \mu
	N_SCALAR_PROPERTY
};

enum VectorialProperty{
	N_VECTORIAL_PROPERTY
};

enum MatricialProperty{
	N_MATRICIAL_PROPERTY
};

class PhysicalEntity;
typedef SharedPointer<PhysicalEntity> PhysicalEntityPtr;

class PhysicalEntity: public Entity
{
	public:
		// ---- Constructors ----
		PhysicalEntity();
		PhysicalEntity(const Entity & base); // Creates a PhysicalEntity based on an Entity
		PhysicalEntity(const int taylorOrder, const int dim, const int handle = -1);
		PhysicalEntity(const int taylorOrder, const int dim, const Entity & base);

		// ---- Spatial localization ----
		void setPosition(const int derivative, const double x, const double y, const double z = 0);
		void setPosition(const int derivative, const Vector3D & vec);
		void setPosition(const vector<Vector3D>  & position);
		vector<Vector3D> getPosition(void) const;
		Vector3D getPosition(const int) const;
		
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

			// scalarProperty
		void setScalarProperty(const int scalarPropertyIdentifier, const double scalarPropertyValue);
		void setScalarProperty(const DoubleVector scalarPropertyVector);
		double getScalarProperty(const int scalarPropertyIdentifier) const;
		DoubleVector getScalarProperty() const;

			// The two above are incomplete (vectorial and matricial property).
			// vectorialProperty
		DoubleVector2D getVectorialProperty() const {return this->vectorialProperty; }

			// matricialProperty
		vector < DoubleVector2D > getMatricialProperty() const {return this->matricialProperty; }
		
	private:
		int			 taylorOrder; // Number of derivates. If zero, there is just the position (not the velocity)
		static int	 dimension; // Dimension of simulation. ( = 2 ) or ( = 3 )
		GeometryType geometry;

		DoubleVector				scalarProperty;
		DoubleVector2D				vectorialProperty;
		vector < DoubleVector2D >	matricialProperty;
		
		vector<Vector3D>	position;
		vector<Vector3D>	orientation;

		static void setDimension(const int dim);
		// memory functions
		void resizePositionOrientation(void);
		void resizePropertyVector(void);
		// set spacial positions
		void setSpatial(vector<Vector3D> & spatial, const int derivative, const double x, const double y, const double z = 0);
		void setSpatial(vector<Vector3D> & spatial, const int derivative, const Vector3D & vec);
		void setSpatial(vector<Vector3D> & spatialToSet, const vector<Vector3D> & spatial);
};


#endif
