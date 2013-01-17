
#include "precomp.h"
#include "client_visual.h"
#include "Engine/Client/Scene/layer_manager.h"
#include "Engine/Client/Scene/layer.h"

using namespace Totem;
using namespace clan;

ClientVisual::ClientVisual(GameObject *owner, const std::string &name, const LayerManagerPtr &layer_manager)
: Visual(owner, name), layer_manager(layer_manager)
{
	position_property = owner->add<Vec2i>("Position", Vec2i());

	character_layer = layer_manager->get("Character");
	dungeon_layer = layer_manager->get("Dungeon");
}

ClientVisual::~ClientVisual()
{
}

void ClientVisual::update(const float &delta_time)
{
	int character = '@';
	switch(visual_property.get())
	{
	case GOV_CHARACTER:
		character = '@';
	case GOV_ORC:
		character = 'o';
	case GOV_TROLL:
		character = 'T';
	case GOV_ITEM:
		character = '[';
	case GOV_SCROLL:
		character = '#';
	case GOV_POTION:
		character = '!';
	case GOV_CORPSE:
		character = '%';
	};
	character_layer->set_tile(position_property.get(), TileData(Colorf::black, Colorf::yellow, character));
}
