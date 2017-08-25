#ifndef NAMED_GROUP_HPP
#define NAMED_GROUP_HPP

#include <string>

template<template<typename...> class T>
struct NamedGroup
{
	const static std::string name;
}; //struct NamedGroup

#endif // NAMED_GROUP_HPP