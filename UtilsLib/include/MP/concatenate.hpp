#ifndef CONCATENATE_HPP
#define CONCATENATE_HPP

// UtilsLib
#include <MP/metafunction.hpp>

namespace traits {
	template<typename TypeList1, typename TypeList2>
	struct concatenate;

	template<template<typename...> class TypeList, typename...Is, typename...Js>
	struct concatenate<
		TypeList<Is...>,
		TypeList<Js...>
	> : metafunction< TypeList<Is..., Js...> >
	{};
} // traits

#endif // CONCATENATE_HPP
