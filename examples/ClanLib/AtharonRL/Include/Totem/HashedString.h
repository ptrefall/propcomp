#pragma once
 
#include <functional>

#ifdef WIN32
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline
#endif

namespace Totem
{

template <unsigned int N, unsigned int I>
struct HashFNV1a
{
        FORCE_INLINE static unsigned int hash(const char (&str)[N])
        {
                return (HashFNV1a<N, I-1>::hash(str) ^ str[I-1])*16777619u;
        }
};

template <unsigned int N>
struct HashFNV1a<N, 1>
{
        FORCE_INLINE static unsigned int hash(const char (&str)[N])
        {
                return (2166136261u ^ str[0])*16777619u;
        }
};

class HashedString
{
public:
	template<unsigned int N>
	FORCE_INLINE HashedString(const char (&value)[N])
		: hashId(HashFNV1a<N,N>::hash(value)), str(value)
	{
	}

	FORCE_INLINE unsigned int getId() const { return hashId; }
	FORCE_INLINE const std::string &getStr() const { return str; }

private:
	unsigned int hashId;
	std::string str;
};

/*class HashFNV1a
{
public:
	template<unsigned int N>
	FORCE_INLINE static unsigned int hash(const char (&value)[N])
	{
		return (hash<N-1>((const char(&)[N-1])value)^ value[N-1]) * 16777619u;
	}

	template<N, 1>
	FORCE_INLINE static unsigned int hash(const char (&value)[N])
	{
		return (2166136261u^ value[0]) * 16777619u;
	}
};
*/
typedef HashedString HashedString1;

}
