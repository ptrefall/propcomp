#pragma once

#include "../Property.h"
#include "../HashedString.h"

#include "../../../depends/Standard/sigslot.h"
#include <unordered_map>
#include <memory>

namespace Totem {
namespace Addon {

class Component;
class ComponentFactory;

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
template<class DefaultParam = void*>
class EventSignal0 : public IEventSignal
{
public:
	/// Signal taking no arguments
	sigslot::signal0<> signal;
};
/// Event holding a signal that requires a single argument.
template<class T> 
class EventSignal1 : public IEventSignal
{
public:
	/// Signal taking one arguments
	sigslot::signal1<T> signal;
};
/// Event holding a signal that requires two arguments.
template<class T, class U> 
class EventSignal2 : public IEventSignal
{
public:
	/// Signal taking two arguments
	sigslot::signal2<T, U> signal;
};
/// Event holding a signal that requires three arguments.
template<class T, class U, class V> 
class EventSignal3 : public IEventSignal
{
public:
	/// Signal taking three arguments
	sigslot::signal3<T, U, V> signal;
};
/// Event holding a signal that requires four arguments.
template<class T, class U, class V, class W> 
class EventSignal4 : public IEventSignal
{
public:
	/// Signal taking four arguments
	sigslot::signal4<T, U, V, W> signal;
};
/// Event holding a signal that requires five arguments.
template<class T, class U, class V, class W, class X> 
class EventSignal5 : public IEventSignal
{
public:
	/// Signal taking five arguments
	sigslot::signal5<T, U, V, W, X> signal;
};
/// Event holding a signal that requires six arguments.
template<class T, class U, class V, class W, class X, class Y> 
class EventSignal6 : public IEventSignal
{
public:
	/// Signal taking six arguments
	sigslot::signal6<T, U, V, W, X, Y> signal;
};

class DefaultEventFactory
{
public:
	static std::shared_ptr<EventSignal0<>> createEvent()
	{
		return std::make_shared<EventSignal0<>>();
	}

	template<class Param1>
	static std::shared_ptr<EventSignal1<Param1>> createEvent()
	{
		return std::make_shared<EventSignal1<Param1>>();
	}

	template<class Param1, class Param2>
	static std::shared_ptr<EventSignal2<Param1,Param2>> createEvent()
	{
		return std::make_shared<EventSignal2<Param1,Param2>>();
	}

	template<class Param1, class Param2, class Param3>
	static std::shared_ptr<EventSignal3<Param1,Param2,Param3>> createEvent()
	{
		return std::make_shared<EventSignal3<Param1,Param2,Param3>>();
	}

	template<class Param1, class Param2, class Param3, class Param4>
	static std::shared_ptr<EventSignal4<Param1,Param2,Param3,Param4>> createEvent()
	{
		return std::make_shared<EventSignal4<Param1,Param2,Param3,Param4>>();
	}

	template<class Param1, class Param2, class Param3, class Param4, class Param5>
	static std::shared_ptr<EventSignal5<Param1,Param2,Param3,Param4,Param5>> createEvent()
	{
		return std::make_shared<EventSignal5<Param1,Param2,Param3,Param4,Param5>>();
	}

	template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
	static std::shared_ptr<EventSignal6<Param1,Param2,Param3,Param4,Param5,Param6>> createEvent()
	{
		return std::make_shared<EventSignal6<Param1,Param2,Param3,Param4,Param5,Param6>>();
	}
};

template<class EventFactory = DefaultEventFactory>
class EventSystem : public sigslot::has_slots<>
{
public:
	/**
	 * Calls all slots registered to the argument-less event signal of type.
	 *
	 * @param type The hashed type string id of the event.
	 */
	void sendEvent0(const HashedString &type);

	/**
	 * Calls all slots registered to the event signal of type holding one argument.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 */
	template<class T> 
	void sendEvent1(const HashedString &type, T arg0);

	/**
	 * Calls all slots registered to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 */
	template<class T, class U> 
	void sendEvent2(const HashedString &type, T arg0, U arg1);

	/**
	 * Calls all slots registered to the event signal of type holding three arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 */
	template<class T, class U, class V> 
	void sendEvent3(const HashedString &type, T arg0, U arg1, V arg2);

