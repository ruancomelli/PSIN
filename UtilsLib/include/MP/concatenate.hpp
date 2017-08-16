#ifndef CONCATENATE_HPP
#define CONCATENATE_HPP

namespace traits {
	template<typename TypeList1, typename TypeList2>
	struct concatenate;

	template<template<typename...> class TypeList, typename...Is, typename...Js>
	struct concatenate<
		TypeList<Is...>,
		TypeList<Js...>
	>
	{
		using type = TypeList<Is..., Js...>;
	};
} // traits

#endif // CONCATENATE_HPP
