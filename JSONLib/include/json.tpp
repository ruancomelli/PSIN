#ifndef PSIN_JSON_TPP
#define PSIN_JSON_TPP

namespace psin {

template<typename JsonContainer>
json merge(const JsonContainer & container)
{
	json result;

	for(const json & j : container)
	{
		result = merge(result, j);
	}

	return result;
}

} // psin

#endif // PSIN_JSON_TPP
