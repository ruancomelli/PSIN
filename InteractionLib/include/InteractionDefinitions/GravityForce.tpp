#ifndef GRAVITY_FORCE_TPP
#define GRAVITY_FORCE_TPP

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
template<typename P1>
void GravityForce::calculate(P1 & particle, const GravityField & field)
{
	const Vector3D force = particle.template get<Mass>() * field.get<Gravity>();
	particle.addBodyForce(force);
}

} // psin

#endif // GRAVITY_FORCE_TPP
