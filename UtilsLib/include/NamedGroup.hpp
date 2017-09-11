#ifndef NAMED_GROUP_HPP
#define NAMED_GROUP_HPP

// UtilsLib
#include <string.hpp>

namespace psin {

template<template<typename...> class T>
struct NamedGroup
{
	const static std::string name;
}; //struct NamedGroup

} // psin

#endif // NAMED_GROUP_HPP