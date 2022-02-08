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

	template <class T> struct is_integral				: public ft::integral_constant<T, false> {};
	template <> struct ft::is_integral<bool>			: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<char>			: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<char16_t>		: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<char32_t>		: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<wchar_t>			: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<signed char>		: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<short>			: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<int>				: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<long>			: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<unsigned char>	: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<unsigned short>	: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<unsigned int>	: public ft::integral_constant<bool, true> {};
	template <> struct ft::is_integral<unsigned long>	: public ft::integral_constant<bool, true> {};
	//template <> struct ft::is_integral<long long>		: public ft::integral_constant<bool, true> {};
	//template <> struct ft::is_integral<unsigned long long> : public ft::integral_constant<bool, true> {};
}

#endif
