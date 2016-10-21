#include <ForceModel.h>

// Normal Force Model
// Linear Dashpot Force
// Every comment in here may be related to the book Computational Granular Dynamics


/* taylorPredictor: Let f: A -> R^k be a function of class C^n, where A is in R. Let t be in A, and define
		currentVector = (f(t), f'(t), f''(t), ..., f^(n)(t))
		Given dt in R, Taylor theorem says that
		f(t + dt) = f(t) + dt * f'(t) + (1/2) * dt^2 * f''(t) + ... + (1/n!) * dt^n * f^(n)(t) + r(dt)	,
		where r is a function such that the limit of r(h) when h tends to zero is zero
		For a sufficiently small dt, we can approximate f(t+dt) by its expansion is Taylor's sum and writing r = 0
		The following function then calculates a new vector (f(t+dt), f'(t+dt), f''(t+dt), ..., f^(n)(t+dt)).
*/
vector<Vector3D> ForceModel::taylorPredictor( const vector<Vector3D> currentVector, const int predictionOrder, const double dt ){
	// predictionOrder is the order of the derivatives to be computed.
	// dt is the time step for the predictionOrder
	// currentVector is a matrix of size predictionOrder X nDimensions, where nDimensions is the number of dimensions of the function to be predicted

	// This algorithm is an implementation of equation (2.24) (see reference)

	vector<Vector3D> predictedVector;
	Vector3D taylorExpansion;

	int nDimensions = 3;

	// initialize predictedVector and taylorExpansion
	predictedVector.resize( predictionOrder + 1 );

	// predict position
	for( int i = 0; i <= predictionOrder; ++i ){

		// set each entry of taylorExpansion to zero
		taylorExpansion.x() = 0.0;
		taylorExpansion.y() = 0.0;
		taylorExpansion.z() = 0.0;

		// perform summation
		for( int j = i; j <= predictionOrder; ++j ){
			taylorExpansion += ( pow( dt , j - i) / factorial( j - i ) ) * currentVector[j];
		}

		// set the i-th predicted derivative as the calculated Taylor expansion
		predictedVector[i] = taylorExpansion;

	}

	return predictedVector;
}


vector<Vector3D> ForceModel::gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt){

	vector<Vector3D> correctedVector = predictedVector;
	DoubleVector correctorConstants(predictionOrder + 1);

	switch(predictionOrder){
		case 3:
			correctorConstants[0] = 1./6.;
			correctorConstants[1] = 5./6.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 1./3.;
			break;
		case 4:
			correctorConstants[0] = 19./90.;
			correctorConstants[1] = 3./4.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 1./2.;
			correctorConstants[4] = 1./12.;
			break;
		case 5:
			correctorConstants[0] = 3./16.;
			correctorConstants[1] = 251./360.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 11./18.;
			correctorConstants[4] = 1./6.;
			correctorConstants[5] = 1./60.;
			break;
		default:
			throw runtime_error("There is no support for this prediction order");
			return predictedVector;
	}

	for(int i = 0 ; i <= predictionOrder ; ++i){
		correctedVector[i] += (correctorConstants[i] * ( factorial(i) / pow(dt, i) ) * (pow(dt, 2) / 2.0) ) * doubleDerivative;
	}

	return correctedVector;
}

Vector3D ForceModel::viscoelasticSpheres(SphericalParticle particle1, SphericalParticle particle2)
{	
	Vector3D force;

	// Getting particles properties and parameters
	Vector3D positionParticle1 = particle1.getPosition(0);
	Vector3D positionParticle2 = particle2.getPosition(0);
	double distance = positionParticle1.dist(positionParticle2);
	double radius1 = particle1.getGeometricParameter(RADIUS);
	double radius2 = particle2.getGeometricParameter(RADIUS);
	double effectiveRadius = radius1 * radius2 / ( radius1 + radius2 );
	
	// Calculations
	double overlap = radius1 + radius2 - distance;
	
	if(overlap > 0)
	{
		
	}
	else
	{
		force = nullVector3D();
	}
	// Change this:
	return force;
}

// This is the code presented by the authors:
/*
  double dx=normalize(p1.x()-p2.x(),lx);
  double dy=normalize(p1.y()-p2.y(),ly);
  double rr=sqrt(dx*dx+dy*dy);
  double r1=p1.r();
  double r2=p2.r();
  double xi=r1+r2-rr;

  if(xi>0){
	  
    double Y = p1.Y * p2.Y / ( p1.Y + p2.Y );
    double A = 0.5 * (p1.A + p2.A);
    double mu = ( p1.mu < p2.mu ? p1.mu : p2.mu );
    double gamma = ( p1.gamma < p2.gamma ? p1.gamma : p2.gamma );
    double reff = (r1*r2)/(r1+r2);
    double dvx = p1.vx()-p2.vx();
    double dvy = p1.vy()-p2.vy();
    double rr_rez = 1/rr;
    double ex = dx*rr_rez;
    double ey = dy*rr_rez;
    double xidot = -(ex*dvx+ey*dvy);
    double vtrel = -dvx*ey + dvy*ex + p1.omega()*p1.r()-p2.omega()*p2.r();
    double fn = sqrt(xi)*Y*sqrt(reff)*(xi+A*xidot);
    double ft = -gamma*vtrel;

    if(fn<0) fn=0;
	
    if(ft<-mu*fn) ft=-mu*fn;
	
    if(ft>mu*fn) ft=mu*fn;
	
    if(p1.ptype()==0) {
      p1.add_force(Vector(fn*ex-ft*ey, fn*ey+ft*ex, r1*ft));
    }
	
    if(p2.ptype()==0) {
      p2.add_force(Vector(-fn*ex+ft*ey, -fn*ey-ft*ex, -r2*ft));
    }
  }
 */








/*

DoubleVector ForceModel::linearDashpotForce(Particle particle1, Particle particle2, string method, string interaction ){
	// particle1 and particle2 are the particles between which the interaction must be calculated
	// mehtod specifies which discretization method must be used
	// method must be "Integral"
	// In the future, method should be able to be "FiniteDifference"
	// interaction specifies the kind of interaction that must be calculated
	// interaction must be "Impulse"
	// In the future, interaction should be able to be "Force"

	transform(interaction.begin(), interaction.end(), interaction.begin(), toupper);

	vector <double> normalInteraction;

	normalInteraction.resize(3);

	if (interaction.compare("IMPULSE") == 0)
		normalInteraction = linearDashpotForceImpulseCalculationViaIntegration(particle1, particle2, method);
	else if (interaction.compare("FORCE") == 0)
		normalInteraction = linearDashpotForceForceCalculationViaIntegration(particle1, particle2, method);

	return normalInteraction;
}

DoubleVector ForceModel::linearDashpotForceImpulseCalculationViaIntegration(Particle particle1, Particle particle2, string method){

}

DoubleVector linearDashpotForceForceCalculationViaIntegration(Particle particle1, Particle particle2, string method){

}

*/
