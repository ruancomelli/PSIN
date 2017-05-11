#ifndef UTILS_EQUAL_TYPES_HPP
#define UTILS_EQUAL_TYPES_HPP

// ---- equal_types ----
template<typename T, typename U>
struct equal_types
{
	constexpr static bool value = false;
};

template<typename T>
struct equal_types<T, T>
{
	constexpr static bool value = true;
};


#endif
