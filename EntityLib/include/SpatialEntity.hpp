#ifndef SPATIAL_ENTITY_HPP
#define SPATIAL_ENTITY_HPP

// UtilsLib
#include <Quaternion.hpp>
#include <Vector3D.hpp>

// JSONLib
#include <json.hpp>

// Standard
#include <vector>

#define DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER 4

namespace psin {

class SpatialEntity
{
	public:
		SpatialEntity();
		explicit SpatialEntity(const std::size_t taylorOrder);

		// ----- Position -----
		void setPosition(const double x, const double y, const double z = 0);
		void setPosition(const Vector3D & position);

		void setVelocity(const double x, const double y, const double z = 0);
		void setVelocity(const Vector3D & velocity);

		void setAcceleration(const double x, const double y, const double z = 0);
		void setAcceleration(const Vector3D & acceleration);

		void setPositionMatrix(const std::vector<Vector3D> & positionMatrix); // throws

		void setPositionDerivative(const std::size_t derivative, const double x, const double y, const double z = 0); // throws
		void setPositionDerivative(const std::size_t derivative, const Vector3D & vec); // throws

		Vector3D getPosition() const;
		Vector3D getVelocity() const;
		Vector3D getAcceleration() const;

		std::vector<Vector3D> getPositionMatrix(void) const;
		Vector3D getPositionDerivative(const std::size_t derivative) const; // throws


		// ----- Orientation -----
		void setOrientation(const double x, const double y, const double z = 0);
		void setOrientation(const Vector3D & orientation);

		void setAngularVelocity(const double x, const double y, const double z = 0);
		void setAngularVelocity(const Vector3D & angularVelocity);

		void setAngularAcceleration(const double x, const double y, const double z = 0);
		void setAngularAcceleration(const Vector3D & angularAcceleration);

		void setOrientationMatrix(const std::vector<Quaterniond> & orientationMatrix); // throws

		void setOrientationDerivative(const std::size_t derivative, const double x, const double y, const double z = 0); // throws
		void setOrientationDerivative(const std::size_t derivative, const Vector3D & vec); // throws
		void setOrientationDerivative(const std::size_t derivative, const Quaterniond & q); // throws

		Vector3D getOrientation() const;
		Vector3D getAngularVelocity() const;
		// Vector3D getAngularAcceleration() const;

		std::vector<Quaterniond> getOrientationMatrix(void) const;
		Quaterniond getOrientationDerivative(const std::size_t derivative) const; // throws

		// ----- Taylor Order -----
		void setTaylorOrder(const std::size_t taylorOrder); // throws
		std::size_t getTaylorOrder() const;


	private:
		// memory function
		void resizePositionOrientation(void);

		// set spatial position
		void setSpatial(std::vector<Vector3D> & spatial, const std::size_t derivative, const double x, const double y, const double z = 0);
		void setSpatial(std::vector<Vector3D> & spatial, const std::size_t derivative, const Vector3D & vec);
		void setSpatial(std::vector<Vector3D> & spatialToSet, const std::vector<Vector3D> & spatial);

		std::vector<Vector3D>	positionMatrix;
		std::vector<Quaterniond>	orientationMatrix;

		std::size_t taylorOrder;
};

void from_json(const json& j, SpatialEntity &);
void to_json(json& j, const SpatialEntity &);

double distance(const SpatialEntity & left, const SpatialEntity & right);	// distance function. Must be specialized for every pair of types

Vector3D normalVersor(const SpatialEntity & lhs, const SpatialEntity & rhs);

} // psin

#endif
