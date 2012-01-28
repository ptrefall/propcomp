#pragma once

/**
 * @file
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @section LICENSE
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 * Note: Some of the libraries Totem EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * Types Configuration, originally contributed by 'savuporo'.
 * 
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <memory>
#include <functional>
#include "sigslot.h"
#include "cdiggins_any.h"
#include "FastDelegate.h"
#include "FastDelegateBind.h"

//--------------------------------------------

typedef unsigned int T_HashedStringType;
//typedef T_String T_HashedStringType;

class T_HashedString
{
public:
	T_HashedString(const std::string &str)
		: hashId(0), str(std::string())
	{
		this->str = str;
		this->hashId = std::hash<std::string>()(str);
	}

	~T_HashedString()
	{
		str = std::string();
		hashId = 0;
	}

	const T_HashedStringType &getId() const { return hashId; }
	const std::string &getStr() const { return str; }

private:
	T_HashedStringType hashId;
	std::string str;
};
