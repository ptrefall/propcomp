/////////////////////////////////////////////////////
//
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

class Component;
typedef std::shared_ptr<Component> ComponentPtr;
class PoolComponentFactory;
typedef std::shared_ptr<PoolComponentFactory> PoolComponentFactoryPtr;

class PoolComponentFactory
{
public:
	unsigned int getTypeId(const std::string &type);

	template<class ComponentType>
	void registerTypeId()
	{
		internalRegisterTypeId(ComponentType::Type(), Component::getTypeId<ComponentType>());
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> create()
	{
		auto component_type_pool_it = pools.find(Component::getTypeId<ComponentType>());
		if(component_type_pool_it == pools.end())
			throw std::runtime_error("Couldn't find component pool!");

		std::vector<std::pair<bool, ComponentPtr>> &component_type_pool = component_type_pool_it->second;
		std::for_each(component_type_pool.begin(), component_type_pool.end(), [](std::pair<bool, ComponentPtr> &component_in_pool){
			if(component_in_pool.first == true)
				continue;

			std::shared_ptr<ComponentType> component = (std::shared_ptr<ComponentType>)component_in_pool.second;
			component->reset();
			return component;
		});

		throw std::runtime_error("Couldn't find component in pool!");
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> create(CustomParam0 param0)
	{
		auto component_type_pool_it = pools.find(Component::getTypeId<ComponentType>());
		if(component_type_pool_it == pools.end())
			throw std::runtime_error("Couldn't find component pool!");

		std::vector<std::pair<bool, ComponentPtr>> &component_type_pool = component_type_pool_it->second;
		for(unsigned int i = 0; i < component_type_pool.size(); i++)
		{
			std::pair<bool, ComponentPtr> &component_in_pool = component_type_pool[i];
			if(component_in_pool.first != true)
			{
				std::shared_ptr<ComponentType> component = std::shared_ptr<ComponentType>(dynamic_cast<ComponentType*>(component_in_pool.second.get()));
				component->reset(param0);
				return component;
			}
		};

		throw std::runtime_error("Couldn't find component in pool!");
	}

	template<class ComponentType>
	void pool(const unsigned int &count)
	{
		std::vector<std::pair<bool, ComponentPtr>> component_type_pool;
		std::for_each(0, count, [](){
			component_type_pool.push_back(std::pair<bool, ComponentPtr>(false, std::make_shared<ComponentType>()));
		});
		pools[Component::getTypeId<ComponentType>()] = component_type_pool;
	}

	template<class ComponentType, class CustomParam0>
	void pool(const unsigned int &count, CustomParam0 param0)
	{
		std::vector<std::pair<bool, ComponentPtr>> component_type_pool;
		for (unsigned int i = 0; i < count; i++)
			component_type_pool.push_back(std::pair<bool, ComponentPtr>(false, std::make_shared<ComponentType>(param0)));
		pools[Component::getTypeId<ComponentType>()] = component_type_pool;
	}

protected:
	void internalRegisterTypeId(const std::string &type, unsigned int typeId);
	std::unordered_map<std::string, unsigned int> component_type_ids;
	std::unordered_map<unsigned int, std::vector<std::pair<bool, ComponentPtr>>> pools;
};
//
/////////////////////////////////////////////////////////