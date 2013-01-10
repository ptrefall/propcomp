#pragma once

class UIScreen;
class ClientGameObject;

class ClientComponentFactory
{
public:
	ClientComponentFactory(UIScreen *screen);

	void create_and_add_component(ClientGameObject *owner, const std::string &type, const std::string &name);

private:
	UIScreen *screen;
};
