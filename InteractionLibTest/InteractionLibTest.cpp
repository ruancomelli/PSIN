#define BOOST_TEST_MODULE InteractionLibTest

// UtilsLib
#include <Mathematics.hpp>
#include <Vector3D.hpp>
#include <Vector.hpp>
#include <Test.hpp>
#include <Foreach.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

//EntityLib
#include <Particle.hpp>
#include <PhysicalEntity.hpp>
#include <SphericalParticle.hpp>

//InteractionLib
#include <Interaction.hpp>
#include <InteractionDefinitions.hpp>

// IOLib
// #include <vectorIO.hpp>

using namespace std;
using namespace PropertyDefinitions;

TestCase( TaylorPredictor_Test )
{
		int predictionOrder = 2;
		double dx = 0.5;

		vector<Vector3D> currentVector(predictionOrder+1);
		currentVector[0].x() = 1.0;
		currentVector[1].x() = 3.0;
		currentVector[2].x() = 15.0;
		currentVector[0].y() = 4.0;
		currentVector[1].y() = -5.0;
		currentVector[2].y() = 8.0;
		currentVector[0].z() = -1.0;
		currentVector[1].z() = 2.0;
		currentVector[2].z() = -5.0;

		vector<Vector3D> solution(predictionOrder+1);
		solution[0].x() = 4.375;
		solution[1].x() = 10.5;
		solution[2].x() = 15.0;
		solution[0].y() = 2.5;
		solution[1].y() = -1.0;
		solution[2].y() = 8.0;
		solution[0].z() = -0.625;
		solution[1].z() = -0.5;
		solution[2].z() = -5.0;

		vector<Vector3D> predictedVector = Interaction<>::taylorPredictor( currentVector, predictionOrder, dx );

		for(int i=0 ; i<=predictionOrder ; ++i)
		{
			checkEqual( predictedVector[i].x(), solution[i].x() );
			checkEqual( predictedVector[i].y(), solution[i].y() );
			checkEqual( predictedVector[i].z(), solution[i].z() );
		}
}

TestCase(RequireProperties_Test)
{
	// check((
	// 	Interaction<Mass, Volume>::has_required_properties< SphericalParticle<Volume> >
	// ));

	// check(!(
	// 	Interaction<Mass, Volume, ElectricCharge>::has_required_properties< SphericalParticle<> >
	// ));

	// fm.requireProperty(mass);
	// fm.requireProperty(volume);

	// PropertyContainer raw = fm.getRequiredProperties();

	// SharedPointer< set<string> > mySetPtr = raw.getPropertyNames();
	// set<string>::iterator it = mySetPtr->find(mass.getName());
	// set<string>::iterator it2 = mySetPtr->find(volume.getName());

	// checkEqual(*it, mass.getName());
	// checkEqual(*it2, volume.getName());
}

TestCase(ElectrostaticForce_Test)
{
	double k = 9e+9;
	double charge1 = 1.5; // [C]
	double charge2 = -1.8; // [C]
	Vector3D position1( 0.0, 0.0, 0.0 );
	Vector3D position2( 1.0, 0.0, 0.0 );

	Vector3D ResultingForceOnP1 = - k * charge1 * charge2 * Vector3D(1, 0, 0) / (position2 - position1).squaredLength();
	Vector3D ResultingForceOnP2 = - ResultingForceOnP1;

	Particle<ElectricCharge> p1;
	Particle<ElectricCharge, PoissonRatio> p2;

	p1.set<ElectricCharge>(charge1);
	p2.set<ElectricCharge>(charge2);
	p1.setPosition(position1);
	p2.setPosition(position2);

	check((
		ElectrostaticForce::check< Particle<ElectricCharge>, Particle<ElectricCharge, Volume> >::value
	));
	check(!(
		ElectrostaticForce::check< Particle<>, Particle<ElectricCharge, Volume> >::value
	));

	ElectrostaticForce::calculate(p1, p2);

	check(p1.getResultingForce() == ResultingForceOnP1);
	check(p2.getResultingForce() == ResultingForceOnP2);
}


