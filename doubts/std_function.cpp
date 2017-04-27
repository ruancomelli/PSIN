#include <iostream>

template<typename Ret, typename...Args>
Ret call(std::function<Ret(Args...)> f, Args...args)
{
	return f(args...);
}

template<typename Ret, typename...Args>
Ret call(Ret(*f)(Args...), Args...args)
{
	return call(std::function<Ret(Args...)>(f), args...);
}

template<typename Ret, typename...Args, typename ... ImplicitArgs>
Ret call( Ret (*f)(Args...), ImplicitArgs...args )
{
	return call( std::function<Ret(Args...)>(f), Args(args)... );
}

int myF(double x, string y)
{
	cout << x << endl;
	cout << y << endl;
	return 1;
}

int main()
{
	std::cout << call(myF, 2.5, "Oi") << std::endl;
}

//	Conclusions:
//		* We cannot specialize Ret call(std::function<Ret(Args...)> , Args... ) using a function pointer, as the template parameter expects a std::function.