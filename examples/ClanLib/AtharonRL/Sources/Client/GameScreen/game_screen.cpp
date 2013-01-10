
#include "precomp.h"
#include "game_screen.h"
#include "game.h"
#include "Engine/Client/UIFramework/window_manager.h"
#include "Engine/Common/Network/netevents.h"

#include "Engine/Client/Scene/layer.h"

using namespace clan;

GameScreen::GameScreen(UIScreenManager *screen_manager, Game *game, NetGameClient &network, clan::ResourceManager &resources)
: UIScreen(screen_manager), network(network), game(game)
{
	slots.connect(network.sig_event_received(), this, &GameScreen::on_event_received);

	GraphicContext gc = screen_manager->get_window().get_gc();

	layer_manager.reset(new LayerManager());

	auto tile_data = TileData(Colorf::black, Colorf::white, '.');
	auto description = LayerDescription(Point(0,0), Point(80,50), tile_data);
	auto bitmap = LayerBitmap(Sprite(gc, "Font/font-10", &resources), Point(16,29), nullptr);
	test_layer = std::shared_ptr<Layer>(new Layer(description, bitmap));
	test_layer->set_tile(Point(12, 4), Colorf::blueviolet, Colorf::red, '@');
	layer_manager->add(test_layer);

	zone.reset(new ClientZone(this, network));
}

void GameScreen::on_activated()
{
	UIScreen::on_activated();
}

void GameScreen::update()
{
	Canvas canvas = get_canvas();
	canvas.clear(Colorf::black);
	layer_manager->draw(canvas, 0,0);

	UIScreen::update();
}

void GameScreen::on_event_received(const NetGameEvent &e)
{
	zone->dispatch_net_event(e);
}
