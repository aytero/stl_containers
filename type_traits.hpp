#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

template <bool Cond, class T = void>
	struct enable_if {};

template <class T>
	struct enable_if<true, T> { typedef T type; };

template <class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator T() const { return v; }
};

template <class T> struct is_integral : public ft::integral_constant<T, false> {};
//template <> struct ft::is_integral<bool> : std::true_type {};
template <> struct ft::is_integral<bool> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<char> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<char16_t> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<char32_t> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<wchar_t> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<signed char> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<short> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<int> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<long int> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<long long int> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<unsigned char> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<unsigned short int> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<unsigned int> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<unsigned long int> : ft::integral_constant<bool, true> {};
template <> struct ft::is_integral<unsigned long long int> : ft::integral_constant<bool, true> {};

};

#endif










/*
template<bool B, class T, class F>
	struct conditional {
	typedef F type;
};
 
template<class T, class F>
struct conditional<true, T, F> { typedef T type; };



*/
