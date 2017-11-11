#include <SpatialEntity.hpp>

// Standard
#include <stdexcept>

namespace psin {

void from_json(const json& j, SpatialEntity & spatial)
{
	if(j.count("PositionMatrix") > 0)
	{
		spatial.setPositionMatrix(j.at("PositionMatrix"));
	}
	if(j.count("OrientationMatrix") > 0)
	{
		spatial.setOrientationMatrix(j.at("OrientationMatrix"));
	}
	if(j.count("Position") > 0) spatial.setPosition(j.at("Position").get<Vector3D>());
	if(j.count("Velocity") > 0) spatial.setVelocity(j.at("Velocity").get<Vector3D>());
	if(j.count("Acceleration") > 0) spatial.setAcceleration(j.at("Acceleration").get<Vector3D>());
	
	if(j.count("Orientation") > 0) spatial.setOrientation(j.at("Orientation").get<Vector3D>());
	if(j.count("AngularVelocity") > 0) spatial.setAngularVelocity(j.at("AngularVelocity").get<Vector3D>());
	if(j.count("AngularAcceleration") > 0) spatial.setAngularAcceleration(j.at("AngularAcceleration").get<Vector3D>());

	spatial.setTaylorOrder( j.at("TaylorOrder") );
}

void to_json(json& j, const SpatialEntity & spatial)
{
	j["PositionMatrix"] =  spatial.getPositionMatrix();
	j["OrientationMatrix"] =  spatial.getOrientationMatrix();

	j["Position"] = spatial.getPosition();
	j["Position - X"] = spatial.getPosition().x();
	j["Position - Y"] = spatial.getPosition().y();
	j["Position - Z"] = spatial.getPosition().z();
	j["Velocity"] = spatial.getVelocity();
	j["Velocity - X"] = spatial.getVelocity().x();
	j["Velocity - Y"] = spatial.getVelocity().y();
	j["Velocity - Z"] = spatial.getVelocity().z();
	j["Acceleration"] = spatial.getAcceleration();
	j["Acceleration - X"] = spatial.getAcceleration().x();
	j["Acceleration - Y"] = spatial.getAcceleration().y();
	j["Acceleration - Z"] = spatial.getAcceleration().z();

	j["Orientation"] = spatial.getOrientation();
	j["Orientation - X"] = spatial.getOrientation().x();
	j["Orientation - Y"] = spatial.getOrientation().y();
	j["Orientation - Z"] = spatial.getOrientation().z();
	j["AngularVelocity"] = spatial.getAngularVelocity();
	j["AngularVelocity - X"] = spatial.getAngularVelocity().x();
	j["AngularVelocity - Y"] = spatial.getAngularVelocity().y();
	j["AngularVelocity - Z"] = spatial.getAngularVelocity().z();
	j["AngularAcceleration"] = spatial.getAngularAcceleration();
	j["AngularAcceleration - X"] = spatial.getAngularAcceleration().x();
	j["AngularAcceleration - Y"] = spatial.getAngularAcceleration().y();
	j["AngularAcceleration - Z"] = spatial.getAngularAcceleration().z();

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
	spatialToSet = spatial;
	spatialToSet.resize(this->taylorOrder+1);
	// if( spatial.size() != (this->taylorOrder + 1) )
	// {
	// 	throw std::runtime_error("taylorOrder does not match spatial's size in function SpatialEntity::setSpatial(vector<Vector3D> & spatialToSet, const vector<Vector3D> & spatial)");
	// }
	// else
	// {
	// 	spatialToSet = spatial;
	// }
}

void SpatialEntity::setTaylorOrder(const std::size_t taylorOrder)
{
	this->taylorOrder = taylorOrder;
	resizePositionOrientation();
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

Vector3D normalVersor(const SpatialEntity & lhs, const SpatialEntity & rhs)
{
	return (rhs.getPosition() - lhs.getPosition()).normalized();
}

} // psin
