#ifndef GRAVITY_CPP
#define GRAVITY_CPP

Gravity::Gravity()
	: Property<Vector3D>()
{}

Gravity::Gravity(const Vector3D & value)
	: Property<Vector3D>(value)
{}

template<> const string NamedType<Gravity>::name = "Gravity";

void from_json(const json& j, Gravity & x)
{
	x = Gravity(j.get<Vector3D>());
}
void to_json(json& j, const Gravity & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

#endif // GRAVITY_CPP
