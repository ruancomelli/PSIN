#ifndef IS_CALLABLE_HPP
#define IS_CALLABLE_HPP

// UtilsLib
#include <Metaprogramming/sfinae_true.hpp>

#define define_is_callable(SYMBOL, NAME)                                         \
    namespace detail{                                                            \
        template<typename...Args>                                                \
        static auto NAME ## _test_is_callable(int)                               \
            -> sfinae_true<                                                      \
                decltype(                                                        \
                    SYMBOL(                                                      \
                        std::declval<Args>()...                                  \
                    )                                                            \
                )                                                                \
            >;                                                                   \
        template<typename...Args>                                                \
        static auto NAME ## _test_is_callable(long) -> std::false_type;          \
    }                                                                            \
                                                                                 \
    template<typename...Args>                                                    \
    struct NAME ## _is_callable :                                                \
        decltype(detail::NAME ## _test_is_callable<Args...>(0)){}


// Arithmetic operators
define_is_callable(operator+, unary_plus_operator);
define_is_callable(operator-, unary_minus_operator);
define_is_callable(operator+, addition_operator);
define_is_callable(operator-, subtraction_operator);
define_is_callable(operator*, multiplication_operator);
define_is_callable(operator/, division_operator);
define_is_callable(operator%, modulo_operator);
define_is_callable(operator~, bitwise_NOT_operator);
define_is_callable(operator&, bitwise_AND_operator);
define_is_callable(operator|, bitwise_OR_operator);
define_is_callable(operator^, bitwise_XOR_operator);
define_is_callable(operator<<, bitwise_left_shift_operator);
define_is_callable(operator>>, bitwise_right_shift_operator);

// Increment/decrement operators
define_is_callable(operator++, increment_operator);
define_is_callable(operator--, decrement_operator);

// Assignment operators
define_is_callable(operator+=, addition_assignment_operator);
define_is_callable(operator-=, subtraction_assignment_operator);
define_is_callable(operator*=, multiplication_assignment_operator);
define_is_callable(operator/=, division_assignment_operator);
define_is_callable(operator%=, modulo_assignment_operator);
define_is_callable(operator&=, bitwise_AND_assignment_operator);
define_is_callable(operator|=, bitwise_OR_assignment_operator);
define_is_callable(operator^=, bitwise_XOR_assignment_operator);
define_is_callable(operator<<=, bitwise_left_shift_assignment_operator);
define_is_callable(operator>>=, bitwise_right_shift_assignment_operator);

// Logical operators
define_is_callable(operator!, negation_operator);
define_is_callable(operator&&, AND_operator);
define_is_callable(operator||, inclusive_OR_operator);

// Comparison operators
define_is_callable(operator==, equal_to_operator);
define_is_callable(operator!=, not_equal_to_operator);
define_is_callable(operator<, less_than_operator);
define_is_callable(operator>, greater_than_operator);
define_is_callable(operator<=, less_than_or_equal_to_operator);
define_is_callable(operator>=, greater_than_or_equal_to_operator);

// Member access operators
define_is_callable(operator*, indirection_operator);
define_is_callable(operator&, address_of_operator);
define_is_callable(operator->*, pointer_to_member_of_pointer_operator);


// Explanation:
//      define_is_callable(g, myFunction) generates a metafunction called myFunction_is_callable that tests whether g can be called.
//      myFunction_is_callable receives argument types Args... as parameters.
//      myFunction_is_callable<Args...>::value asserts whether type g(Args...) is a valid call.
// Usage:
//      struct X{};
//      f(int);
//      
//      define_is_callable(f, myFunction);
//
//      int main()
//      {
//          static_assert(!myFunction_is_callable<X>::value);
//          static_assert(myFunction_is_callable<int>::value);
//          static_assert(myFunction_is_callable<double>::value);  // It is possible to convert double into int
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