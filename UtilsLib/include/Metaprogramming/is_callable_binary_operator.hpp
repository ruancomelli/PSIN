#ifndef IS_CALLABLE_BINARY_OPERATOR_HPP
#define IS_CALLABLE_BINARY_OPERATOR_HPP

// UtilsLib
#include <Metaprogramming/sfinae_true.hpp>

#define define_is_callable_binary_operator(SYMBOL, NAME)                      \
    namespace detail{                                                         \
        template<typename T, typename U>                                      \
        static auto NAME ## _test_is_callable_binary_operator(int)            \
            -> sfinae_true<                                                   \
                decltype(                                                     \
                    std::declval<T>() SYMBOL std::declval<U>()                \
                )                                                             \
            >;                                                                \
        template<typename, typename>                                          \
        static auto NAME ## _test_is_callable_binary_operator(long) -> std::false_type;          \
    }                                                                         \
                                                                              \
    template<typename T, typename U>                                          \
    struct NAME ## _is_callable_binary_operator :                             \
        decltype(detail::NAME ## _test_is_callable_binary_operator<T, U>(0)){}

// Arithmetic operators
define_is_callable_binary_operator(+, addition);
define_is_callable_binary_operator(-, subtraction);
define_is_callable_binary_operator(*, multiplication);
define_is_callable_binary_operator(/, division);
define_is_callable_binary_operator(%, modulo);
define_is_callable_binary_operator(&, bitwise_AND);
define_is_callable_binary_operator(|, bitwise_OR);
define_is_callable_binary_operator(^, bitwise_XOR);
define_is_callable_binary_operator(<<, bitwise_left_shift);
define_is_callable_binary_operator(>>, bitwise_right_shift);

// Assignment operators
define_is_callable_binary_operator(=, simple_assignment);
define_is_callable_binary_operator(+=, addition_assignment);
define_is_callable_binary_operator(-=, subtraction_assignment);
define_is_callable_binary_operator(*=, multiplication_assignment);
define_is_callable_binary_operator(/=, division_assignment);
define_is_callable_binary_operator(%=, modulo_assignment);
define_is_callable_binary_operator(&=, bitwise_AND_assignment);
define_is_callable_binary_operator(|=, bitwise_OR_assignment);
define_is_callable_binary_operator(^=, bitwise_XOR_assignment);
define_is_callable_binary_operator(<<=, bitwise_left_shift_assignment);
define_is_callable_binary_operator(>>=, bitwise_right_shift_assignment);

// Logical operators
define_is_callable_binary_operator(&&, AND);
define_is_callable_binary_operator(||, inclusive_OR);

// Comparison operators
define_is_callable_binary_operator(==, equal_to);
define_is_callable_binary_operator(!=, not_equal_to);
define_is_callable_binary_operator(<, less_than);
define_is_callable_binary_operator(>, greater_than);
define_is_callable_binary_operator(<=, less_than_or_equal_to);
define_is_callable_binary_operator(>=, greater_than_or_equal_to);

// Member access operators
define_is_callable_binary_operator(->*, pointer_to_member_of_pointer);

// Explanation:
//      define_is_callable_binary_operator(?, myOp) generates a metafunction called myFunction_is_callable_binary_operator that tests whether ? can be called.
//      myOp_is_callable_binary_operator receives two argument types (T and U) as parameters.
//      myOp_is_callable_binary_operator<T, U>::value asserts whether type g(Args...) is a valid call.
// Usage:
//      struct X{};
//      f(int);
//      
//      define_is_callable_binary_operator(f, myOp);
//
//      int main()
//      {
//          static_assert(!myOp_is_callable_binary_operator<X>::value);
//          static_assert(myOp_is_callable_binary_operator<int>::value);
//          static_assert(myOp_is_callable_binary_operator<double>::value);  // It is possible to convert double into int
//      }
//
// // Usage with operators:
//    struct X{};
//    X& operator+(const X &, const X &);
//
//    int main()
//    {
//        static_assert(addition_operator_is_callable<X, X>::value);
//    }

#endif
