#ifndef IS_CALLABLE_MEMBER_HPP
#define IS_CALLABLE_MEMBER_HPP

// UtilsLib
#include <Metaprogramming/sfinae_true.hpp>

#define define_is_callable_member(SYMBOL, NAME)                                \
    namespace detail{                                                          \
        template<typename T, typename...Args>                                  \
        static auto NAME ## _test_is_callable_member(int)                      \
            -> sfinae_true<                                                    \
                decltype(                                                      \
                    std::declval<T>().SYMBOL(                                  \
                        std::declval<Args>()...                                \
                    )                                                          \
                )                                                              \
            >;                                                                 \
        template<typename, typename...Args>                                    \
        static auto NAME ## _test_is_callable_member(long) -> std::false_type; \
    }                                                                          \
                                                                               \
    template<typename T, typename...Args>                                      \
    struct NAME ## _is_callable_member :                                       \
        decltype(detail::NAME ## _test_is_callable_member<T, Args...>(0)){}

// Arithmetic operators
define_is_callable_member(operator+, unary_plus_operator);
define_is_callable_member(operator-, unary_minus_operator);
define_is_callable_member(operator+, addition_operator);
define_is_callable_member(operator-, subtraction_operator);
define_is_callable_member(operator*, multiplication_operator);
define_is_callable_member(operator/, division_operator);
define_is_callable_member(operator%, modulo_operator);
define_is_callable_member(operator~, bitwise_NOT_operator);
define_is_callable_member(operator&, bitwise_AND_operator);
define_is_callable_member(operator|, bitwise_OR_operator);
define_is_callable_member(operator^, bitwise_XOR_operator);
define_is_callable_member(operator<<, bitwise_left_shift_operator);
define_is_callable_member(operator>>, bitwise_right_shift_operator);

// Increment/decrement operators
define_is_callable_member(operator++, increment_operator);
define_is_callable_member(operator--, decrement_operator);

// Assignment operators
define_is_callable_member(operator=, simple_assignment_operator);
define_is_callable_member(operator+=, addition_assignment_operator);
define_is_callable_member(operator-=, subtraction_assignment_operator);
define_is_callable_member(operator*=, multiplication_assignment_operator);
define_is_callable_member(operator/=, division_assignment_operator);
define_is_callable_member(operator%=, modulo_assignment_operator);
define_is_callable_member(operator&=, bitwise_AND_assignment_operator);
define_is_callable_member(operator|=, bitwise_OR_assignment_operator);
define_is_callable_member(operator^=, bitwise_XOR_assignment_operator);
define_is_callable_member(operator<<=, bitwise_left_shift_assignment_operator);
define_is_callable_member(operator>>=, bitwise_right_shift_assignment_operator);

// Logical operators
define_is_callable_member(operator!, negation_operator);
define_is_callable_member(operator&&, AND_operator);
define_is_callable_member(operator||, inclusive_OR_operator);

// Comparison operators
define_is_callable_member(operator==, equal_to_operator);
define_is_callable_member(operator!=, not_equal_to_operator);
define_is_callable_member(operator<, less_than_operator);
define_is_callable_member(operator>, greater_than_operator);
define_is_callable_member(operator<=, less_than_or_equal_to_operator);
define_is_callable_member(operator>=, greater_than_or_equal_to_operator);

// Member access operators
define_is_callable_member(operator[], subscript_operator);
define_is_callable_member(operator*, indirection_operator);
define_is_callable_member(operator&, address_of_operator);
define_is_callable_member(operator->, member_of_pointer_operator);
define_is_callable_member(operator->*, pointer_to_member_of_pointer_operator);

// Explanation:
//      define_is_callable_member(g, myFunction) generates a metafunction called myFunction_is_callable_member that tests whether g can be called by a class.
//      myFunction_is_callable_member receives template parameters: a type T and argument types Args...
//      myFunction_is_callable_member<T, Args...>::value asserts whether type T can call g(Args...).
// Usage:
//      struct X{};
//      struct Y{
//          int myFunction(double, X);
//      };
//      
//      define_is_callable_member(myF, myFunction);
//
//      int main()
//      {
//          static_assert(!myFunction_is_callable_member<X, double,char>::value);
//          static_assert(myFunction_is_callable_member<Y, double, X>::value);
//          static_assert(myFunction_is_callable_member<Y, int, X>::value);  // It is possible to convert int into double
//      }
// Usage with operators:
//     struct X
//     {
//         double operator[](int index);
//     };

//     int main()
//     {
//         static_assert(subscript_operator_is_callable_member<X, int>::value);
//     }

#endif
