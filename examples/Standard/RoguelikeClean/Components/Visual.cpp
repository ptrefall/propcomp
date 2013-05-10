#include "Visual.h"
#include "../GameManager.h"
#include "../RenderManager.h"
#include "../PropertyDefinitions.h"

using namespace clan;
using namespace Totem;

Visual::Visual(Entity *owner)
	: Component<Visual>(GetType()), _owner(owner)
{
	_layer = owner->add<int>(PROPERTY_CANVAS_LAYER, RenderManager::LAYER_GROUND);
	_symbol = owner->add<int>(PROPERTY_SYMBOL, '@');
	_color = owner->add<TCODColor>(PROPERTY_FOREGROUND_COLOR, TCODColor::white);
	_position = owner->add<Vec2i>(PROPERTY_POSITION, Vec2i());

	_layer.valueChanged().connect(this, &Visual::OnCanvasLayerChanged);

	GameManager::Get()->getRender()->add(this, RenderManager::toLayer(_layer));
}

Visual::~Visual() 
{
	GameManager::Get()->getRender()->remove(this, RenderManager::toLayer(_layer));
}

void Visual::render(const std::shared_ptr<TCODConsole> &canvas)
{
	canvas->setChar(_position.get().x, _position.get().y, _symbol.get());
	canvas->setCharForeground(_position.get().x, _position.get().y, _color.get());
	//canvas->setCharBackground(_position.get().x, _position.get().y, TCODColor(255, 240, 0));
	//canvas->putChar(_position.get().x, _position.get().y, _symbol.get(), TCOD_BKGND_NONE);
}

void Visual::OnCanvasLayerChanged(const int &oldValue, const int &newValue)
{
	GameManager::Get()->getRender()->remove(this, RenderManager::toLayer(oldValue));
	GameManager::Get()->getRender()->add(this, RenderManager::toLayer(newValue));
}
