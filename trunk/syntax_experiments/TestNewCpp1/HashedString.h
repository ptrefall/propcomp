#pragma once

#include <string>
#include <functional>

class HashedString
{
public:
	HashedString(const std::string &str)
		: hashId(0), str(str)
	{
		hashId = std::hash<std::string>()(str);
	}

	const unsigned int &getId() const { return hashId; }
	const std::string &getStr() const { return str; }

private:
	unsigned int hashId;
	std::string str;
};
