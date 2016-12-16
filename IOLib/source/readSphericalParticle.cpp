#include <readSphericalParticle.h>

SphericalParticlePtr readSphericalParticle( string & fileName )
{
	FileReader fileReader(fileName);

	// ----- Read Particle -----
	Particle particle = readParticle(fileName);
	
	// ----- Read SphericalParticle -----
	SphericalParticlePtr sphericalParticlePtr( new SphericalParticle(particle) );

	DoubleVector geometricParameter(N_GEOMETRIC_PARAMETER);
	fileReader.readValue("<Radius>", geometricParameter[RADIUS]);

	sphericalParticlePtr->setGeometricParameter(geometricParameter);

	return sphericalParticlePtr;
}