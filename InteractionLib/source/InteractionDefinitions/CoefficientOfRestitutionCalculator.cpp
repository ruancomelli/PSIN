#ifndef COEFFICIENT_OF_RESTITUTION_CALCULATOR_CPP
#define COEFFICIENT_OF_RESTITUTION_CALCULATOR_CPP

#include <InteractionDefinitions/CoefficientOfRestitutionCalculator.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {
	
std::map<CoefficientOfRestitutionCalculator::name_pair, bool> CoefficientOfRestitutionCalculator::collisionFlag;
std::map<CoefficientOfRestitutionCalculator::name_pair, double> CoefficientOfRestitutionCalculator::coefficientOfRestitution;
std::map<CoefficientOfRestitutionCalculator::name_pair, CoefficientOfRestitutionCalculator::velocities_t> CoefficientOfRestitutionCalculator::velocities;
unique_ptr<std::fstream> CoefficientOfRestitutionCalculator::file;

template<> const std::string NamedType<CoefficientOfRestitutionCalculator>::name = "CoefficientOfRestitutionCalculator";

void Builder<CoefficientOfRestitutionCalculator>::setup(const json & j)
{
	if(j.count("path") > 0) CoefficientOfRestitutionCalculator::setFile(j.at("path").get<path>());
}

void CoefficientOfRestitutionCalculator::setFile(const path & filepath)
{
	file = make_unique<std::fstream>(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
}

} // psin


#endif // COEFFICIENT_OF_RESTITUTION_CALCULATOR_CPP
