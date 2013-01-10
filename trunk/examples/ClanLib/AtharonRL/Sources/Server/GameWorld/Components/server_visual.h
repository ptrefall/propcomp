
#pragma once

#include "Engine/Common/GameWorld/Components/visual.h"
#include "Server/GameWorld/replicated_component.h"

class ServerVisual : public Visual, public ReplicatedComponent
{
public:
	ServerVisual(GameObject *owner, const std::string &name = std::string());
	virtual ~ServerVisual();
};
