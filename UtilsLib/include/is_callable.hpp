#ifndef IS_CALLABLE_HPP
#define IS_CALLABLE_HPP


#define define_is_callable(FUNCTION_NAME)                                        \
    namespace detail{                                                            \
        template<typename...Args>                                                \
        static auto test_is_callable_ ## FUNCTION_NAME(int)                      \
            -> sfinae_true<                                                      \
                decltype(                                                        \
                    FUNCTION_NAME(                                               \
                        std::declval<Args>()...                                  \
                    )                                                            \
                )                                                                \
            >;                                                                   \
        template<typename...Args>                                                \
        static auto test_is_callable_ ## FUNCTION_NAME(long) -> std::false_type; \
    }                                                                            \
                                                                                 \
    template<typename...Args>                                                    \
    struct is_callable_ ## FUNCTION_NAME :                                       \
        decltype(detail::test_is_callable_ ## FUNCTION_NAME<Args...>(0)){}

// Explanation:
//      define_can_call(f) generates a metafunction called can_call_f.
//      can_call_f receives template parameters: a type T and argument types Args...
//      can_call_f<T, Args>::value asserts whether type T can call f(Args...).
// Usage:
//      struct X{};
//      struct Y{
//          int myF(double, X);
//      };
//      
//      define_can_call(myF);
//
//      int main()
//      {
//          static_assert(!can_call_myF<X, double,char>::value);
//          static_assert(can_call_myF<Y, int(double, X)>::value);
//          static_assert(can_call_myF<Y, int(int, X)>::value);  // It is possible to convert int to double
//      }
//     

#define define_is_callable_operator(NAME, SYMBOL)                                \
    namespace detail{                                                            \
        template<typename T, typename...Args>                                    \
        static auto test_is_callable_operator_ ## NAME(int)                      \
            -> sfinae_true<                                                      \
                decltype(                                                        \
                    operator ## SYMBOL(                                          \
                        std::declval<Args>()...                                  \
                    )                                                            \
                )                                                                \
            >;                                                                   \
        template<typename, typename...Args>                                      \
        static auto test_is_callable_operator_ ## NAME(long) -> std::false_type; \
    }                                                                            \
                                                                                 \
    template<typename T, typename...Args>                                        \
    struct is_callable_ ## FUNCTION_NAME :                                       \
        decltype(detail::test_is_callable_operator_ ## NAME<T, Args...>(0)){}

#endif