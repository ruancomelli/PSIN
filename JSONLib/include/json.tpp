#ifndef PSIN_JSON_TPP
#define PSIN_JSON_TPP

namespace psin {

template<typename JsonContainer>
json merge(const JsonContainer & container)
{
	json result;
	json tmp;

	for(const json& j : container)
	{
		tmp = j.flatten();
		for(auto it = tmp.begin(); it != tmp.end(); ++it)
		{
			result[it.key()] = it.value();
		}
	}

	return result.unflatten();
}

} // psin

#endif // PSIN_JSON_TPP
