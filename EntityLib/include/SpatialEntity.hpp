#ifndef SPATIAL_ENTITY_HPP
#define SPATIAL_ENTITY_HPP

// UtilsLib
#include <Vector3D.hpp>

// Standard
#include <vector>

#define DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER 4

template<typename T, typename U>
double distance(const T & left, const U & right);	// distance function. Must be specialized for every pair of types

class SpatialEntity
{
	public:
		SpatialEntity();
		explicit SpatialEntity(const int taylorOrder);

		// ----- Position -----
		void setPosition(const double x, const double y, const double z = 0);
		void setPosition(const Vector3D & position);

		void setVelocity(const double x, const double y, const double z = 0);
		void setVelocity(const Vector3D & velocity);

		void setAcceleration(const double x, const double y, const double z = 0);
		void setAcceleration(const Vector3D & acceleration);

		void setPositionMatrix(const std::vector<Vector3D> & positionMatrix); // throws

		void setPositionDerivative(const int derivative, const double x, const double y, const double z = 0); // throws
		void setPositionDerivative(const int derivative, const Vector3D & vec); // throws

		Vector3D getPosition() const;
		Vector3D getVelocity() const;
		Vector3D getAcceleration() const;

		std::vector<Vector3D> getPositionMatrix(void) const;
		Vector3D getPositionDerivative(const int derivative) const; // throws


		// ----- Orientation -----
		void setOrientation(const double x, const double y, const double z = 0);
		void setOrientation(const Vector3D & orientation);

		void setAngularVelocity(const double x, const double y, const double z = 0);
		void setAngularVelocity(const Vector3D & angularVelocity);

		void setAngularAcceleration(const double x, const double y, const double z = 0);
		void setAngularAcceleration(const Vector3D & angularAcceleration);

		void setOrientationMatrix(const std::vector<Vector3D> & orientationMatrix); // throws

		void setOrientationDerivative(const int derivative, const double x, const double y, const double z = 0); // throws
		void setOrientationDerivative(const int derivative, const Vector3D & vec); // throws

		Vector3D getOrientation() const;
		Vector3D getAngularVelocity() const;
		Vector3D getAngularAcceleration() const;

		std::vector<Vector3D> getOrientationMatrix(void) const;
		Vector3D getOrientationDerivative(const int derivative) const; // throws
		

		// ----- Taylor Order -----
		void setTaylorOrder(const int taylorOrder); // throws
		int getTaylorOrder() const;


	private:
		// memory function
		void resizePositionOrientation(void);

		// set spatial position
		void setSpatial(std::vector<Vector3D> & spatial, const int derivative, const double x, const double y, const double z = 0);
		void setSpatial(std::vector<Vector3D> & spatial, const int derivative, const Vector3D & vec);
		void setSpatial(std::vector<Vector3D> & spatialToSet, const std::vector<Vector3D> & spatial);

		std::vector<Vector3D>	positionMatrix;
		std::vector<Vector3D>	orientationMatrix;

		int taylorOrder;
};

#endif
