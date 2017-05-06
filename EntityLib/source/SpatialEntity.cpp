#include <SpatialEntity.hpp>

// Standard
#include <stdexcept>

SpatialEntity::SpatialEntity()
{
	this->setTaylorOrder(DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
}

SpatialEntity::SpatialEntity(const int taylorOrder)
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

void SpatialEntity::setPositionDerivative(const int derivative, const double x, const double y, const double z)
{
	this->setSpatial(this->positionMatrix, derivative, x, y, z);
}

void SpatialEntity::setPositionDerivative(const int derivative, const Vector3D & vec)
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

Vector3D SpatialEntity::getPositionDerivative(const int derivative) const
{
	if(derivative < 0 || derivative > this->taylorOrder)
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

void SpatialEntity::setOrientationDerivative(const int derivative, const double x, const double y, const double z)
{
	this->setSpatial(this->orientationMatrix, derivative, x, y, z);
}

void SpatialEntity::setOrientationDerivative(const int derivative, const Vector3D & vec)
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

Vector3D SpatialEntity::getOrientationDerivative(const int derivative) const
{
	if(derivative < 0 || derivative > this->taylorOrder)
	{
		throw std::runtime_error("Invalid derivative inserted. Derivative must be positive and less or equal to taylorOrder");
	}
	else
	{
		return this->orientationMatrix[derivative];
	}
}

void SpatialEntity::setSpatial(std::vector<Vector3D> & spatial, const int derivative, const double x, const double y, const double z)
{
	if(derivative < 0 || derivative > this->taylorOrder)
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

void SpatialEntity::setSpatial(std::vector<Vector3D> & spatial, const int derivative, const Vector3D & vec)
{
	if(derivative < 0 || derivative > this->taylorOrder)
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

void SpatialEntity::setTaylorOrder(const int taylorOrder)
{
	if(taylorOrder < 3 || taylorOrder > 5)
	{
		throw std::runtime_error("Invalid taylorOrder inserted. taylorOrder must be either 3, 4 or 5.");
	}
	else
	{
		this->taylorOrder = taylorOrder;
		resizePositionOrientation();
	}
}

int SpatialEntity::getTaylorOrder() const
{
	return this->taylorOrder;
}

void SpatialEntity::resizePositionOrientation()
{
	int size = taylorOrder + 1;
	this->positionMatrix.resize(size);
	this->orientationMatrix.resize(size);
}

double distance(const SpatialEntity & left, const SpatialEntity & right)
{
	return (left.getPosition() - right.getPosition()).length();
}
