
#include "precomp.h"
#include "client_visual.h"
#include "../client_zone.h"
#include "../client_camera.h"
#include "Engine/Client/Scene/layer_manager.h"
#include "Engine/Client/Scene/layer.h"

using namespace Totem;
using namespace clan;

ClientVisual::ClientVisual(GameObject *owner, const std::string &name, ClientZone *zone, const LayerManagerPtr &layer_manager)
: Visual(owner, name), layer_manager(layer_manager)
{
	position_property = owner->add<Vec2i>("Position", Vec2i());

	character_layer = layer_manager->get("Character");
	dungeon_layer = layer_manager->get("Dungeon");

	slots.connect(zone->sig_draw, this, &ClientVisual::on_draw);
}

ClientVisual::~ClientVisual()
{
}

void ClientVisual::update(const float &delta_time)
{
}

void ClientVisual::on_draw(const ClientCameraPtr &camera)
{
	int character = '@';
	switch(visual_property.get())
	{
	case GOV_CHARACTER:
		character = '@'; break;
	case GOV_ORC:
		character = 'o'; break;
	case GOV_TROLL:
		character = 'T'; break;
	case GOV_ITEM:
		character = '['; break;
	case GOV_SCROLL:
		character = '#'; break;
	case GOV_POTION:
		character = '!'; break;
	case GOV_CORPSE:
		character = '%'; break;
	};

	auto view_space_position = position_property.get() - camera->get_view() + camera->get_projection();
	character_layer->set_tile(view_space_position, TileData(Colorf::black, Colorf::yellow, character));
}