TestCase(NormalForceLinearDashpotForce_Test)
{
	double elasticModulus1 = 1e9;
	double elasticModulus2 = 1e8;

	double normalDissipativeConstant1 = 104;
	double normalDissipativeConstant2 = 650;

	double radius1 = 0.6;
	double radius2 = 0.8;

	Vector3D position1(0.0, 0.0, 0.0);
	Vector3D position2(1.0, 0.0, 0.0);

	Vector3D velocity1(0.0, 0.0, 0.0);
	Vector3D velocity2(-1.0, 0.0, 0.0);

	SphericalParticle<ElasticModulus, NormalDissipativeConstant> p1;
	SphericalParticle<ElasticModulus, NormalDissipativeConstant, ElectricCharge> p2;

	p1.set<ElasticModulus>(elasticModulus1);
	p2.set<ElasticModulus>(elasticModulus2);

	p1.set<NormalDissipativeConstant>(normalDissipativeConstant1);
	p2.set<NormalDissipativeConstant>(normalDissipativeConstant2); 
			
	p1.set<Radius>(radius1);
	p2.set<Radius>(radius2);

	p1.setPosition(position1);
	p2.setPosition(position2);

	p1.setPosition(position1);
	p2.setPosition(position2);

	check((
		NormalForceLinearDashpotForce::check< SphericalParticle<ElasticModulus, NormalDissipativeConstant>, 
			SphericalParticle<ElasticModulus, NormalDissipativeConstant, Volume> 
			>::value
	));
	check(!(
		NormalForceLinearDashpotForce::check< Particle<NormalDissipativeConstant>, 
			Particle<ElasticModulus, Volume> 
			>::value
	));

	NormalForceLinearDashpotForce::calculate(p1, p2);

	//TODO check values
}

TestCase(NormalForceViscoelasticSpheres_Test)
{
	double elasticModulus1 = 1e9;
	double elasticModulus2 = 1e8;

	double dissipativeConstant1 = 104;
	double dissipativeConstant2 = 650;

	double poissonRatio1 = 0.3;
	double poissonRatio2 = 0.4;

	double radius1 = 0.6;
	double radius2 = 0.8;

	Vector3D position1(0.0, 0.0, 0.0);
	Vector3D position2(1.0, 0.0, 0.0);

	Vector3D velocity1(0.0, 0.0, 0.0);
	Vector3D velocity2(-1.0, 0.0, 0.0);

	SphericalParticle<ElasticModulus, DissipativeConstant, PoissonRatio> p1;
	SphericalParticle<ElasticModulus, DissipativeConstant, PoissonRatio, ElectricCharge> p2;

	p1.set<ElasticModulus>(elasticModulus1);
	p2.set<ElasticModulus>(elasticModulus2);

	p1.set<DissipativeConstant>(dissipativeConstant1);
	p2.set<DissipativeConstant>(dissipativeConstant2); 

	p1.set<PoissonRatio>(poissonRatio1);
	p2.set<PoissonRatio>(poissonRatio2); 
			
	p1.set<Radius>(radius1);
	p2.set<Radius>(radius2);

	p1.setPosition(position1);
	p2.setPosition(position2);

	p1.setVelocity(velocity1);
	p2.setVelocity(velocity2);

	check((
		NormalForceViscoelasticSpheres::check< SphericalParticle<ElasticModulus, DissipativeConstant, PoissonRatio>, 
			SphericalParticle<ElasticModulus, DissipativeConstant, Volume, PoissonRatio> 
			>::value
	));
	check(!(
		NormalForceViscoelasticSpheres::check< SphericalParticle<ElasticModulus, DissipativeConstant, PoissonRatio>, 
			Particle<ElasticModulus, Volume> 
			>::value
	));

	NormalForceViscoelasticSpheres::calculate(p1, p2);

	//TODO check values
}

