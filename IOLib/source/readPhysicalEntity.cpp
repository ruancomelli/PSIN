#include <readPhysicalEntity.h>

PhysicalEntityPtr readPhysicalEntity( const string fileName )
{
	FileReader fileReader(fileName);

	// ----- Read Entity -----
	EntityPtr entity = readEntity(fileName);
	

	// ----- Read taylorOrder -----
	int taylorOrder;
	fileReader.readValue("<TaylorOrder>", taylorOrder);

	// ----- Read dimension -----
	int dimension;
	fileReader.readValue("<Dimension>", dimension);

	// ----- Create object -----
	PhysicalEntity physicalEntity( taylorOrder, dimension, *entity );


	// ----- Read initial position -----
	int size = taylorOrder + 1;

	vector<Vector3D> position;
	position.resize(size);
	fileReader.readValue("<Position>", position);
	physicalEntity.setPosition(position);

	// ----- Read initial orientation -----
	vector<Vector3D> orientation;
	orientation.resize(size);
	fileReader.readValue("<Orientation>", orientation);
	physicalEntity.setOrientation(orientation);

	// ----- Read physical properties -----
	// Scalar Properties
	vector<double> scalarProperty( N_SCALAR_PROPERTY );
	fileReader.readValue("<Mass>", scalarProperty[MASS]);
	fileReader.readValue("<MomentOfInertia>", scalarProperty[MOMENT_OF_INERTIA]);
	fileReader.readValue("<Volume>", scalarProperty[VOLUME]);
	fileReader.readValue("<SpecificMass>", scalarProperty[SPECIFIC_MASS]);
	fileReader.readValue("<DissipativeConstant>", scalarProperty[DISSIPATIVE_CONSTANT]);
	fileReader.readValue("<PoissonRatio>", scalarProperty[POISSON_RATIO]);
	fileReader.readValue("<ElasticModulus>", scalarProperty[ELASTIC_MODULUS]);
	fileReader.readValue("<TangentialDamping>", scalarProperty[TANGENTIAL_DAMPING]);
	fileReader.readValue("<FrictionParameter>", scalarProperty[FRICTION_PARAMETER]);
	fileReader.readValue("<NormalDissipativeConstant>", scalarProperty[NORMAL_DISSIPATIVE_CONSTANT]);
	fileReader.readValue("<TangentialKappa>", scalarProperty[TANGENTIAL_KAPPA]);


	physicalEntity.setScalarProperty(scalarProperty);

	return PhysicalEntityPtr( new PhysicalEntity(physicalEntity) );
}