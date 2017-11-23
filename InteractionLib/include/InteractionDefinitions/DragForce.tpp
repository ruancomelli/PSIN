#ifndef DRAG_FORCE_TPP
#define DRAG_FORCE_TPP

#include <iostream>

// PropertyLib
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <Mathematics.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
template<typename Particle, typename Fluid, typename T>
void DragForce::calculate(Particle & particle, const Fluid & neighbor, T&&)
{
	const auto dragCoeff = dragCoefficient(particle, neighbor);

	const auto radius = particle.template get<Radius>();
	const auto area = pi<double>() * radius * radius;
	const auto velocity = particle.getVelocity();

	const auto density = neighbor.template get<SpecificMass>();

	const auto dragForce = - 0.5 * density * velocity.length() * velocity * dragCoeff * area;

	std::cout << "Drag force: " << dragForce << std::endl; // DEBUG

	particle.addBodyForce(dragForce);
}

template<typename Particle, typename Fluid>
double DragForce::dragCoefficient(Particle & particle, const Fluid & neighbor)
{
	// Reynolds: [5.33, 5.99, 11.0, 13.1, 13.2, 13.9, 14.6, 16.2, 21.1, 23.4, 29.1, 45.0, 50.6, 54.4, 68.9, 68.9, 78.2, 88.1, 93.8, 101, 104, 108, 109, 124, 130, 138, 163, 168, 170, 186, 186, 189, 190, 191, 193, 229, 229, 240, 258, 280, 284, 286, 311, 312, 318, 358, 361, 364, 379, 409, 444, 468, 472, 480, 500, 522, 532, 532, 557, 579, 588, 603, 644, 713, 727, 833, 932, 984, 985, 985, 1000, 1000, 1070, 1330, 1650, 1690, 1950, 2000, 5570, 5990, 6210, 6250, 6900, 7280, 7520, 8230, 8580, 8700, 9620, 13300, 13400, 13900, 14700, 16800, 18000, 18700, 19500, 21200, 23100, 23600, 23700, 24100, 24200, 25000, 28000, 31900, 32400, 33800, 35400, 35500, 38200, 41800, 45900, 46800, 52400, 53500, 57500, 57700, 71900, 89000, 100000, 118300]
	// Drag coefficient: [7.06, 6.41, 4.01, 3.76, 3.66, 3.59, 3.41, 3.29, 2.82, 2.48, 2.28, 1.79, 1.58, 1.52, 1.35, 1.33, 1.27, 1.12, 1.03, 1.08, 1.05, 1.02, 1.03, 0.994, 0.927, 0.907, 0.879, 0.799, 0.819, 0.799, 0.841, 0.778, 0.751, 0.799, 0.732, 0.711, 0.71, 0.7, 0.721, 0.674, 0.646, 0.675, 0.592, 0.607, 0.656, 0.627, 0.6, 0.632, 0.595, 0.579, 0.585, 0.578, 0.566, 0.572, 0.547, 0.544, 0.543, 0.556, 0.552, 0.523, 0.52, 0.531, 0.525, 0.505, 0.48, 0.485, 0.472, 0.466, 0.477, 0.485, 0.472, 0.483, 0.452, 0.436, 0.44, 0.435, 0.427, 0.43, 0.46, 0.43, 0.39, 0.451, 0.46, 0.43, 0.435, 0.429, 0.39, 0.49, 0.49, 0.46, 0.48, 0.4, 0.46, 0.452, 0.51, 0.523, 0.5, 0.509, 0.511, 0.529, 0.455, 0.524, 0.52, 0.519, 0.495, 0.5, 0.479, 0.457, 0.482, 0.504, 0.513, 0.485, 0.467, 0.468, 0.503, 0.497, 0.48, 0.492, 0.451, 0.502, 0.467, 0.476]
	return 0.5;
}

} // psin


#endif
