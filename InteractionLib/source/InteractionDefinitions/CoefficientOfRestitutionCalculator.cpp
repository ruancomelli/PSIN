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
bool CoefficientOfRestitutionCalculator::firstPrint = true;

template<> const std::string NamedType<CoefficientOfRestitutionCalculator>::name = "CoefficientOfRestitutionCalculator";

template<>
void initializeInteraction<CoefficientOfRestitutionCalculator>(const json & j)
{
	if(j.count("path") > 0) CoefficientOfRestitutionCalculator::setFile(j.at("path").get<path>());
}

template<>
void finalizeInteraction<CoefficientOfRestitutionCalculator>()
{
	CoefficientOfRestitutionCalculator::finish();
}

void CoefficientOfRestitutionCalculator::setFile(const path & filepath)
{
	file = make_unique<std::fstream>(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
	*file << "[\n";
}

void CoefficientOfRestitutionCalculator::finish()
{
	*file << "\n]";
}

} // psin


#endif // COEFFICIENT_OF_RESTITUTION_CALCULATOR_CPP
