#pragma once

/**
 * @file
 * @class Totem::Addon::DelegateHandler
 *
 * @author P�l Trefall
 * @author Kenneth Gangst�
 *
 * @version 2.0
 *
 * @brief DelegateHandler base class
 *
 * @section LICENSE
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no delegate will the authors be held liable for any damages
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
 * The delegate handler.
 * 
 */

#include "../config.h"
#include "../Property.h"
#include "../Component.h"
#include "../HashedString.h"

namespace Totem {
namespace Addon {

template<typename RetType> class Delegate0;
template<typename Param1, typename RetType> class Delegate1;
template<typename Param1, typename Param2, typename RetType> class Delegate2;
template<typename Param1, typename Param2, typename Param3, typename RetType> class Delegate3;
template<typename Param1, typename Param2, typename Param3, typename Param4, typename RetType> class Delegate4;
template<typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename RetType> class Delegate5;
template<typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename RetType> class Delegate6;

class DefaultDelegateFactory
{
public:
	template<class RetType>
	static std::shared_ptr<Delegate0<RetType>> createDelegate()
	{
		return std::make_shared<Delegate0<RetType>>();
	}

	template<class Param1, class RetType>
	static std::shared_ptr<Delegate1<Param1, RetType>> createDelegate()
	{
		return std::make_shared<Delegate1<Param1, RetType>>();
	}

	template<class Param1, class Param2, class RetType>
	static std::shared_ptr<Delegate2<Param1, Param2, RetType>> createDelegate()
	{
		return std::make_shared<Delegate2<Param1, Param2, RetType>>();
	}

	template<class Param1, class Param2, class Param3, class RetType>
	static std::shared_ptr<Delegate3<Param1, Param2, Param3, RetType>> createDelegate()
	{
		return std::make_shared<Delegate3<Param1, Param2, Param3, RetType>>();
	}

	template<class Param1, class Param2, class Param3, class Param4, class RetType>
	static std::shared_ptr<Delegate4<Param1, Param2, Param3, Param4, RetType>> createDelegate()
	{
		return std::make_shared<Delegate4<Param1, Param2, Param3, Param4, RetType>>();
	}

	template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
	static std::shared_ptr<Delegate5<Param1, Param2, Param3, Param4, Param5, RetType>> createDelegate()
	{
		return std::make_shared<Delegate5<Param1, Param2, Param3, Param4, Param5, RetType>>();
	}

	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
	static std::shared_ptr<Delegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>> createDelegate()
	{
		return std::make_shared<Delegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>>();
	}
};

template<class DelegateFactory = DefaultDelegateFactory>
class DelegateHandler
{
public:
	/**
	 * Constructor
	 */
	DelegateHandler() {}
	/**
	 * Destructor
	 */
	virtual ~DelegateHandler() {}

	//--------------------------------------------------------------

	/**
	 * Calls all slots registered to the parameter-less delegate signal of type.
	 *
	 * @param type The hashed type string id of the delegate.
	 */
	template<class RetType>
	RetType call0(const HashedString &type);

	/**
	 * Calls all slots registered to the delegate signal of type holding one parameter.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param1 First parameter of type Param1.
	 */
	template<class Param1, class RetType>
	RetType call1(const HashedString &type, const Param1 &param1);

	/**
	 * Calls all slots registered to the delegate signal of type holding two parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param1 First parameter of type Param1.
	 * @param param2 Second parameter of type Param2.
	 */
	template<class Param1, class Param2, class RetType>
	RetType call2(const HashedString &type, const Param1 &param1, const Param2 &param2);

	/**
	 * Calls all slots registered to the delegate signal of type holding three parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param1 First parameter of type Param1.
	 * @param param2 Second parameter of type Param2.
	 * @param param3 Third parameter of type Param3.
	 */
	template<class Param1, class Param2, class Param3, class RetType>
	RetType call3(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3);

