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
class Entity;

enum ComponentFactoryCreateType
{
	CFCT_GET_FROM_POOL = 1,
	CFCT_GET_FROM_POOL_OR_CREATE,
	CFCT_CREATE
};

class PoolComponentFactory
{
public:
	template<class ComponentType>
	std::shared_ptr<ComponentType> create(Entity *entity, unsigned int optionalParam)
	{
		auto component_type_pool_it = pools.find(ComponentType::Type());
		if(component_type_pool_it == pools.end())
			throw std::runtime_error("Couldn't find component pool!");

		std::vector<std::pair<bool, ComponentPtr>> &component_type_pool = component_type_pool_it->second;
		std::for_each(component_type_pool.begin(), component_type_pool.end(), [](std::pair<bool, ComponentPtr> &component_in_pool){
			if(component_in_pool.first == true)
				continue;

			std::shared_ptr<ComponentType> component = std::static_pointer_cast<ComponentType>(component_in_pool.second);
			component->reset(entity);
			return component;
		});

		throw std::runtime_error("Couldn't find component in pool!");
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> create(Entity *entity, CustomParam0 param0, unsigned int optionalParam)
	{
		auto component_type_pool_it = pools.find(ComponentType::Type());
		if(component_type_pool_it == pools.end())
			throw std::runtime_error("Couldn't find component pool!");

		std::vector<std::pair<bool, ComponentPtr>> &component_type_pool = component_type_pool_it->second;
		for(unsigned int i = 0; i < component_type_pool.size(); i++)
		{
			std::pair<bool, ComponentPtr> &component_in_pool = component_type_pool[i];
			if(component_in_pool.first != true)
			{
				std::shared_ptr<ComponentType> component = std::static_pointer_cast<ComponentType>(component_in_pool.second);
				component->reset(entity, param0);
				return component;
			}
		};

		throw std::runtime_error("Couldn't find component in pool!");
	}

	template<class ComponentType>
	void pool(const unsigned int &count, Entity *entity)
	{
		std::vector<std::pair<bool, ComponentPtr>> component_type_pool;
		std::for_each(0, count, [](){
			component_type_pool.push_back(std::pair<bool, ComponentPtr>(false, std::make_shared<ComponentType>(entity)));
		});
		pools[ComponentType::Type()] = component_type_pool;
	}

	template<class ComponentType, class CustomParam0>
	void pool(const unsigned int &count, Entity *entity, CustomParam0 param0)
	{
		std::vector<std::pair<bool, ComponentPtr>> component_type_pool;
		for (unsigned int i = 0; i < count; i++)
			component_type_pool.push_back(std::pair<bool, ComponentPtr>(false, std::make_shared<ComponentType>(entity, param0)));
		pools[ComponentType::Type()] = component_type_pool;
	}

protected:
	std::unordered_map<std::string, std::vector<std::pair<bool, ComponentPtr>>> pools;
};
//
/////////////////////////////////////////////////////////