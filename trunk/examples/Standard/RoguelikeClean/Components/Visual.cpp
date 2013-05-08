#include "Visual.h"
#include "../GameManager.h"
#include "../RenderManager.h"

using namespace clan;
using namespace Totem;

Visual::Visual(Entity *owner)
	: Component<Visual>(GetType()), _owner(owner)
{
	_layer = owner->add<int>("CanvasLayer", 0);
	_symbol = owner->add<int>("Symbol", '@');
	_color = owner->add<TCODColor>("ForegroundColor", TCODColor::white);
	_position = owner->add<Vec2i>("Position", Vec2i());

	_layer.valueChanged().connect(this, &Visual::OnCanvasLayerChanged);

	GameManager::Get()->getRender()->add(this, _layer);
}

Visual::~Visual() 
{
	GameManager::Get()->getRender()->remove(this, _layer);
}

void Visual::render(const std::shared_ptr<TCODConsole> &canvas)
{
	canvas->setChar(_position.get().x, _position.get().y, _symbol.get());
	canvas->setCharForeground(_position.get().x, _position.get().y, _color.get());
}

void Visual::OnCanvasLayerChanged(const int &oldValue, const int &newValue)
{
	GameManager::Get()->getRender()->remove(this, oldValue);
	GameManager::Get()->getRender()->add(this, newValue);
}