TestCase(TangentialForceCundallStrack_Test)
{
	double tangentialKappa1 = 650;
	double tangentialKappa2 = 500;

	double frictionParameter1 = 0.5;
	double frictionParameter2 = 0.75;

	double radius1 = 0.6;
	double radius2 = 0.8;

	Vector3D position1(0.0, 0.0, 0.0);
	Vector3D position2(1.0, 0.0, 0.0);

	Vector3D velocity1(0.0, 0.0, 0.0);
	Vector3D velocity2(-1.0, 0.0, 0.0);

	Vector3D angularVelocity1(0.5, 0, 3);
	Vector3D angularVelocity2(-1, 0, -5);

	SphericalParticle<TangentialKappa, FrictionParameter, PoissonRatio> p1;
	SphericalParticle<TangentialKappa, FrictionParameter> p2;

	p1.set<TangentialKappa>(tangentialKappa1);
	p2.set<TangentialKappa>(tangentialKappa2);

	p1.set<FrictionParameter>(frictionParameter1);
	p2.set<FrictionParameter>(frictionParameter2); 
			
	p1.set<Radius>(radius1);
	p2.set<Radius>(radius2);

	p1.setPosition(position1);
	p2.setPosition(position2);

	p1.setVelocity(velocity1);
	p2.setVelocity(velocity2);

	p1.setAngularVelocity(angularVelocity1);
	p2.setAngularVelocity(angularVelocity2);

	Vector3D normalForce(500, 0, 0);
	double timeStep = 0.5;

	check((
		TangentialForceCundallStrack::check< SphericalParticle<TangentialKappa, FrictionParameter, PoissonRatio>, 
			SphericalParticle<TangentialKappa, ElasticModulus, DissipativeConstant, Volume, PoissonRatio, FrictionParameter> 
			>::value
	));
	check(!(
		TangentialForceCundallStrack::check< SphericalParticle<ElasticModulus, DissipativeConstant, PoissonRatio>, 
			SphericalParticle<TangentialKappa, ElasticModulus, DissipativeConstant, Volume, PoissonRatio, FrictionParameter>
			>::value
	));

	TangentialForceCundallStrack::calculate(p1, p2, normalForce, timeStep);

	//TODO check values
}

TestCase(TangentialForceHaffWerner_Test)
{
	double tangentialDamping1 = 650;
	double tangentialDamping2 = 500;

	double frictionParameter1 = 0.5;
	double frictionParameter2 = 0.75;

	double radius1 = 0.6;
	double radius2 = 0.8;

	Vector3D position1(0.0, 0.0, 0.0);
	Vector3D position2(1.0, 0.0, 0.0);

	Vector3D velocity1(0.0, 0.0, 0.0);
	Vector3D velocity2(-1.0, 0.0, 0.0);

	Vector3D angularVelocity1(0.5, 0, 3);
	Vector3D angularVelocity2(-1, 0, -5);

	SphericalParticle<TangentialDamping, FrictionParameter, PoissonRatio> p1;
	SphericalParticle<TangentialDamping, FrictionParameter> p2;

	p1.set<TangentialDamping>(tangentialDamping1);
	p2.set<TangentialDamping>(tangentialDamping2);

	p1.set<FrictionParameter>(frictionParameter1);
	p2.set<FrictionParameter>(frictionParameter2); 
			
	p1.set<Radius>(radius1);
	p2.set<Radius>(radius2);

	p1.setPosition(position1);
	p2.setPosition(position2);

	p1.setVelocity(velocity1);
	p2.setVelocity(velocity2);

	p1.setAngularVelocity(angularVelocity1);
	p2.setAngularVelocity(angularVelocity2);

	Vector3D normalForce(500, 0, 0);
	double timeStep = 0.5;
	check((
		TangentialForceHaffWerner::check< SphericalParticle<TangentialDamping, FrictionParameter, PoissonRatio>, 
			SphericalParticle<TangentialKappa, ElasticModulus, TangentialDamping, Volume, PoissonRatio, FrictionParameter> 
			>::value
	));
	check(!(
		TangentialForceHaffWerner::check< SphericalParticle<ElasticModulus, DissipativeConstant, PoissonRatio>, 
			SphericalParticle<TangentialKappa, ElasticModulus, DissipativeConstant, Volume, PoissonRatio, FrictionParameter>
			>::value
	));

	TangentialForceHaffWerner::calculate(p1, p2, normalForce, timeStep);

	//TODO check values
}

// TestCase(ConstructorsTest)
// {
// 	SphericalParticlePtr sph0( new SphericalParticle() );
// 	SphericalParticlePtr sph1( new SphericalParticle() );

// 	string defaultName = "Nameless";
// 	string name = "DarkSideOfTheForce";

// 	Interaction<SphericalParticle, SphericalParticle> fm0;
// 	fm0.calculate(sph0, sph1);
// 	checkEqual(fm0.getName(), defaultName);
// 	checkEqual(sph0->getResultingForce(), nullVector3D());
// 	checkEqual(sph1->getResultingForce(), nullVector3D());

