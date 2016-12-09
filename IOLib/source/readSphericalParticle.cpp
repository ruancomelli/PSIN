#include <readSphericalParticle.h>

SphericalParticle readSphericalParticle( string & fileName )
{
	FileReader fileReader(fileName);

	// ----- Read Particle -----
	Particle particle = readParticle(fileName);
	
	// ----- Read SphericalParticle -----
	SphericalParticle sphericalParticle(particle);

	DoubleVector geometricParameter(N_GEOMETRIC_PARAMETER);
	fileReader.readValue("<Radius>", geometricParameter[RADIUS]);

	sphericalParticle.setGeometricParameter(geometricParameter);

	return sphericalParticle;
}