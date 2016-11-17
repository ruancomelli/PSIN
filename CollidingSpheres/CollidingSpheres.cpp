// Standard
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdio>

// EntityLib
#include <Particle.h>
#include <SphericalParticle.h>

// UtilsLib
#include <Vector.h>
#include <setVector.h>
#include <Mathematics.h>
#include <Foreach.h>

// ForceModelLib
#include <ForceModel.h>

// boost
#include <boost/math/constants/constants.hpp>

using namespace std;

using boost::math::constants::pi;

int main(int argc, char **argv){

	int defaultDimension = 3; // This means that we are constraint to Vector3D

	// TESTING!!!
	// Input

	//
	
	// Initialize gravity
	Vector3D gravity(0.0, 0.0, 0.0);
	
	// Simulation data
	double initialTime = 0.0;
	double timeStep = 0.000001;
	double finalTime = 0.02;
	
	int taylorOrder = 3;
	int dimension = 3;
	
	int numberOfParticles = 2;

	// Initialize particles
	
	SphericalParticle particle1( taylorOrder, dimension, 1 );
	SphericalParticle particle2( taylorOrder, dimension, 2 );

	particle1.setPosition(0, 0.0, 0.0, 0.0);
	particle1.setPosition(1, 10.0, 0.0, 0.0);
	particle1.setPosition(2, 0.0, 0.0, 0.0);
		
	particle2.setPosition(0, 0.1, 0.0, 0.0);
	particle2.setPosition(1, 0.0, 0.0, 0.0);
	particle2.setPosition(2, 0.0, 0.0, 0.0);

	particle1.setOrientation(0, 0.0, 0.0, 0.0);
	particle1.setOrientation(1, 0.0, 0.0, 1e+6);
	particle1.setOrientation(2, 0.0, 0.0, 0.0);
		
	particle2.setOrientation(0, 0.0, 0.0, 0.0);
	particle2.setOrientation(1, 0.0, 0.0, 1e+6);
	particle2.setOrientation(2, 0.0, 0.0, 0.0);

	particle1.setGeometricParameter( RADIUS, 0.010 );
	particle2.setGeometricParameter( RADIUS, 0.005 );

	particle1.setScalarProperty(MASS, 0.001);
	particle2.setScalarProperty(MASS, 0.0002);

	double m1 = particle1.getGeometricParameter( MASS );
	double m2 = particle2.getGeometricParameter( MASS );

	double r1 = particle1.getGeometricParameter( RADIUS );
	double r2 = particle2.getGeometricParameter( RADIUS );

	particle1.setScalarProperty( MOMENT_OF_INERTIA, 2 * m1 * r1*r1 / 5 );
	particle2.setScalarProperty( MOMENT_OF_INERTIA, 2 * m2 * r2*r2 / 5 );

	particle1.setScalarProperty( VOLUME, 4 * pi<double>() * r1*r1*r1 / 3 );
	particle2.setScalarProperty( VOLUME, 4 * pi<double>() * r2*r2*r2 / 3 );

	particle1.setScalarProperty( DISSIPATIVE_CONSTANT, 0.0 );	// A
	particle2.setScalarProperty( DISSIPATIVE_CONSTANT, 0.0 );

	particle1.setScalarProperty( POISSON_RATIO, 0.3 );			// \nu
	particle2.setScalarProperty( POISSON_RATIO, 0.4 );

	particle1.setScalarProperty( ELASTIC_MODULUS, 1e+6 );		// E or Y
	particle2.setScalarProperty( ELASTIC_MODULUS, 1e+5 );

	particle1.setScalarProperty( TANGENTIAL_DAMPING, 0.8 );		// \gamma
	particle2.setScalarProperty( TANGENTIAL_DAMPING, 0.7 );

	particle1.setScalarProperty( FRICTION_PARAMETER, 0.5 );		// \mu
	particle2.setScalarProperty( FRICTION_PARAMETER, 0.6 );

	vector <SphericalParticle*> particleVector;
	particleVector.resize(2);
	particleVector[0] = &particle1;
	particleVector[1] = &particle2;
	
	// Output
	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile("../_output/output.txt");
	mainOutFile << "Number of Particles = " << numberOfParticles << verticalSeparator;
	mainOutFile << "Particle1: Radius = "<< particle1.getGeometricParameter(RADIUS) << verticalSeparator;
	mainOutFile << "Particle2: Radius = "<< particle2.getGeometricParameter(RADIUS) << verticalSeparator;

	mainOutFile << "Initial Time Instant = " << initialTime << verticalSeparator;
	mainOutFile << "Time Step = " << timeStep << verticalSeparator;
	mainOutFile << "Final Time Instant = " << finalTime << verticalSeparator;

	mainOutFile << "Taylor Expansion Order = " << taylorOrder << verticalSeparator;

	string outputTimeLabel = "Time: ";
	string outputPositionLabel = "r";

	ofstream outFile1("../_output/output1.txt");
	ofstream outFile2("../_output/output2.txt");
	
	outFile1 << 0 << verticalSeparator;
	outFile2 << 0 << verticalSeparator;

	// Prints every derivative of particles' position
	for(int i = 0 ; i <= taylorOrder ; ++i ){
		
		// Saves each component of the i-th derivative of the positions
		/*particle1.fwritePosition(outFile1, horizontalSeparator, verticalSeparator);
		particle2.fwritePosition(outFile2, horizontalSeparator, verticalSeparator);*/
		
		outFile1 << horizontalSeparator << particle1.getPosition(i).x();
		outFile2 << horizontalSeparator << particle2.getPosition(i).x();
		outFile1 << horizontalSeparator << particle1.getPosition(i).y();
		outFile2 << horizontalSeparator << particle2.getPosition(i).y();
		outFile1 << horizontalSeparator << particle1.getPosition(i).z();
		outFile2 << horizontalSeparator << particle2.getPosition(i).z();
		
		outFile1 << verticalSeparator;
		outFile2 << verticalSeparator;
	}
	outFile1 << verticalSeparator;
	outFile2 << verticalSeparator;
	
	// Simulation
	for(double t = initialTime; t <= finalTime - timeStep ; t += timeStep){

		// Set forces and torques to zero
		foreach( SphericalParticle* particle, particleVector ){
			particle->setResultingForce( nullVector3D() );
			particle->setResultingTorque( nullVector3D() );
		}

		// Body forces
		foreach( SphericalParticle* particle, particleVector ){
			particle->addForce(particle->getScalarProperty(MASS) * gravity);
		}

		// Contact forces
		if(particle1.touch(particle2))	// If particles are in touch
		{
			cout << "Collision Instant: " << t << endl;

			particle1.setPosition( ForceModel::taylorPredictor( particle1.getPosition(), taylorOrder, timeStep ) );
			particle2.setPosition( ForceModel::taylorPredictor( particle2.getPosition(), taylorOrder, timeStep ) );

			particle1.setOrientation( ForceModel::taylorPredictor( particle1.getOrientation(), taylorOrder, timeStep ) );
			particle2.setOrientation( ForceModel::taylorPredictor( particle2.getOrientation(), taylorOrder, timeStep ) );

			ForceModel::viscoelasticSpheres( particle1, particle2 );

			ForceModel::correctPosition( particle1 , taylorOrder, timeStep );
			ForceModel::correctPosition( particle2 , taylorOrder, timeStep );
			
			ForceModel::correctOrientation( particle1 , taylorOrder, timeStep );
			ForceModel::correctOrientation( particle2 , taylorOrder, timeStep );
		}
		else
		{
			particle1.setPosition(ForceModel::taylorPredictor( particle1.getPosition(), 2, timeStep ));
			particle2.setPosition(ForceModel::taylorPredictor( particle2.getPosition(), 2, timeStep ));

			particle1.setOrientation( ForceModel::taylorPredictor( particle1.getOrientation(), 2, timeStep ) );
			particle2.setOrientation( ForceModel::taylorPredictor( particle2.getOrientation(), 2, timeStep ) );

			ForceModel::correctPosition( particle1 , taylorOrder, timeStep );
			ForceModel::correctPosition( particle2 , taylorOrder, timeStep );

			ForceModel::correctOrientation( particle1 , taylorOrder, timeStep );
			ForceModel::correctOrientation( particle2 , taylorOrder, timeStep );
		}


		// ----- Saving to file -----

		outFile1 << t + timeStep << verticalSeparator;
		outFile2 << t + timeStep << verticalSeparator;

		// Prints every derivative of particles' position
		for(int i = 0 ; i <= taylorOrder ; ++i ){
			
			// Saves each component of the i-th derivative of the positions
			/*particle1.fwritePosition(outFile1, horizontalSeparator, verticalSeparator);
			particle2.fwritePosition(outFile2, horizontalSeparator, verticalSeparator);*/
			
			outFile1 << horizontalSeparator << particle1.getPosition(i).x();
			outFile2 << horizontalSeparator << particle2.getPosition(i).x();
			outFile1 << horizontalSeparator << particle1.getPosition(i).y();
			outFile2 << horizontalSeparator << particle2.getPosition(i).y();
			outFile1 << horizontalSeparator << particle1.getPosition(i).z();
			outFile2 << horizontalSeparator << particle2.getPosition(i).z();
			
			outFile1 << verticalSeparator;
			outFile2 << verticalSeparator;
		}
		outFile1 << verticalSeparator;
		outFile2 << verticalSeparator;
	}
	
	outFile1.close();
	outFile2.close();
	
	cout << endl << "Success" << endl << endl;
}
