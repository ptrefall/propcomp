#pragma once

#include <string>
#include <functional>

#ifdef WIN32
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline
#endif

namespace Totem
{

template<typename HashFunction>
class HashedString
{
public:
	template<unsigned int N>
	FORCE_INLINE HashedString(const char (&value)[N])
		: hashId(HashFunction::hash<N>(value)), str(value)
	{
	}

	FORCE_INLINE unsigned int getId() const { return hashId; }
	FORCE_INLINE const std::string &getStr() const { return str; }

private:
	unsigned int hashId;
	std::string str;
};

class HashFNV1a
{
public:
	template<unsigned int N>
	FORCE_INLINE static unsigned int hash(const char (&value)[N])
	{
		return (hash<N-1>((const char(&)[N-1])value)^ value[N-1]) * 16777619u;
	}

	template<>
	FORCE_INLINE static unsigned int hash<1>(const char (&value)[1])
	{
		return (2166136261u^ value[0]) * 16777619u;
	}
};

typedef HashedString<HashFNV1a> HashedString1;

}
