#pragma once

/**
 * @file
 * @class EventHandler
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief EventHandler base class
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
 * Note: Some of the libraries Component-based EventHandler Engine may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * The event handler.
 * 
 */

#include "types_config.h"
#include "Property.h"

class Component;
class ComponentFactory;

class EventHandler
{
public:
	/**
	 * Constructor
	 */
	EventHandler() {}
	/**
	 * Destructor
	 */
	virtual ~EventHandler() {}

	//--------------------------------------------------------------

	/**
	 * Calls all slots registered to the argument-less event signal of type.
	 *
	 * @param type The hashed type string id of the event.
	 */
	void sendEvent0(const T_HashedString &type);

	/**
	 * Calls all slots registered to the event signal of type holding one argument.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 */
	template<class T> void sendEvent1(const T_HashedString &type, const T &arg0);

	/**
	 * Calls all slots registered to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 */
	template<class T, class U> void sendEvent2(const T_HashedString &type, const T &arg0, const U &arg1);

	/**
	 * Calls all slots registered to the event signal of type holding three arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 */
	template<class T, class U, class V> void sendEvent3(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2);

	/**
	 * Calls all slots registered to the event signal of type holding four arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 */
	template<class T, class U, class V, class W> void sendEvent4(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3);

	/**
	 * Calls all slots registered to the event signal of type holding five arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 * @param arg4 Fifth argument of type X.
	 */
	template<class T, class U, class V, class W, class X> void sendEvent5(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4);

	/**
	 * Calls all slots registered to the event signal of type holding six arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 * @param arg4 Fifth argument of type X.
	 * @param arg5 Sixth argument of type Y.
	 */
	template<class T, class U, class V, class W, class X, class Y> void sendEvent6(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4, const Y &arg5);

	/**
	 * Calls all slots registered to the event signal of type holding seven arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 * @param arg4 Fifth argument of type X.
	 * @param arg5 Sixth argument of type Y.
	 * @param arg6 Seventh argument of type Z.
	 */
	template<class T, class U, class V, class W, class X, class Y, class Z> void sendEvent7(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4, const Y &arg5, const Z &arg6);

	/**
	 * Calls all slots registered to the event signal of type holding eight arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 * @param arg4 Fifth argument of type X.
	 * @param arg5 Sixth argument of type Y.
	 * @param arg6 Seventh argument of type Z.
	 * @param arg7 Eight argument of type S.
	 */
	template<class T, class U, class V, class W, class X, class Y, class Z, class S> void sendEvent8(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4, const Y &arg5, const Z &arg6, const S &arg7);

