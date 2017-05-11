#ifndef UTILS_IF_THEN_ELSE_HPP
#define UTILS_IF_THEN_ELSE_HPP


template<bool value, typename TrueResult, typename FalseResult>
struct if_then_else;

template<typename TrueResult, typename FalseResult>
struct if_then_else<true, TrueResult, FalseResult>
{
	using value = TrueResult;
};

template<typename TrueResult, typename FalseResult>
struct if_then_else<false, TrueResult, FalseResult>
{
	using value = FalseResult;
};



#endif