	/**
	 * Calls all slots registered to the delegate signal of type holding four parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param1 First parameter of type Param1.
	 * @param param2 Second parameter of type Param2.
	 * @param param3 Third parameter of type Param3.
	 * @param param4 Fourth parameter of type Param4.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class RetType>
	RetType call4(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4);

	/**
	 * Calls all slots registered to the delegate signal of type holding five parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param1 First parameter of type Param1.
	 * @param param2 Second parameter of type Param2.
	 * @param param3 Third parameter of type Param3.
	 * @param param4 Fourth parameter of type Param4.
	 * @param param5 Fifth parameter of type Param5.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
	RetType call5(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5);

	/**
	 * Calls all slots registered to the delegate signal of type holding six parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param1 First parameter of type Param1.
	 * @param param2 Second parameter of type Param2.
	 * @param param3 Third parameter of type Param3.
	 * @param param4 Fourth parameter of type Param4.
	 * @param param5 Fifth parameter of type Param5.
	 * @param param6 Sixth parameter of type Param6.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
	RetType call6(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6);

	//--------------------------------------------------------------

	/**
	 * Register a slot to the delegate signal of type holding two parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires no parameters in the slot.
	 */
	template<class RetType>
	std::shared_ptr<typename T_Delegate_v0<RetType>::Type> registerFunction0(const HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding one parameter.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires one parameters in the slot.
	 */
	template<class Param1, class RetType>
	std::shared_ptr<typename T_Delegate_v1<Param1, RetType>::Type> registerFunction1(const HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding two parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires two parameters in the slot.
	 */
	template<class Param1, class Param2, class RetType>
	std::shared_ptr<typename T_Delegate_v2<Param1, Param2, RetType>::Type> registerFunction2(const HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding three parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires three parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class RetType>
	std::shared_ptr<typename T_Delegate_v3<Param1, Param2, Param3, RetType>::Type> registerFunction3(const HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding four parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires four parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class RetType>
	std::shared_ptr<typename T_Delegate_v4<Param1, Param2, Param3, Param4, RetType>::Type> registerFunction4(const HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding five parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires five parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
	std::shared_ptr<typename T_Delegate_v5<Param1, Param2, Param3, Param4, Param5, RetType>::Type> registerFunction5(const HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding six parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires six parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
	std::shared_ptr<typename T_Delegate_v6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>::Type> registerFunction6(const HashedString &type);

	//--------------------------------------------------------------

	/**
	 *
	 */
	bool hasFunction(const HashedString &id, int num_params = -1);

protected:

	/**
	 * In order to support multiple different types registered into the delegate maps
	 * we need to store them as interfaces, else we can only store one specific type
	 * into the map (must specify value of template classes).
	 */
	class IDelegate
	{
	public:
		/// Constructor.
		IDelegate() {}
		/// Destructor.
		virtual ~IDelegate() {}
	};
	/// Delegate holding an parameter-less delegate.
	template<class RetType> 
	class Delegate0 : public IDelegate
	{
	public:
		/// Delegate taking no parameters
		typename T_Delegate_v0<RetType>::Type delegate;
	};
	/// Delegate holding a delegate that requires a single parameter.
	template<class Param1, class RetType> 
	class Delegate1 : public IDelegate
	{
	public:
		/// Delegate taking one parameters
		typename T_Delegate_v1<Param1, RetType>::Type delegate;
	};
	/// Delegate holding a delegate that requires two parameters.
	template<class Param1, class Param2, class RetType> 
	class Delegate2 : public IDelegate
	{
	public:
		/// Delegate taking two parameters
		typename T_Delegate_v2<Param1, Param2, RetType>::Type delegate;
	};
	/// Delegate holding a delegate that requires three parameters.
	template<class Param1, class Param2, class Param3, class RetType>
	class Delegate3 : public IDelegate
	{
	public:
		/// Delegate taking three parameters
		typename T_Delegate_v3<Param1, Param2, Param3, RetType>::Type delegate;
	};
	/// Delegate holding a delegate that requires four parameters.
	template<class Param1, class Param2, class Param3, class Param4, class RetType>
	class Delegate4 : public IDelegate
	{
	public:
		/// Delegate taking four parameters
		typename T_Delegate_v4<Param1, Param2, Param3, Param4, RetType>::Type delegate;
	};
	/// Delegate holding a delegate that requires five parameters.
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
	class Delegate5 : public IDelegate
	{
	public:
		/// Delegate taking five parameters
		typename T_Delegate_v5<Param1, Param2, Param3, Param4, Param5, RetType>::Type delegate;
	};
	/// Delegate holding a delegate that requires six parameters.
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
	class Delegate6 : public IDelegate
	{
	public:
		/// Delegate taking six parameters
		typename T_Delegate_v6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>::Type delegate;
	};
	
	/// Map of parameter-less delegate delegates held by DelegateHandler.
	typename T_Map<unsigned int, std::shared_ptr<IDelegate>>::Type delegates0;
	/// Map of delegate delegates with one parameter held by DelegateHandler.
	typename T_Map<unsigned int, std::shared_ptr<IDelegate>>::Type delegates1;
	/// Map of delegate delegates with two parameters held by DelegateHandler.
	typename T_Map<unsigned int, std::shared_ptr<IDelegate>>::Type delegates2;
	/// Map of delegate delegates with three parameters held by DelegateHandler.
	typename T_Map<unsigned int, std::shared_ptr<IDelegate>>::Type delegates3;
	/// Map of delegate delegates with four parameters held by DelegateHandler.
	typename T_Map<unsigned int, std::shared_ptr<IDelegate>>::Type delegates4;
	/// Map of delegate delegates with five parameters held by DelegateHandler.
	typename T_Map<unsigned int, std::shared_ptr<IDelegate>>::Type delegates5;
	/// Map of delegate delegates with six parameters held by DelegateHandler.
	typename T_Map<unsigned int, std::shared_ptr<IDelegate>>::Type delegates6;
};

//------------------------------------------------------

template<class DelegateFactory>
template<class RetType>
inline RetType DelegateHandler<DelegateFactory>::call0(const HashedString &type)
{
	auto it = delegates0.find(type.getId());
	if(it == delegates0.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates0 registry!").c_str());

	return static_cast<Delegate0<RetType>*>(it->second)->delegate();
}

template<class DelegateFactory>
template<class Param1, class RetType>
inline RetType DelegateHandler<DelegateFactory>::call1(const HashedString &type, const Param1 &param1)
{
	auto it = delegates1.find(type.getId());
	if(it == delegates1.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates1 registry!").c_str());

#ifdef _DEBUG
	auto delegate = dynamic_cast<Delegate1<Param1, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but the parameter type didn't match the registered type!").c_str());
	return delegate->delegate(param1);
#else
	return static_cast<Delegate1<Param1, RetType>*>(it->second)->delegate(param1);
#endif
}

template<class DelegateFactory>
template<class Param1, class Param2, class RetType>
inline RetType DelegateHandler<DelegateFactory>::call2(const HashedString &type, const Param1 &param1, const Param2 &param2)
{
	auto it = delegates2.find(type.getId());
	if(it == delegates2.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates2 registry!").c_str());

#ifdef _DEBUG
	auto delegate = dynamic_cast<Delegate2<Param1,Param2, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2);
#else
	return static_cast<Delegate2<Param1,Param2, RetType>*>(it->second)->delegate(param1, param2);
#endif
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class RetType>
inline RetType DelegateHandler<DelegateFactory>::call3(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3)
{
	auto it = delegates3.find(type.getId());
	if(it == delegates3.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates3 registry!").c_str());

#ifdef _DEBUG
	auto delegate = dynamic_cast<Delegate3<Param1,Param2,Param3, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3);
#else
	return static_cast<Delegate3<Param1,Param2,Param3, RetType>*>(it->second)->delegate(param1, param2, param3);
#endif
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class Param4, class RetType>
inline RetType DelegateHandler<DelegateFactory>::call4(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4)
{
	auto it = delegates4.find(type.getId());
	if(it == delegates4.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates4 registry!").c_str());

#ifdef _DEBUG
	auto delegate = dynamic_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4);
#else
	return static_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>*>(it->second)->delegate(param1, param2, param3, param4);
#endif
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
inline RetType DelegateHandler<DelegateFactory>::call5(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5)
{
	auto it = delegates5.find(type.getId());
	if(it == delegates5.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates5 registry!").c_str());

#ifdef _DEBUG
	auto delegate = dynamic_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4, param5);
#else
	return static_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>*>(it->second)->delegate(param1, param2, param3, param4, param5);
#endif
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
inline RetType DelegateHandler<DelegateFactory>::call6(const HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6)
{
	auto it = delegates6.find(type.getId());
	if(it == delegates6.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates6 registry!").c_str());

#ifdef _DEBUG
	auto delegate = dynamic_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4, param5, param6);
#else
	return static_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>*>(it->second)->delegate(param1, param2, param3, param4, param5, param6);
#endif
}

//------------------------------------------------------------------

template<class DelegateFactory>
template<class RetType>
inline std::shared_ptr<typename T_Delegate_v0<RetType>::Type> DelegateHandler<DelegateFactory>::registerFunction0(const HashedString &type)
{
	auto it = delegates0.find(type.getId());
	if(it == delegates0.end())
	{
		auto delegate = DelegateFactory::createDelegate<RetType>();
		delegates0[type.getId()] = delegate;
		return delegate->delegate;
	}
	else
	{
		auto delegate = std::static_pointer_cast<Delegate0<RetType>>(it->second);
		return delegate->delegate;
	}
}

template<class DelegateFactory>
template<class Param1, class RetType>
inline std::shared_ptr<typename T_Delegate_v1<Param1, RetType>::Type> DelegateHandler<DelegateFactory>::registerFunction1(const HashedString &type)
{
	auto it = delegates1.find(type.getId());
	if(it == delegates1.end())
	{
		auto delegate = DelegateFactory::createDelegate<Param1, RetType>();
		delegates1[type.getId()] = delegate;
		return delegate->delegate;
	}
	else
	{
#ifdef _DEBUG
		auto delegate = std::dynamic_pointer_cast<Delegate1<Param1, RetType>>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but the parameter type didn't match the registered type!").c_str());
#else
		auto delegate = std::static_pointer_cast<Delegate1<Param1, RetType>>(it->second);
#endif
		return delegate->delegate;
	}
}

template<class DelegateFactory>
template<class Param1, class Param2, class RetType>
inline std::shared_ptr<typename T_Delegate_v2<Param1, Param2, RetType>::Type> DelegateHandler<DelegateFactory>::registerFunction2(const HashedString &type)
{
	auto it = delegates2.find(type.getId());
	if(it == delegates2.end())
	{
		auto delegate = DelegateFactory::createDelegate<Param1,Param2, RetType>();
		delegates2[type.getId()] = delegate;
		return delegate->delegate;
	}
	else
	{
#ifdef _DEBUG
		auto delegate = std::dynamic_pointer_cast<Delegate2<Param1,Param2, RetType>>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		auto delegate = std::static_pointer_cast<Delegate2<Param1,Param2, RetType>>(it->second);
#endif
		return delegate->delegate;
	}
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class RetType>
inline std::shared_ptr<typename T_Delegate_v3<Param1, Param2, Param3, RetType>::Type> DelegateHandler<DelegateFactory>::registerFunction3(const HashedString &type)
{
	auto it = delegates3.find(type.getId());
	if(it == delegates3.end())
	{
		auto delegate = DelegateFactory::createDelegate<Param1,Param2,Param3, RetType>();
		delegates3[type.getId()] = delegate;
		return delegate->delegate;
	}
	else
	{
#ifdef _DEBUG
		auto delegate = std::dynamic_pointer_cast<Delegate3<Param1,Param2,Param3, RetType>>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		auto delegate = std::static_pointer_cast<Delegate3<Param1,Param2,Param3, RetType>>(it->second);
#endif
		return delegate->delegate;
	}
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class Param4, class RetType>
inline std::shared_ptr<typename T_Delegate_v4<Param1, Param2, Param3, Param4, RetType>::Type> DelegateHandler<DelegateFactory>::registerFunction4(const HashedString &type)
{
	auto it = delegates4.find(type.getId());
	if(it == delegates4.end())
	{
		auto delegate = DelegateFactory::createDelegate<Param1,Param2,Param3,Param4, RetType>();
		delegates4[type.getId()] = delegate;
		return delegate->delegate;
	}
	else
	{
#ifdef _DEBUG
		auto delegate = std::dynamic_pointer_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		auto delegate = std::static_pointer_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>>(it->second);
#endif
		return delegate->delegate;
	}
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
inline std::shared_ptr<typename T_Delegate_v5<Param1, Param2, Param3, Param4, Param5, RetType>::Type> DelegateHandler<DelegateFactory>::registerFunction5(const HashedString &type)
{
	auto it = delegates5.find(type.getId());
	if(it == delegates5.end())
	{
		auto delegate = DelegateFactory::createDelegate<Param1,Param2,Param3,Param4,Param5, RetType>();
		delegates5[type.getId()] = delegate;
		return delegate->delegate;
	}
	else
	{
#ifdef _DEBUG
		auto delegate = std::dynamic_pointer_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		auto delegate = std::static_pointer_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>>(it->second);
#endif
		return delegate->delegate;
	}
}

template<class DelegateFactory>
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
inline std::shared_ptr<typename T_Delegate_v6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>::Type> DelegateHandler<DelegateFactory>::registerFunction6(const HashedString &type)
{
	auto it = delegates6.find(type.getId());
	if(it == delegates6.end())
	{
		auto delegate = DelegateFactory::createDelegate<Param1,Param2,Param3,Param4,Param5,Param6, RetType>();
		delegates6[type.getId()] = delegate;
		return delegate->delegate;
	}
	else
	{
#ifdef _DEBUG
		auto delegate = std::dynamic_pointer_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		auto delegate = std::static_pointer_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>>(it->second);
#endif
		return delegate->delegate;
	}
}

//--------------------------------------------------------------------------------

template<class DelegateFactory>
bool DelegateHandler<DelegateFactory>::hasFunction(const HashedString &id, int num_params)
{
	if(num_params == 0)
	{
		auto it = delegates0.find(id.getId());
		if(it != delegates0.end())
			return true;
		else
			return false;
	}
	else if(num_params == 1)
	{
		auto it = delegates1.find(id.getId());
		if(it != delegates1.end())
			return true;
		else
			return false;
	}
	else if(num_params == 2)
	{
		auto it = delegates2.find(id.getId());
		if(it != delegates2.end())
			return true;
		else
			return false;
	}
	else if(num_params == 3)
	{
		auto it = delegates3.find(id.getId());
		if(it != delegates3.end())
			return true;
		else
			return false;
	}
	else if(num_params == 4)
	{
		auto it = delegates4.find(id.getId());
		if(it != delegates4.end())
			return true;
		else
			return false;
	}
	else if(num_params == 5)
	{
		auto it = delegates5.find(id.getId());
		if(it != delegates5.end())
			return true;
		else
			return false;
	}
	else if(num_params == 6)
	{
		auto it = delegates6.find(id.getId());
		if(it != delegates6.end())
			return true;
		else
			return false;
	}
	else
	{
		auto it = delegates0.find(id.getId());
		if(it != delegates0.end())
			return true;
		it = delegates1.find(id.getId());
		if(it != delegates1.end())
			return true;
		it = delegates2.find(id.getId());
		if(it != delegates2.end())
			return true;
		it = delegates3.find(id.getId());
		if(it != delegates3.end())
			return true;
		it = delegates4.find(id.getId());
		if(it != delegates4.end())
			return true;
		it = delegates5.find(id.getId());
		if(it != delegates5.end())
			return true;
		it = delegates6.find(id.getId());
		if(it != delegates6.end())
			return true;

		return false;
	}
}

} //namespace Addon
} //namespace Totem
