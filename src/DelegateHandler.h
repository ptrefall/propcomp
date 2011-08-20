#pragma once

/**
 * @file
 * @class DelegateHandler
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
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
 * Note: Some of the libraries Factotum EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * The delegate handler.
 * 
 */

#include "types_config.h"
#include "Property.h"

class Component;
class ComponentFactory;

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
	RetType call0(const T_HashedString &type);

	/**
	 * Calls all slots registered to the delegate signal of type holding one parameter.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 */
	template<class Param1, class RetType>
	RetType call1(const T_HashedString &type, const Param1 &param1);

	/**
	 * Calls all slots registered to the delegate signal of type holding two parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 * @param param1 Second parameter of type Param2.
	 */
	template<class Param1, class Param2, class RetType>
	RetType call2(const T_HashedString &type, const Param1 &param1, const Param2 &param2);

	/**
	 * Calls all slots registered to the delegate signal of type holding three parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 * @param param1 Second parameter of type Param2.
	 * @param param2 Third parameter of type Param3.
	 */
	template<class Param1, class Param2, class Param3, class RetType>
	RetType call3(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3);

	/**
	 * Calls all slots registered to the delegate signal of type holding four parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 * @param param1 Second parameter of type Param2.
	 * @param param2 Third parameter of type Param3.
	 * @param param3 Fourth parameter of type Param4.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class RetType>
	RetType call4(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4);

	/**
	 * Calls all slots registered to the delegate signal of type holding five parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 * @param param1 Second parameter of type Param2.
	 * @param param2 Third parameter of type Param3.
	 * @param param3 Fourth parameter of type Param4.
	 * @param param4 Fifth parameter of type Param5.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
	RetType call5(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5);

	/**
	 * Calls all slots registered to the delegate signal of type holding six parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 * @param param1 Second parameter of type Param2.
	 * @param param2 Third parameter of type Param3.
	 * @param param3 Fourth parameter of type Param4.
	 * @param param4 Fifth parameter of type Param5.
	 * @param param5 Sixth parameter of type Param6.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
	RetType call6(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6);

	/**
	 * Calls all slots registered to the delegate signal of type holding seven parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 * @param param1 Second parameter of type Param2.
	 * @param param2 Third parameter of type Param3.
	 * @param param3 Fourth parameter of type Param4.
	 * @param param4 Fifth parameter of type Param5.
	 * @param param5 Sixth parameter of type Param6.
	 * @param param6 Seventh parameter of type Param7.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
	RetType call7(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6, const Param7 &param7);

	/**
	 * Calls all slots registered to the delegate signal of type holding eight parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @param param0 First parameter of type Param1.
	 * @param param1 Second parameter of type Param2.
	 * @param param2 Third parameter of type Param3.
	 * @param param3 Fourth parameter of type Param4.
	 * @param param4 Fifth parameter of type Param5.
	 * @param param5 Sixth parameter of type Param6.
	 * @param param6 Seventh parameter of type Param7.
	 * @param param7 Eight parameter of type Param8.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
	RetType call8(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6, const Param7 &param7, const Param8 &param8);
	//--------------------------------------------------------------

	/**
	 * Register a slot to the delegate signal of type holding two parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires no parameters in the slot.
	 */
	template<class RetType>
	typename T_Delegate_v0<RetType>::Type &registerFunction0(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding one parameter.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires one parameters in the slot.
	 */
	template<class Param1, class RetType>
	typename T_Delegate_v1<Param1, RetType>::Type &registerFunction1(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding two parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires two parameters in the slot.
	 */
	template<class Param1, class Param2, class RetType>
	typename T_Delegate_v2<Param1, Param2, RetType>::Type &registerFunction2(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding three parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires three parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class RetType>
	typename T_Delegate_v3<Param1, Param2, Param3, RetType>::Type &registerFunction3(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding four parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires four parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class RetType>
	typename T_Delegate_v4<Param1, Param2, Param3, Param4, RetType>::Type &registerFunction4(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding five parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires five parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
	typename T_Delegate_v5<Param1, Param2, Param3, Param4, Param5, RetType>::Type &registerFunction5(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding six parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires six parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
	typename T_Delegate_v6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>::Type &registerFunction6(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding seven parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires seven parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
	typename T_Delegate_v7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType>::Type &registerFunction7(const T_HashedString &type);

	/**
	 * Register a slot to the delegate signal of type holding eight parameters.
	 *
	 * @param type The hashed type string id of the delegate.
	 * @return A signal that requires eight parameters in the slot.
	 */
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
	typename T_Delegate_v8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType>::Type &registerFunction8(const T_HashedString &type);

	//--------------------------------------------------------------

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
	/// Delegate holding a delegate that requires seven parameters.
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
	class Delegate7 : public IDelegate
	{
	public:
		/// Delegate taking seven parameters
		typename T_Delegate_v7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType>::Type delegate;
	};
	/// Delegate holding a delegate that requires eight parameters.
	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
	class Delegate8 : public IDelegate
	{
	public:
		/// Delegate taking eight parameters
		typename T_Delegate_v8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType>::Type delegate;
	};
	/// Map of parameter-less delegate delegates held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates0;
	/// Map of delegate delegates with one parameter held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates1;
	/// Map of delegate delegates with two parameters held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates2;
	/// Map of delegate delegates with three parameters held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates3;
	/// Map of delegate delegates with four parameters held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates4;
	/// Map of delegate delegates with five parameters held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates5;
	/// Map of delegate delegates with six parameters held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates6;
	/// Map of delegate delegates with seven parameters held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates7;
	/// Map of delegate delegates with eight parameters held by DelegateHandler.
	T_Map<T_HashedStringType, IDelegate*>::Type delegates8;
};

//------------------------------------------------------

template<class RetType>
inline RetType DelegateHandler::call0(const T_HashedString &type)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates0.find(type.getId());
	if(it == delegates0.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates0 registry!").c_str());

	return static_cast<Delegate0<RetType>*>(it->second)->delegate();
}

template<class Param1, class RetType>
inline RetType DelegateHandler::call1(const T_HashedString &type, const Param1 &param1)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates1.find(type.getId());
	if(it == delegates1.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates1 registry!").c_str());

#ifdef _DEBUG
	Delegate1<Param1, RetType> *delegate = dynamic_cast<Delegate1<Param1, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but the parameter type didn't match the registered type!").c_str());
	return delegate->delegate(param1);
#else
	return static_cast<Delegate1<Param1, RetType>*>(it->second)->delegate(param1);
#endif
}

template<class Param1, class Param2, class RetType>
inline RetType DelegateHandler::call2(const T_HashedString &type, const Param1 &param1, const Param2 &param2)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates2.find(type.getId());
	if(it == delegates2.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates2 registry!").c_str());

#ifdef _DEBUG
	Delegate2<Param1,Param2, RetType> *delegate = dynamic_cast<Delegate2<Param1,Param2, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2);
#else
	return static_cast<Delegate2<Param1,Param2, RetType>*>(it->second)->delegate(param1, param2);
#endif
}

template<class Param1, class Param2, class Param3, class RetType>
inline RetType DelegateHandler::call3(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates3.find(type.getId());
	if(it == delegates3.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates3 registry!").c_str());

#ifdef _DEBUG
	Delegate3<Param1,Param2,Param3, RetType> *delegate = dynamic_cast<Delegate3<Param1,Param2,Param3, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3);
#else
	return static_cast<Delegate3<Param1,Param2,Param3, RetType>*>(it->second)->delegate(param1, param2, param3);
#endif
}

template<class Param1, class Param2, class Param3, class Param4, class RetType>
inline RetType DelegateHandler::call4(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates4.find(type.getId());
	if(it == delegates4.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates4 registry!").c_str());

#ifdef _DEBUG
	Delegate4<Param1,Param2,Param3,Param4, RetType> *delegate = dynamic_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4);
#else
	return static_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>*>(it->second)->delegate(param1, param2, param3, param4);
#endif
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
inline RetType DelegateHandler::call5(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates5.find(type.getId());
	if(it == delegates5.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates5 registry!").c_str());

#ifdef _DEBUG
	Delegate5<Param1,Param2,Param3,Param4,Param5, RetType> *delegate = dynamic_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4, param5);
#else
	return static_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>*>(it->second)->delegate(param1, param2, param3, param4, param5);
#endif
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
inline RetType DelegateHandler::call6(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates6.find(type.getId());
	if(it == delegates6.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates6 registry!").c_str());

#ifdef _DEBUG
	Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType> *delegate = dynamic_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4, param5, param6);
#else
	return static_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>*>(it->second)->delegate(param1, param2, param3, param4, param5, param6);
#endif
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
inline RetType DelegateHandler::call7(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6, const Param7 &param7)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates7.find(type.getId());
	if(it == delegates7.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates7 registry!").c_str());

#ifdef _DEBUG
	Delegate7<Param1,Param2,Param3,Param4,Param5,Param6,Param7, RetType> *delegate = dynamic_cast<Delegate7<Param1,Param2,Param3,Param4,Param5,Param6,Param7, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4, param5, param6, param7);
#else
	return static_cast<Delegate7<Param1,Param2,Param3,Param4,Param5,Param6,Param7, RetType>*>(it->second)->delegate(param1, param2, param3, param4, param5, param6, param7);
#endif
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
inline RetType DelegateHandler::call8(const T_HashedString &type, const Param1 &param1, const Param2 &param2, const Param3 &param3, const Param4 &param4, const Param5 &param5, const Param6 &param6, const Param7 &param7, const Param8 &param8)
{
	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates8.find(type.getId());
	if(it == delegates8.end())
		throw T_Exception(("Couldn't find delegate type " + type.getStr() + " in delegates8 registry!").c_str());

#ifdef _DEBUG
	Delegate8<Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8, RetType> *delegate = dynamic_cast<Delegate8<Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8, RetType>*>(it->second);
	if(delegate == NULL_PTR)
		throw T_Exception(("Tried to call delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
	return delegate->delegate(param1, param2, param3, param4, param5, param6, param7, param8);
#else
	return static_cast<Delegate8<Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8, RetType>*>(it->second)->delegate(param1, param2, param3, param4, param5, param6, param7, param8);
#endif
}

//------------------------------------------------------------------

template<class RetType>
inline typename T_Delegate_v0<RetType>::Type &DelegateHandler::registerFunction0(const T_HashedString &type)
{
	Delegate0 *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates0.find(type.getId());
	if(it == delegates0.end())
	{
		delegate = new Delegate0();
		delegates0[type.getId()] = delegate;
	}
	else
	{
		delegate = static_cast<Delegate0*, RetType>(it->second);
	}

	return delegate->delegate;
}

template<class Param1, class RetType>
inline typename T_Delegate_v1<Param1, RetType>::Type &DelegateHandler::registerFunction1(const T_HashedString &type)
{
	Delegate1<Param1, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates1.find(type.getId());
	if(it == delegates1.end())
	{
		delegate = new Delegate1<Param1, RetType>();
		delegates1[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate1<Param1, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but the parameter type didn't match the registered type!").c_str());
#else
		delegate = static_cast<Delegate1<Param1, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}

template<class Param1, class Param2, class RetType>
inline typename T_Delegate_v2<Param1, Param2, RetType>::Type &DelegateHandler::registerFunction2(const T_HashedString &type)
{
	Delegate2<Param1,Param2, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates2.find(type.getId());
	if(it == delegates2.end())
	{
		delegate = new Delegate2<Param1,Param2, RetType>();
		delegates2[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate2<Param1,Param2, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		delegate = static_cast<Delegate2<Param1,Param2, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}

template<class Param1, class Param2, class Param3, class RetType>
inline typename T_Delegate_v3<Param1, Param2, Param3, RetType>::Type &DelegateHandler::registerFunction3(const T_HashedString &type)
{
	Delegate3<Param1,Param2,Param3, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates3.find(type.getId());
	if(it == delegates3.end())
	{
		delegate = new Delegate3<Param1,Param2,Param3, RetType>();
		delegates3[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate3<Param1,Param2,Param3, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		delegate = static_cast<Delegate3<Param1,Param2,Param3, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}

template<class Param1, class Param2, class Param3, class Param4, class RetType>
inline typename T_Delegate_v4<Param1, Param2, Param3, Param4, RetType>::Type &DelegateHandler::registerFunction4(const T_HashedString &type)
{
	Delegate4<Param1,Param2,Param3,Param4, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates4.find(type.getId());
	if(it == delegates4.end())
	{
		delegate = new Delegate4<Param1,Param2,Param3,Param4, RetType>();
		delegates4[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		delegate = static_cast<Delegate4<Param1,Param2,Param3,Param4, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
inline typename T_Delegate_v5<Param1, Param2, Param3, Param4, Param5, RetType>::Type &DelegateHandler::registerFunction5(const T_HashedString &type)
{
	Delegate5<Param1,Param2,Param3,Param4,Param5, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates5.find(type.getId());
	if(it == delegates5.end())
	{
		delegate = new Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>();
		delegates5[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		delegate = static_cast<Delegate5<Param1,Param2,Param3,Param4,Param5, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
inline typename T_Delegate_v6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>::Type &DelegateHandler::registerFunction6(const T_HashedString &type)
{
	Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates6.find(type.getId());
	if(it == delegates6.end())
	{
		delegate = new Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>();
		delegates6[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		delegate = static_cast<Delegate6<Param1,Param2,Param3,Param4,Param5,Param6, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
inline typename T_Delegate_v7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType>::Type &DelegateHandler::registerFunction7(const T_HashedString &type)
{
	Delegate7<Param1,Param2,Param3,Param4,Param5,Param6,Param7, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates7.find(type.getId());
	if(it == delegates7.end())
	{
		delegate = new Delegate7<Param1,Param2,Param3,Param4,Param5,Param6,Param7, RetType>();
		delegates7[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate7<Param1,Param2,Param3,Param4,Param5,Param6,Param7, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		delegate = static_cast<Delegate7<Param1,Param2,Param3,Param4,Param5,Param6,Param7, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
inline typename T_Delegate_v8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType>::Type &DelegateHandler::registerFunction8(const T_HashedString &type)
{
	Delegate8<Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8, RetType> *delegate = NULL_PTR;

	T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates8.find(type.getId());
	if(it == delegates8.end())
	{
		delegate = new Delegate8<Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8, RetType>();
		delegates8[type.getId()] = delegate;
	}
	else
	{
#ifdef _DEBUG
		delegate = dynamic_cast<Delegate8<Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8, RetType>*>(it->second);
		if(delegate == NULL_PTR)
			throw T_Exception(("Tried to return the delegate " + type.getStr() + ", but one or both of the parameter types didn't match the registered types!").c_str());
#else
		delegate = static_cast<Delegate8<Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8, RetType>*>(it->second);
#endif
	}

	return delegate->delegate;
}
