#ifndef PHYSICAL_ENTITY_HPP
#define PHYSICAL_ENTITY_HPP

// Standard
#include <vector>
#include <set>

// EntityLib
#include <Entity.hpp>

// UtilsLib
#include <Vector3D.hpp>
#include <SharedPointer.hpp>
#include <Any.hpp>

// PropertyLib
#include <PropertyContainer.hpp>


enum GeometryType{
	SPHERE = 0,
	DEFAULT = SPHERE
};

template<typename ... Properties>
class PhysicalEntity: public Entity
{
	using string = std::string;

	template<typename ... Args>
	using vector = std::vector<Args...>;

	public:
		using PhysicalEntityPtr = SharedPointer<PhysicalEntity>;

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
		void requireProperties( const PropertyContainer & raw );

			// dimension
		int getDimension(void) const;

			// taylorOrder
		void setTaylorOrder(const int taylorOrder);
		int getTaylorOrder(void) const;

			// set property
		template< typename InterfaceType, typename StoredType, typename implicitInterfaceType >
		void set( const Property<InterfaceType, StoredType> & property, const implicitInterfaceType & value );

		void set( const string & rawName, const Any & value ); // CAUTION: inputMethod and outputMethod are not inserted!

			// get property
		template<typename InterfaceType, typename StoredType>
		InterfaceType get(const Property<InterfaceType, StoredType> & property) const;

		Any getAsAnyValue( const string & name ) const;

		SharedPointer<std::set<string>> getPropertyNames( void ) const;
		
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
		ValuedPropertyContainer propertyContainer;
};

using PhysicalEntityPtr = SharedPointer<PhysicalEntity>;

#include <PhysicalEntity.tpp>


#endif
