
#pragma once

#include "Engine/Common/GameWorld/Components/visual.h"
#include "Server/GameWorld/replicated_component.h"

class ServerVisual : public Totem::Component<ServerVisual>, public ReplicatedComponent
{
public:
	ServerVisual(GameObject *owner, const std::string &name = std::string());
	virtual ~ServerVisual();

	static std::string getType() { return "Visual"; }

protected:
	Totem::Property<int> visual_property;
};