	/**
	 * Calls all slots registered to the event signal of type holding four arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 */
	template<class T, class U, class V, class W> 
	void sendEvent4(const HashedString &type, T arg0, U arg1, V arg2, W arg3);

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
	template<class T, class U, class V, class W, class X> 
	void sendEvent5(const HashedString &type, T arg0, U arg1, V arg2, W arg3, X arg4);

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
	template<class T, class U, class V, class W, class X, class Y> 
	void sendEvent6(const HashedString &type, T arg0, U arg1, V arg2, W arg3, X arg4, Y arg5);

	//--------------------------------------------------------------

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires no arguments in the slot.
	 */
	sigslot::signal0<> &registerToEvent0(const HashedString &type);

	/**
	 * Register a slot to the event signal of type holding one argument.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires one arguments in the slot.
	 */
	template<class T>
	sigslot::signal1<T> &registerToEvent1(const HashedString &type);

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires two arguments in the slot.
	 */
	template<class T, class U>
	sigslot::signal2<T, U> &registerToEvent2(const HashedString &type);

	/**
	 * Register a slot to the event signal of type holding three arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires three arguments in the slot.
	 */
	template<class T, class U, class V>
	sigslot::signal3<T, U, V> &registerToEvent3(const HashedString &type);

	/**
	 * Register a slot to the event signal of type holding four arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires four arguments in the slot.
	 */
	template<class T, class U, class V, class W>
	sigslot::signal4<T, U, V, W> &registerToEvent4(const HashedString &type);

	/**
	 * Register a slot to the event signal of type holding five arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires five arguments in the slot.
	 */
	template<class T, class U, class V, class W, class X>
	sigslot::signal5<T, U, V, W, X> &registerToEvent5(const HashedString &type);

	/**
	 * Register a slot to the event signal of type holding six arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires six arguments in the slot.
	 */
	template<class T, class U, class V, class W, class X, class Y>
	sigslot::signal6<T, U, V, W, X, Y> &registerToEvent6(const HashedString &type);

	//--------------------------------------------------------------

