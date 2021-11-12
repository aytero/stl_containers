#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	template <bool Cond, class T = void>
		struct enable_if;

	template <class T>
		struct is_integral;
}

template <bool Cond, class T>// = void ??
	struct ft::enable_if {};

template <class T>
	struct ft::enable_if<true, T> { typedef T type; };

// make own integral_constant ?
template <class T>
	struct ft::is_integral : std::false_type {};
	//struct is_integral : std::integral_constant {};

//template <class T> struct is_integral : false_type {};

template <>
	struct ft::is_integral<bool> : std::true_type {};


#endif