	//--------------------------------------------------------------

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires no arguments in the slot.
	 */
	T_Signal_v0<>::Type &registerToEvent0(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding one argument.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires one arguments in the slot.
	 */
	template<class T>typename T_Signal_v1<const T&>::Type &registerToEvent1(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires two arguments in the slot.
	 */
	template<class T, class U>typename T_Signal_v2<const T&, const U&>::Type &registerToEvent2(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding three arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires three arguments in the slot.
	 */
	template<class T, class U, class V>typename T_Signal_v3<const T&, const U&, const V&>::Type &registerToEvent3(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding four arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires four arguments in the slot.
	 */
	template<class T, class U, class V, class W>typename T_Signal_v4<const T&, const U&, const V&, const W&>::Type &registerToEvent4(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding five arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires five arguments in the slot.
	 */
	template<class T, class U, class V, class W, class X>typename T_Signal_v5<const T&, const U&, const V&, const W&, const X&>::Type &registerToEvent5(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding six arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires six arguments in the slot.
	 */
	template<class T, class U, class V, class W, class X, class Y>typename T_Signal_v6<const T&, const U&, const V&, const W&, const X&, const Y&>::Type &registerToEvent6(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding seven arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires seven arguments in the slot.
	 */
	template<class T, class U, class V, class W, class X, class Y, class Z>typename T_Signal_v7<const T&, const U&, const V&, const W&, const X&, const Y&, const Z&>::Type &registerToEvent7(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding eight arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires eight arguments in the slot.
	 */
	template<class T, class U, class V, class W, class X, class Y, class Z, class S>typename T_Signal_v8<const T&, const U&, const V&, const W&, const X&, const Y&, const Z&, const S&>::Type &registerToEvent8(const T_HashedString &type);

	//--------------------------------------------------------------

protected:

	/**
	 * In order to support multiple different types registered into the event maps
	 * we need to store them as interfaces, else we can only store one specific type
	 * into the map (must specify value of template classes).
	 */
	class IEventSignal
	{
	public:
		/// Constructor.
		IEventSignal() {}
		/// Destructor.
		virtual ~IEventSignal() {}
	};
	/// Event holding an argument-less signal.
	class EventSignal0 : public IEventSignal
	{
	public:
		/// Signal taking no arguments
		T_Signal_v0<>::Type signal;
	};
	/// Event holding a signal that requires a single argument.
	template<class T> class EventSignal1 : public IEventSignal
	{
	public:
		/// Signal taking one arguments
		typename T_Signal_v1<const T&>::Type signal;
	};
	/// Event holding a signal that requires two arguments.
	template<class T, class U> class EventSignal2 : public IEventSignal
	{
	public:
		/// Signal taking two arguments
		typename T_Signal_v2<const T&, const U&>::Type signal;
	};
	/// Event holding a signal that requires three arguments.
	template<class T, class U, class V> class EventSignal3 : public IEventSignal
	{
	public:
		/// Signal taking three arguments
		typename T_Signal_v3<const T&, const U&, const V&>::Type signal;
	};
	/// Event holding a signal that requires four arguments.
	template<class T, class U, class V, class W> class EventSignal4 : public IEventSignal
	{
	public:
		/// Signal taking four arguments
		typename T_Signal_v4<const T&, const U&, const V&, const W&>::Type signal;
	};
	/// Event holding a signal that requires five arguments.
	template<class T, class U, class V, class W, class X> class EventSignal5 : public IEventSignal
	{
	public:
		/// Signal taking five arguments
		typename T_Signal_v5<const T&, const U&, const V&, const W&, const X&>::Type signal;
	};
	/// Event holding a signal that requires six arguments.
	template<class T, class U, class V, class W, class X, class Y> class EventSignal6 : public IEventSignal
	{
	public:
		/// Signal taking six arguments
		typename T_Signal_v6<const T&, const U&, const V&, const W&, const X&, const Y&>::Type signal;
	};
	/// Event holding a signal that requires seven arguments.
	template<class T, class U, class V, class W, class X, class Y, class Z> class EventSignal7 : public IEventSignal
	{
	public:
		/// Signal taking seven arguments
		typename T_Signal_v7<const T&, const U&, const V&, const W&, const X&, const Y&, const Z&>::Type signal;
	};
	/// Event holding a signal that requires eight arguments.
	template<class T, class U, class V, class W, class X, class Y, class Z, class S> class EventSignal8 : public IEventSignal
	{
	public:
		/// Signal taking eight arguments
		typename T_Signal_v8<const T&, const U&, const V&, const W&, const X&, const Y&, const Z&, const S&>::Type signal;
	};
	/// Map of argument-less event signals held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events0;
	/// Map of event signals with one argument held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events1;
	/// Map of event signals with two arguments held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events2;
	/// Map of event signals with three arguments held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events3;
	/// Map of event signals with four arguments held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events4;
	/// Map of event signals with five arguments held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events5;
	/// Map of event signals with six arguments held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events6;
	/// Map of event signals with seven arguments held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events7;
	/// Map of event signals with eight arguments held by EventHandler.
	T_Map<T_HashedStringType, IEventSignal*>::Type events8;
};

//------------------------------------------------------

inline void EventHandler::sendEvent0(const T_HashedString &type)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events0.find(type.getId());
	if(it == events0.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events0 registry!").c_str());

	static_cast<EventSignal0*>(it->second)->signal.invoke();
}

template<class T>
inline void EventHandler::sendEvent1(const T_HashedString &type, const T &arg0)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events1.find(type.getId());
	if(it == events1.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events1 registry!").c_str());

#ifdef _DEBUG
	EventSignal1<T> *signal = dynamic_cast<EventSignal1<T>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but the argument type didn't match the registered type!").c_str());
	signal->signal.invoke(arg0);
#else
	static_cast<EventSignal1<T>*>(it->second)->signal.invoke(arg0);
#endif
}

template<class T, class U>
inline void EventHandler::sendEvent2(const T_HashedString &type, const T &arg0, const U &arg1)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events2.find(type.getId());
	if(it == events2.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events2 registry!").c_str());

#ifdef _DEBUG
	EventSignal2<T,U> *signal = dynamic_cast<EventSignal2<T,U>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1);
#else
	static_cast<EventSignal2<T,U>*>(it->second)->signal.invoke(arg0, arg1);
#endif
}

template<class T, class U, class V>
inline void EventHandler::sendEvent3(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events3.find(type.getId());
	if(it == events3.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events3 registry!").c_str());

#ifdef _DEBUG
	EventSignal3<T,U,V> *signal = dynamic_cast<EventSignal3<T,U,V>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2);
#else
	static_cast<EventSignal3<T,U,V>*>(it->second)->signal.invoke(arg0, arg1, arg2);
#endif
}

template<class T, class U, class V, class W>
inline void EventHandler::sendEvent4(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events4.find(type.getId());
	if(it == events4.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events4 registry!").c_str());

#ifdef _DEBUG
	EventSignal4<T,U,V,W> *signal = dynamic_cast<EventSignal4<T,U,V,W>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3);
#else
	static_cast<EventSignal4<T,U,V,W>*>(it->second)->signal.invoke(arg0, arg1, arg2, arg3);
#endif
}

template<class T, class U, class V, class W, class X>
inline void EventHandler::sendEvent5(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events5.find(type.getId());
	if(it == events5.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events5 registry!").c_str());

#ifdef _DEBUG
	EventSignal5<T,U,V,W,X> *signal = dynamic_cast<EventSignal5<T,U,V,W,X>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3, arg4);
#else
	static_cast<EventSignal5<T,U,V,W,X>*>(it->second)->signal.invoke(arg0, arg1, arg2, arg3, arg4);
#endif
}

template<class T, class U, class V, class W, class X, class Y>
inline void EventHandler::sendEvent6(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4, const Y &arg5)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events6.find(type.getId());
	if(it == events6.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events6 registry!").c_str());

#ifdef _DEBUG
	EventSignal6<T,U,V,W,X,Y> *signal = dynamic_cast<EventSignal6<T,U,V,W,X,Y>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5);
#else
	static_cast<EventSignal6<T,U,V,W,X,Y>*>(it->second)->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5);
#endif
}

template<class T, class U, class V, class W, class X, class Y, class Z>
inline void EventHandler::sendEvent7(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4, const Y &arg5, const Z &arg6)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events7.find(type.getId());
	if(it == events7.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events7 registry!").c_str());

#ifdef _DEBUG
	EventSignal7<T,U,V,W,X,Y,Z> *signal = dynamic_cast<EventSignal7<T,U,V,W,X,Y,Z>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
#else
	static_cast<EventSignal7<T,U,V,W,X,Y,Z>*>(it->second)->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
#endif
}

template<class T, class U, class V, class W, class X, class Y, class Z, class S>
inline void EventHandler::sendEvent8(const T_HashedString &type, const T &arg0, const U &arg1, const V &arg2, const W &arg3, const X &arg4, const Y &arg5, const Z &arg6, const S &arg7)
{
	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events8.find(type.getId());
	if(it == events8.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events8 registry!").c_str());

#ifdef _DEBUG
	EventSignal8<T,U,V,W,X,Y,Z,S> *signal = dynamic_cast<EventSignal8<T,U,V,W,X,Y,Z,S>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
#else
	static_cast<EventSignal8<T,U,V,W,X,Y,Z,S>*>(it->second)->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
#endif
}

//------------------------------------------------------------------

inline T_Signal_v0<>::Type &EventHandler::registerToEvent0(const T_HashedString &type)
{
	EventSignal0 *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events0.find(type.getId());
	if(it == events0.end())
	{
		signal = new EventSignal0();
		events0[type.getId()] = signal;
	}
	else
	{
		signal = static_cast<EventSignal0*>(it->second);
	}

	return signal->signal;
}

template<class T>
inline typename T_Signal_v1<const T&>::Type &EventHandler::registerToEvent1(const T_HashedString &type)
{
	EventSignal1<T> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events1.find(type.getId());
	if(it == events1.end())
	{
		signal = new EventSignal1<T>();
		events1[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal1<T>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried to return the event signal " + type.getStr() + ", but the argument type didn't match the registered type!").c_str());
#else
		signal = static_cast<EventSignal1<T>*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U>
inline typename T_Signal_v2<const T&, const U&>::Type &EventHandler::registerToEvent2(const T_HashedString &type)
{
	EventSignal2<T,U> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events2.find(type.getId());
	if(it == events2.end())
	{
		signal = new EventSignal2<T,U>();
		events2[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal2<T,U>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal2<T,U>*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U, class V>
inline typename T_Signal_v3<const T&, const U&, const V&>::Type &EventHandler::registerToEvent3(const T_HashedString &type)
{
	EventSignal3<T,U,V> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events3.find(type.getId());
	if(it == events3.end())
	{
		signal = new EventSignal3<T,U,V>();
		events3[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal3<T,U,V>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal3<T,U,V>*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U, class V, class W>
inline typename T_Signal_v4<const T&, const U&, const V&, const W&>::Type &EventHandler::registerToEvent4(const T_HashedString &type)
{
	EventSignal4<T,U,V,W> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events4.find(type.getId());
	if(it == events4.end())
	{
		signal = new EventSignal4<T,U,V,W>();
		events4[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal4<T,U,V,W>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal4<T,U,V,W>*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U, class V, class W, class X>
inline typename T_Signal_v5<const T&, const U&, const V&, const W&, const X&>::Type &EventHandler::registerToEvent5(const T_HashedString &type)
{
	EventSignal5<T,U,V,W,X> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events5.find(type.getId());
	if(it == events5.end())
	{
		signal = new EventSignal5<T,U,V,W,X>();
		events5[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal5<T,U,V,W,X>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal5<T,U,V,W,X>*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U, class V, class W, class X, class Y>
inline typename T_Signal_v6<const T&, const U&, const V&, const W&, const X&, const Y&>::Type &EventHandler::registerToEvent6(const T_HashedString &type)
{
	EventSignal6<T,U,V,W,X,Y> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events6.find(type.getId());
	if(it == events6.end())
	{
		signal = new EventSignal6<T,U,V,W,X,Y>();
		events6[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal6<T,U,V,W,X,Y>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal6<T,U,V,W,X,Y>*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U, class V, class W, class X, class Y, class Z>
inline typename T_Signal_v7<const T&, const U&, const V&, const W&, const X&, const Y&, const Z&>::Type &EventHandler::registerToEvent7(const T_HashedString &type)
{
	EventSignal7<T,U,V,W,X,Y,Z> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events7.find(type.getId());
	if(it == events7.end())
	{
		signal = new EventSignal7<T,U,V,W,X,Y,Z>();
		events7[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal7<T,U,V,W,X,Y,Z>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal7<T,U,V,W,X,Y,Z>*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U, class V, class W, class X, class Y, class Z, class S>
inline typename T_Signal_v8<const T&, const U&, const V&, const W&, const X&, const Y&, const Z&, const S&>::Type &EventHandler::registerToEvent8(const T_HashedString &type)
{
	EventSignal8<T,U,V,W,X,Y,Z,S> *signal = NULL_PTR;

	T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events8.find(type.getId());
	if(it == events8.end())
	{
		signal = new EventSignal8<T,U,V,W,X,Y,Z,S>();
		events8[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal8<T,U,V,W,X,Y,Z,S>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal8<T,U,V,W,X,Y,Z,S>*>(it->second);
#endif
	}

	return signal->signal;
}
