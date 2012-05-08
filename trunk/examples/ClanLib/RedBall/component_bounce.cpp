
#include "precomp.h"
#include "component_bounce.h"

Bounce::Bounce(Entity *owner, const CL_String &name)
: Component<Bounce>(name)
{
	property_bounce_height = owner->add<float>("bounce_height", 0.0f);
	property_bounce_speed = owner->add<float>("bounce_speed", 10.0f);

	property_position = owner->add<CL_Pointf>("position", CL_Pointf());

	slot = property_position.valueChanged().connect(this, &Bounce::on_position_changed);
	on_position_changed(property_position.get(), property_position.get());

	total_time = 0.0f;
}

void Bounce::update(const float &delta_time)
{
	total_time += delta_time;

	CL_Pointf position = property_position;

	float curve = ((sinf(total_time * (property_bounce_speed / 1000))) + 1.0f) / 2.0f;  
	float ypos = curve * property_bounce_height;

	position.y = original_position.y - ypos;

	property_position.set(position, false);
}

void Bounce::on_position_changed(const CL_Pointf &old_value, const CL_Pointf &new_value)
{
	original_position = new_value;
}
