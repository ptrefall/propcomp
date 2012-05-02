/////////////////////////////////////////////////////
//
#pragma once
#pragma warning(push)
#pragma warning(disable : 4481)

#include "IComponent.h"

#include <sigslot.h>
#include <string>
#include <memory>

namespace Totem
{

template<class ComponentType, class UserData = void*>
class Component : public IComponent<UserData>, public sigslot::has_slots<>, protected std::enable_shared_from_this<ComponentType>
{
public:
	Component(const std::string &name) 
		: name(name)
	{
	}
	virtual ~Component()
	{
	}

	static bool isType(std::shared_ptr<IComponent<UserData>> component)
	{
		return (component->getRuntimeTypeId() == IComponent<UserData>::getRuntimeTypeId<ComponentType>());
	}

	unsigned int getRuntimeTypeId() const override { return IComponent<UserData>::getRuntimeTypeId<ComponentType>(); }
	const std::string &getName() const override { return name; }

	Component &operator= (const Component &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between ComponentTypes are not supported!");
	}

	sigslot::signal1<std::shared_ptr<ComponentType>> &removed() { return sign_Removed; }
	void invokeRemovedSignal() final { sign_Removed.invoke(shared_from_this()); }
	
protected:
	std::string name;
	sigslot::signal1<std::shared_ptr<ComponentType>> sign_Removed;
};

} // namespace Totem

#pragma warning(pop)

//
/////////////////////////////////////////////////////////
