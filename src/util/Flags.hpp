#ifndef DBR_UTIL_FLAGS_HPP
#define DBR_UTIL_FLAGS_HPP

#define DBR_UTIL_FLAGS(E)												\
																		\
inline E operator|(E lhs, E rhs)										\
{																		\
	using UT = std::underlying_type_t<E>;								\
																		\
	return static_cast<E>(static_cast<UT>(lhs) | static_cast<UT>(rhs));	\
}																		\
																		\
inline E& operator|=(E& lhs, E rhs)										\
{																		\
	using UT = std::underlying_type_t<E>;								\
																		\
	return lhs = lhs | rhs;												\
}																		\
																		\
inline E operator&(E lhs, E rhs)										\
{																		\
	using UT = std::underlying_type_t<E>;								\
																		\
	return static_cast<E>(static_cast<UT>(lhs) & static_cast<UT>(rhs));	\
}																		\
																		\
inline E& operator&=(E& lhs, E rhs)										\
{																		\
	using UT = std::underlying_type_t<E>;								\
																		\
	return lhs = lhs & rhs;												\
}																		\
																		\
inline E operator^(E lhs, E rhs)										\
{																		\
	using UT = std::underlying_type_t<E>;								\
																		\
	return static_cast<E>(static_cast<UT>(lhs) ^ static_cast<UT>(rhs));	\
}																		\
																		\
inline E& operator^=(E& lhs, E rhs)										\
{																		\
	using UT = std::underlying_type_t<E>;								\
																		\
	return lhs = lhs ^ rhs;												\
}																		\
																		\
inline E operator~(E e)													\
{																		\
	using UT = std::underlying_type_t<E>;								\
																		\
	return static_cast<E>(~static_cast<UT>(e));							\
}

#endif
