#pragma once

class ClientCamera
{
public:
	ClientCamera();

	void set_position(const clan::Point &position) { this->position = position; }
	const clan::Point &get_position() const { return position; }

private:
	clan::Point position;
};
