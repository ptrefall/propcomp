#include "precomp.h"
#include "component_serializer.h"

#include "Components/looks.h"
#include "Components/transform.h"

using namespace Totem;
using namespace clan;

std::string ComponentSerializer::get_component_type(std::shared_ptr<Totem::IComponent<>> component)
{
	if(IComponent<>::isType<Looks>(component))
	{
		return Looks::getType();
	}
	else if(IComponent<>::isType<Transform>(component))
	{
		return Transform::getType();
	}
	/*else if(Component<MeshObject>::isType(component))
	{
		return MeshObject::getType();
	}
	else if(Component<BoxCollider>::isType(component))
	{
		return BoxCollider::getType();
	}
	else if(Component<TriggerDisplayText>::isType(component))
	{
		return TriggerDisplayText::getType();
	}*/
	else
	{
		throw Exception("ComponentSerializer::get_component_type - Unable to get type for component " + component->getRuntimeTypeId());
	}
}