// 	Interaction<SphericalParticle, SphericalParticle> fm1(name);
// 	fm1.calculate(sph0, sph1);
// 	checkEqual(fm1.getName(), name);
// 	checkEqual(sph0->getResultingForce(), nullVector3D());
// 	checkEqual(sph1->getResultingForce(), nullVector3D());

// 	Interaction<SphericalParticle, SphericalParticle> fm2(fm1);
// 	fm2.calculate(sph0, sph1);
// 	checkEqual(fm2.getName(), name);
// 	checkEqual(sph0->getResultingForce(), nullVector3D());
// 	checkEqual(sph1->getResultingForce(), nullVector3D());
// }

// Vector3D myNormalForce(SphericalParticlePtr sph0, SphericalParticlePtr sph1)
// {
// 	sph0->addContactForce(Vector3D(1.0, 0.0, 0.0));
// 	sph1->addContactForce(Vector3D(1.0, 0.0, 0.0));
// 	return Vector3D(1.0, 0.0, 0.0);
// }
// void myTangentialForce(SphericalParticlePtr sph0, SphericalParticlePtr sph1, Vector3D normalForce, double timeStep)
// {
// 	sph0->addContactForce(Vector3D(0.0, 1.0, 0.0));
// 	sph1->addContactForce(Vector3D(0.0, 1.0, 0.0));
// }

// TestCase(SetForceMethodsTest)
// {
// 	SphericalParticlePtr sph0(new SphericalParticle());
// 	SphericalParticlePtr sph1(new SphericalParticle());
// 	SphericalParticlePtr sph2(new SphericalParticle());
// 	SphericalParticlePtr sph3(new SphericalParticle());
// 	SphericalParticlePtr sph4(new SphericalParticle());
// 	SphericalParticlePtr sph5(new SphericalParticle());

// 	string name = "DarkSideOfTheForce";

// 	Vector3D normalForce = Vector3D(1.0, 0.0, 0.0);
// 	Vector3D tangentialForce = Vector3D(0.0, 1.0, 0.0);


// 	Interaction<SphericalParticle, SphericalParticle> fm0(name);
// 	fm0.setNormal(myNormalForce);
// 	fm0.setTangential(myTangentialForce);
// 	fm0.calculate(sph0, sph1);
// 	checkEqual(fm0.getName(), name);
// 	checkEqual(sph0->getResultingForce(), normalForce + tangentialForce);
// 	checkEqual(sph1->getResultingForce(), normalForce + tangentialForce);

// 	Interaction<SphericalParticle, SphericalParticle> fm1(fm0);
// 	fm1.calculate(sph2, sph3);
// 	checkEqual(fm1.getName(), name);
// 	checkEqual(sph2->getResultingForce(), normalForce + tangentialForce);
// 	checkEqual(sph3->getResultingForce(), normalForce + tangentialForce);

// 	Interaction<SphericalParticle, SphericalParticle> fm2;
// 	fm2.setNormal({ myNormalForce, myNormalForce });
// 	fm2.setTangential(myTangentialForce);
// 	fm2.addTangential(myTangentialForce);
// 	fm2.calculate(sph4, sph5);
// 	checkEqual(sph4->getResultingForce(), 2*normalForce + 2*tangentialForce);
// 	checkEqual(sph5->getResultingForce(), 2*normalForce + 2*tangentialForce);
// }

// void myTangentialForce2(SphericalParticlePtr sph0, SphericalParticlePtr sph1, Vector3D normalForce, double timeStep)
// {
// 	sph0->addContactForce( timeStep * Vector3D(0.0, 1.0, 0.0) );
// }

// TestCase(SetTimeStepAndNumberOfParticlesTest)
// {
// 	SphericalParticlePtr sph0(new SphericalParticle());
// 	SphericalParticlePtr sph1(new SphericalParticle());

// 	Interaction<SphericalParticle, SphericalParticle> fm;
// 	int numberOfParticles = 100;
// 	double timeStep = 0.8;

// 	fm.setNumberOfParticles(numberOfParticles);
// 	checkEqual(fm.getNumberOfParticles(), numberOfParticles);

// 	fm.setTimeStep(timeStep);
// 	auto tangentialForce = timeStep * Vector3D(0.0, 1.0, 0.0);

// 	fm.setTangential(myTangentialForce2);
// 	fm.calculate(sph0, sph1);
// 	checkEqual(sph0->getResultingForce(), tangentialForce);
// }