	bool hasEvent(const HashedString &id, int num_params = -1);

protected:
	/// Map of argument-less event signals held by TemplateEventHandler.
	std::unordered_map<unsigned int, std::shared_ptr<IEventSignal>> events0;
	/// Map of event signals with one argument held by TemplateEventHandler.
	std::unordered_map<unsigned int, std::shared_ptr<IEventSignal>> events1;
	/// Map of event signals with two arguments held by TemplateEventHandler.
	std::unordered_map<unsigned int, std::shared_ptr<IEventSignal>> events2;
	/// Map of event signals with three arguments held by TemplateEventHandler.
	std::unordered_map<unsigned int, std::shared_ptr<IEventSignal>> events3;
	/// Map of event signals with four arguments held by TemplateEventHandler.
	std::unordered_map<unsigned int, std::shared_ptr<IEventSignal>> events4;
	/// Map of event signals with five arguments held by TemplateEventHandler.
	std::unordered_map<unsigned int, std::shared_ptr<IEventSignal>> events5;
	/// Map of event signals with six arguments held by TemplateEventHandler.
	std::unordered_map<unsigned int, std::shared_ptr<IEventSignal>> events6;
};

//------------------------------------------------------

template<class EventFactory>
inline void EventSystem<EventFactory>::sendEvent0(const HashedString &type)
{
	auto it = events0.find(type.getId());
	if(it == events0.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events0 registry!").c_str());

	std::static_pointer_cast<EventSignal0<>>(it->second)->signal.invoke();
}

template<class EventFactory>
template<class T>
inline void EventSystem<EventFactory>::sendEvent1(const HashedString &type, T arg0)
{
	auto it = events1.find(type.getId());
	if(it == events1.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events1 registry!").c_str());

#ifdef _DEBUG
	auto signal = std::dynamic_pointer_cast<EventSignal1<T>>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but the argument type didn't match the registered type!").c_str());
	signal->signal.invoke(arg0);
#else
	static_pointer_cast<EventSignal1<T>>(it->second)->signal.invoke(arg0);
#endif
}

template<class EventFactory>
template<class T, class U>
inline void EventSystem<EventFactory>::sendEvent2(const HashedString &type, T arg0, U arg1)
{
	auto it = events2.find(type.getId());
	if(it == events2.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events2 registry!").c_str());

#ifdef _DEBUG
	auto signal = std::dynamic_pointer_cast<EventSignal2<T,U>>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1);
#else
	std::static_pointer_cast<EventSignal2<T,U>>(it->second)->signal.invoke(arg0, arg1);
#endif
}

template<class EventFactory>
template<class T, class U, class V>
inline void EventSystem<EventFactory>::sendEvent3(const HashedString &type, T arg0, U arg1, V arg2)
{
	auto it = events3.find(type.getId());
	if(it == events3.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events3 registry!").c_str());

#ifdef _DEBUG
	auto signal = std::dynamic_pointer_cast<EventSignal3<T,U,V>>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2);
#else
	std::static_pointer_cast<EventSignal3<T,U,V>>(it->second)->signal.invoke(arg0, arg1, arg2);
#endif
}

template<class EventFactory>
template<class T, class U, class V, class W>
inline void EventSystem<EventFactory>::sendEvent4(const HashedString &type, T arg0, U arg1, V arg2, W arg3)
{
	auto it = events4.find(type.getId());
	if(it == events4.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events4 registry!").c_str());

#ifdef _DEBUG
	auto signal = std::dynamic_pointer_cast<EventSignal4<T,U,V,W>>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3);
#else
	std::static_pointer_cast<EventSignal4<T,U,V,W>>(it->second)->signal.invoke(arg0, arg1, arg2, arg3);
#endif
}

template<class EventFactory>
template<class T, class U, class V, class W, class X>
inline void EventSystem<EventFactory>::sendEvent5(const HashedString &type, T arg0, U arg1, V arg2, W arg3, X arg4)
{
	auto it = events5.find(type.getId());
	if(it == events5.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events5 registry!").c_str());

#ifdef _DEBUG
	auto signal = std::dynamic_pointer_cast<EventSignal5<T,U,V,W,X>>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3, arg4);
#else
	std::static_pointer_cast<EventSignal5<T,U,V,W,X>>(it->second)->signal.invoke(arg0, arg1, arg2, arg3, arg4);
#endif
}

template<class EventFactory>
template<class T, class U, class V, class W, class X, class Y>
inline void EventSystem<EventFactory>::sendEvent6(const HashedString &type, T arg0, U arg1, V arg2, W arg3, X arg4, Y arg5)
{
	auto it = events6.find(type.getId());
	if(it == events6.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events6 registry!").c_str());

#ifdef _DEBUG
	auto signal = std::dynamic_pointer_cast<EventSignal6<T,U,V,W,X,Y>>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to invoke event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5);
#else
	std::static_pointer_cast<EventSignal6<T,U,V,W,X,Y>>(it->second)->signal.invoke(arg0, arg1, arg2, arg3, arg4, arg5);
#endif
}

//------------------------------------------------------------------

template<class EventFactory>
inline sigslot::signal0<> &EventSystem<EventFactory>::registerToEvent0(const HashedString &type)
{
	auto it = events0.find(type.getId());
	if(it == events0.end())
	{
		auto signal = EventFactory::createEvent();
		events0[type.getId()] = signal;
		return signal->signal;
	}
	else
	{
		auto signal = std::static_pointer_cast<EventSignal0<>>(it->second);
		return signal->signal;
	}
}

template<class EventFactory>
template<class T>
inline sigslot::signal1<T> &EventSystem<EventFactory>::registerToEvent1(const HashedString &type)
{
	auto it = events1.find(type.getId());
	if(it == events1.end())
	{
		auto signal = EventFactory::createEvent<T>();
		events1[type.getId()] = signal;
		return signal->signal;
	}
	else
	{
#ifdef _DEBUG
		auto signal = std::dynamic_pointer_cast<EventSignal1<T>>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried to return the event signal " + type.getStr() + ", but the argument type didn't match the registered type!").c_str());
#else
		signal = std::static_pointer_cast<EventSignal1<T>>(it->second);
#endif
		return signal->signal;
	}
}

template<class EventFactory>
template<class T, class U>
inline sigslot::signal2<T, U> &EventSystem<EventFactory>::registerToEvent2(const HashedString &type)
{
	auto it = events2.find(type.getId());
	if(it == events2.end())
	{
		auto signal = EventFactory::createEvent<T,U>();
		events2[type.getId()] = signal;
		return signal->signal;
	}
	else
	{
#ifdef _DEBUG
		auto signal = std::dynamic_pointer_cast<EventSignal2<T,U>>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = std::static_pointer_cast<EventSignal2<T,U>>(it->second);
#endif
		return signal->signal;
	}
}

template<class EventFactory>
template<class T, class U, class V>
inline sigslot::signal3<T, U, V> &EventSystem<EventFactory>::registerToEvent3(const HashedString &type)
{
	auto it = events3.find(type.getId());
	if(it == events3.end())
	{
		auto signal = EventFactory::createEvent<T,U,V>();
		events3[type.getId()] = signal;
		return signal->signal;
	}
	else
	{
#ifdef _DEBUG
		auto signal = std::dynamic_pointer_cast<EventSignal3<T,U,V>>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = std::static_pointer_cast<EventSignal3<T,U,V>>(it->second);
#endif
		return signal->signal;
	}
}

template<class EventFactory>
template<class T, class U, class V, class W>
inline sigslot::signal4<T, U, V, W> &EventSystem<EventFactory>::registerToEvent4(const HashedString &type)
{
	auto it = events4.find(type.getId());
	if(it == events4.end())
	{
		auto signal = EventFactory::createEvent<T,U,V,W>();
		events4[type.getId()] = signal;
		return signal->signal;
	}
	else
	{
#ifdef _DEBUG
		auto signal = std::dynamic_pointer_cast<EventSignal4<T,U,V,W>>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = std::static_pointer_cast<EventSignal4<T,U,V,W>>(it->second);
#endif
		return signal->signal;
	}
}

template<class EventFactory>
template<class T, class U, class V, class W, class X>
inline sigslot::signal5<T, U, V, W, X> &EventSystem<EventFactory>::registerToEvent5(const HashedString &type)
{
	auto it = events5.find(type.getId());
	if(it == events5.end())
	{
		auto signal = EventFactory::createEvent<T,U,V,W,X>();
		events5[type.getId()] = signal;
		return signal->signal;
	}
	else
	{
#ifdef _DEBUG
		auto signal = std::dynamic_pointer_cast<EventSignal5<T,U,V,W,X>>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = std::static_pointer_cast<EventSignal5<T,U,V,W,X>>(it->second);
#endif
		return signal->signal;
	}
}

template<class EventFactory>
template<class T, class U, class V, class W, class X, class Y>
inline sigslot::signal6<T, U, V, W, X, Y> &EventSystem<EventFactory>::registerToEvent6(const HashedString &type)
{
	auto it = events6.find(type.getId());
	if(it == events6.end())
	{
		auto signal = EventFactory::createEvent<T,U,V,W,X,Y>();
		events6[type.getId()] = signal;
		return signal->signal;
	}
	else
	{
#ifdef _DEBUG
		auto signal = std::dynamic_pointer_cast<EventSignal6<T,U,V,W,X,Y>>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = std::static_pointer_cast<EventSignal6<T,U,V,W,X,Y>>(it->second);
#endif
		return signal->signal;
	}
}

//---------------------------------------------------------------------------------------

template<class EventFactory>
bool EventSystem<EventFactory>::hasEvent(const HashedString &id, int num_params)
{
	if(num_params == 0)
	{
		auto it = events0.find(id.getId());
		if(it != events0.end())
			return true;
		else
			return false;
	}
	else if(num_params == 1)
	{
		auto it = events1.find(id.getId());
		if(it != events1.end())
			return true;
		else
			return false;
	}
	else if(num_params == 2)
	{
		auto it = events2.find(id.getId());
		if(it != events2.end())
			return true;
		else
			return false;
	}
	else if(num_params == 3)
	{
		auto it = events3.find(id.getId());
		if(it != events3.end())
			return true;
		else
			return false;
	}
	else if(num_params == 4)
	{
		auto it = events4.find(id.getId());
		if(it != events4.end())
			return true;
		else
			return false;
	}
	else if(num_params == 5)
	{
		auto it = events5.find(id.getId());
		if(it != events5.end())
			return true;
		else
			return false;
	}
	else if(num_params == 6)
	{
		auto it = events6.find(id.getId());
		if(it != events6.end())
			return true;
		else
			return false;
	}
	else
	{
		auto it = events0.find(id.getId());
		if(it != events0.end())
			return true;
		it = events1.find(id.getId());
		if(it != events1.end())
			return true;
		it = events2.find(id.getId());
		if(it != events2.end())
			return true;
		it = events3.find(id.getId());
		if(it != events3.end())
			return true;
		it = events4.find(id.getId());
		if(it != events4.end())
			return true;
		it = events5.find(id.getId());
		if(it != events5.end())
			return true;
		it = events6.find(id.getId());
		if(it != events6.end())
			return true;

		return false;
	}
}

} //namespace Addon
} //namespace Totem
