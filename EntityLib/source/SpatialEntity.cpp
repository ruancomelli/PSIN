#include <SpatialEntity.hpp>

// Standard
#include <stdexcept>

namespace psin {

void from_json(const json& j, SpatialEntity & spatial)
{
	if(j.at("PositionMatrix").size() != j.at("OrientationMatrix").size())
	{
		throw std::runtime_error("PositionMatrix and OrientationMatrix must have the same size");
	}

	spatial.setTaylorOrder( j.at("PositionMatrix").size() - 1 );
	spatial.setPositionMatrix(j.at("PositionMatrix"));
	spatial.setOrientationMatrix(j.at("OrientationMatrix"));
}

void to_json(json& j, const SpatialEntity & spatial)
{
	j["PositionMatrix"] =  spatial.getPositionMatrix();
	j["OrientationMatrix"] =  spatial.getOrientationMatrix();

	j["Position"] =  spatial.getPosition();
	j["Velocity"] =  spatial.getVelocity();
	j["Acceleration"] =  spatial.getAcceleration();

	j["Orientation"] =  spatial.getOrientation();
	j["AngularVelocity"] =  spatial.getAngularVelocity();
	j["AngularAcceleration"] =  spatial.getAngularAcceleration();

	j["TaylorOrder"] = spatial.getTaylorOrder();
}

SpatialEntity::SpatialEntity()
{
	this->setTaylorOrder(DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
}

SpatialEntity::SpatialEntity(const std::size_t taylorOrder)
{
	this->setTaylorOrder(taylorOrder);
}

void SpatialEntity::setPosition(const double x, const double y, const double z)
{
	this->setSpatial(this->positionMatrix, 0, x, y, z);
}

void SpatialEntity::setPosition(const Vector3D & position)
{
	this->setSpatial(this->positionMatrix, 0, position);
}

void SpatialEntity::setVelocity(const double u, const double v, const double w)
{
	this->setSpatial(this->positionMatrix, 1, u, v, w);
}

void SpatialEntity::setVelocity(const Vector3D & velocity)
{
	this->setSpatial(this->positionMatrix, 1, velocity);
}

void SpatialEntity::setAcceleration(const double x, const double y, const double z)
{
	this->setSpatial(this->positionMatrix, 2, x, y, z);
}

void SpatialEntity::setAcceleration(const Vector3D & acceleration)
{
	this->setSpatial(this->positionMatrix, 2, acceleration);
}

void SpatialEntity::setPositionMatrix(const std::vector<Vector3D> & positionMatrix)
{
	this->setSpatial(this->positionMatrix, positionMatrix);
}

void SpatialEntity::setPositionDerivative(const std::size_t derivative, const double x, const double y, const double z)
{
	this->setSpatial(this->positionMatrix, derivative, x, y, z);
}

void SpatialEntity::setPositionDerivative(const std::size_t derivative, const Vector3D & vec)
{
	this->setSpatial(this->positionMatrix, derivative, vec);
}

Vector3D SpatialEntity::getPosition() const
{
	return this->positionMatrix[0];
}

Vector3D SpatialEntity::getVelocity() const
{
	return this->positionMatrix[1];
}

Vector3D SpatialEntity::getAcceleration() const
{
	return this->positionMatrix[2];
}

std::vector<Vector3D> SpatialEntity::getPositionMatrix(void) const
{
	return this->positionMatrix;
}

Vector3D SpatialEntity::getPositionDerivative(const std::size_t derivative) const
{
	if(derivative > this->taylorOrder)
	{
		throw std::runtime_error("Invalid derivative inserted. Derivative must be positive and less or equal to taylorOrder");
	}
	else
	{
		return this->positionMatrix[derivative];
	}
}



void SpatialEntity::setOrientation(const double x, const double y, const double z)
{
	this->setSpatial(this->orientationMatrix, 0, x, y, z);
}

void SpatialEntity::setOrientation(const Vector3D & orientation)
{
	this->setSpatial(this->orientationMatrix, 0, orientation);
}

void SpatialEntity::setAngularVelocity(const double x, const double y, const double z)
{
	this->setSpatial(this->orientationMatrix, 1, x, y, z);
}

void SpatialEntity::setAngularVelocity(const Vector3D & angularVelocity)
{
	this->setSpatial(this->orientationMatrix, 1, angularVelocity);
}

void SpatialEntity::setAngularAcceleration(const double x, const double y, const double z)
{
	this->setSpatial(this->orientationMatrix, 2, x, y, z);
}

void SpatialEntity::setAngularAcceleration(const Vector3D & angularAcceleration)
{
	this->setSpatial(this->orientationMatrix, 2, angularAcceleration);
}

void SpatialEntity::setOrientationMatrix(const std::vector<Vector3D> & orientationMatrix)
{
	this->setSpatial(this->orientationMatrix, orientationMatrix);
}

void SpatialEntity::setOrientationDerivative(const std::size_t derivative, const double x, const double y, const double z)
{
	this->setSpatial(this->orientationMatrix, derivative, x, y, z);
}

void SpatialEntity::setOrientationDerivative(const std::size_t derivative, const Vector3D & vec)
{
	this->setSpatial(this->orientationMatrix, derivative, vec);
}

Vector3D SpatialEntity::getOrientation() const
{
	return this->orientationMatrix[0];
}

Vector3D SpatialEntity::getAngularVelocity() const
{
	return this->orientationMatrix[1];
}

Vector3D SpatialEntity::getAngularAcceleration() const
{
	return this->orientationMatrix[2];
}

std::vector<Vector3D> SpatialEntity::getOrientationMatrix(void) const
{
	return this->orientationMatrix;
}

Vector3D SpatialEntity::getOrientationDerivative(const std::size_t derivative) const
{
	if(derivative > this->taylorOrder)
	{
		throw std::runtime_error("Invalid derivative inserted. Derivative must be positive and less or equal to taylorOrder");
	}
	else
	{
		return this->orientationMatrix[derivative];
	}
}

Vector3D SpatialEntity::normalVersor( const SpatialEntity & neighbor ) const
{
	Vector3D normalDirection = (neighbor.getPosition() - this->getPosition()).normalized();
	return normalDirection;
}

void SpatialEntity::setSpatial(std::vector<Vector3D> & spatial, const std::size_t derivative, const double x, const double y, const double z)
{
	if(derivative > this->taylorOrder)
	{
		throw std::runtime_error("Invalid derivative inserted. Derivative must be positive and less or equal to taylorOrder");
	}
	else
	{
		spatial[derivative].x() = x;
		spatial[derivative].y() = y;
		spatial[derivative].z() = z;
	}
}

void SpatialEntity::setSpatial(std::vector<Vector3D> & spatial, const std::size_t derivative, const Vector3D & vec)
{
	if(derivative > this->taylorOrder)
	{
		throw std::runtime_error("Invalid derivative inserted. Derivative must be positive and less or equal to taylorOrder");
	}
	else
	{
		spatial[derivative] = vec;
	}
}

void SpatialEntity::setSpatial(std::vector<Vector3D> & spatialToSet, const std::vector<Vector3D> & spatial)
{
	if( spatial.size() != (this->taylorOrder + 1) )
	{
		throw std::runtime_error("taylorOrder does not match spatial's size in function SpatialEntity::setSpatial(vector<Vector3D> & spatialToSet, const vector<Vector3D> & spatial)");
	}
	else
	{
		spatialToSet = spatial;
	}
}

void SpatialEntity::setTaylorOrder(const std::size_t taylorOrder)
{
	if(taylorOrder < 3 or taylorOrder > 5)
	{
		throw std::runtime_error("Invalid taylorOrder inserted. taylorOrder must be either 3, 4 or 5.");
	}
	else
	{
		this->taylorOrder = taylorOrder;
		resizePositionOrientation();
	}
}

std::size_t SpatialEntity::getTaylorOrder() const
{
	return this->taylorOrder;
}

void SpatialEntity::resizePositionOrientation()
{
	std::size_t size = taylorOrder + 1;
	this->positionMatrix.resize(size);
	this->orientationMatrix.resize(size);
}

double distance(const SpatialEntity & left, const SpatialEntity & right)
{
	return (left.getPosition() - right.getPosition()).length();
}

} // psin
