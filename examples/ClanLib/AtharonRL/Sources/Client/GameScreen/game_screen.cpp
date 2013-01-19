
#include "precomp.h"
#include "game_screen.h"
#include "game.h"
#include "Engine/Client/UIFramework/window_manager.h"
#include "Engine/Common/Network/netevents.h"

#include "Engine/Client/Scene/layer.h"

using namespace clan;

GameScreen::GameScreen(UIScreenManager *screen_manager, Game *game, NetGameClient &network, clan::ResourceManager &resources)
: /*UIScreen(screen_manager), */network(network), game(game)
{
	slots.connect(network.sig_event_received(), this, &GameScreen::on_event_received);

	GraphicContext gc = screen_manager->get_window().get_gc();
	
	auto glyph_size = Point(16,29);
	auto layer_screen_size = Point((gc.get_width() / glyph_size.x), (gc.get_height() / glyph_size.y));
	//auto layer_screen_size = Point(3,2);
	layer_manager.reset(new LayerManager(layer_screen_size));

	auto tile_data = std::make_shared<TileData>(Colorf::black, Colorf::white, '.');
	auto description = LayerDescription(Point(0,0), layer_manager->get_screen_size(), tile_data);
	auto bitmap = LayerBitmap(Sprite(gc, "Font/font-10", &resources), glyph_size, nullptr);
	test_layer = std::shared_ptr<Layer>(new Layer("Character", description, bitmap));
	//test_layer->set_tile(Point(12, 4), Colorf::blueviolet, Colorf::red, '@');
	layer_manager->add(test_layer);

	zone.reset(new ClientZone(network, layer_manager));
}

void GameScreen::on_activated()
{
//	UIScreen::on_activated();
}

void GameScreen::update()
{
	//Clear layers before we let zone fill it with new data
	layer_manager->clear();

	zone->tick(0.0167f);

//	UIScreen::update();
}

void GameScreen::draw(Canvas &canvas)
{
//	Canvas canvas = get_canvas();

	canvas.clear();
	layer_manager->draw(canvas, 0,0);
}

void GameScreen::on_event_received(const NetGameEvent &e)
{
	zone->dispatch_net_event(e);
}
