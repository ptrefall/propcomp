#include "precomp.h"
#include "property_serializer.h"
#include "gameobject.h"

using namespace Totem;
using namespace clan;

void PropertySerializer::create_and_add_property(GameObject *owner, int type_id, const std::string &name, const std::string &value)
{
	switch(type_id)
	{
		case PropertySerializer::TYPE_UNSIGNED_INT:
		{
			unsigned int result;
			from_string(value, result);
			Property<unsigned int> property = owner->add<unsigned int>(name, result);
			property.set(result);
			break;
		}
		case PropertySerializer::TYPE_INT:
		{
			int result;
			from_string(value, result);
			Property<int> property = owner->add<int>(name, result);
			property.set(result);
			break;
		}
		case PropertySerializer::TYPE_FLOAT:
		{
			float result;
			from_string(value, result);
			Property<float> property = owner->add<float>(name, result);
			property.set(result);
			break;
		}
		case PropertySerializer::TYPE_BOOL:
		{
			bool result;
			from_string(value, result);
			Property<bool> property = owner->add<bool>(name, result);
			property.set(result);
			break;
		}
		case PropertySerializer::TYPE_DOUBLE:
		{
			double result;
			from_string(value, result);
			Property<double> property = owner->add<double>(name, result);
			property.set(result);
			break;
		}
		case PropertySerializer::TYPE_CHAR:
		{
			char result;
			from_string(value, result);
			Property<char> property = owner->add<char>(name, result);
			property.set(result);
			break;
		}
		case PropertySerializer::TYPE_CL_STRING:
		{
			std::string result;
			from_string(value, result);
			Property<std::string> property = owner->add<std::string>(name, result);
			property.set(result);
			break;
		}
		case PropertySerializer::TYPE_CL_VEC2I:
		{
			Vec2i result;
			from_string(value, result);
			Property<Vec2i> property = owner->add<Vec2i>(name, result);
			property.set(result);
			break;
		}
//		case PropertySerializer::TYPE_SERVERGAMEOBJECT:
//		{
//			throw Exception("PropertySerializer::create_and_add_property: ServerGameObject not supported yet");
//			ServerGameObject *result;
//			from_string(value, result);
//			Property<ServerGameObject *> property = owner->add<ServerGameObject *>(name, result);
//			property.set(result);
//			break;
//		}
		default:
			throw Exception(string_format("PropertySerializer::create_and_add_property - Unknown property type %1", type_id));
	}
}

PropertySerializer::PropertyType PropertySerializer::get_property_type(std::shared_ptr<Totem::IProperty> property)
{
	return get_property_type(property.get());
}

PropertySerializer::PropertyType PropertySerializer::get_property_type(Totem::IProperty *property)
{
	if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<unsigned int>())
	{
		return TYPE_UNSIGNED_INT;
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<int>())
	{
		return TYPE_INT;
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<float>())
	{
		return TYPE_FLOAT;
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<bool>())
	{
		return TYPE_BOOL;
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<double>())
	{
		return TYPE_DOUBLE;
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<std::string>())
	{
		return TYPE_CL_STRING;
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<Vec2i>())
	{
		return TYPE_CL_VEC2I;
	}
//	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<ServerGameObject *>())
//	{
//		return TYPE_SERVERGAMEOBJECT;
//	}
	else 
	{
		throw Exception("PropertySerializer::get_property_type: Unknown type " + property->getName());
	}
}

std::string PropertySerializer::property_value_to_string(Totem::IProperty *property)
{
	if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<unsigned int>())
	{
		const unsigned int &value = static_cast<Totem::Property<unsigned int> *>(property)->get();
		return StringHelp::uint_to_text(value);
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<int>())
	{
		const int &value = static_cast<Totem::Property<int> *>(property)->get();
		return StringHelp::int_to_text(value);
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<float>())
	{
		const float &value = static_cast<Totem::Property<float> *>(property)->get();
		return StringHelp::float_to_text(value);
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<bool>())
	{
		const bool &value = static_cast<Totem::Property<bool> *>(property)->get();
		return StringHelp::bool_to_text(value);
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<double>())
	{
		const double &value = static_cast<Totem::Property<double> *>(property)->get();
		return StringHelp::double_to_text(value);
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<char>())
	{
		const char &value = static_cast<Totem::Property<char> *>(property)->get();
		return StringHelp::int_to_text((int)value);
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<std::string>())
	{
		const std::string &value = static_cast<Totem::Property<std::string> *>(property)->get();
		return value;
	}
	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<Vec2i>())
	{
		const Vec2i &value = static_cast<Totem::Property<Vec2i> *>(property)->get();
		return string_format("%1 %2", value.x, value.y);
	}
//	else if(property->getRuntimeTypeId() == Totem::IProperty::getRuntimeTypeId<ServerGameObject *>())
//	{
//		auto &value = static_cast<Totem::Property<ServerGameObject *> *>(property)->get();
//		return StringHelp::int_to_text(value->get_id());
//	}
	else 
	{
		throw Exception("PropertySerializer::property_value_to_string: Unknown type " + property->getName());
	}
}

std::string PropertySerializer::property_value_to_string(std::shared_ptr<Totem::IProperty> property)
{
	return property_value_to_string(property.get());
}

void PropertySerializer::from_string(const std::string &value, unsigned int &result)
{
	result = StringHelp::text_to_uint(value);
}

void PropertySerializer::from_string(const std::string &value, int &result)
{
	result = StringHelp::text_to_int(value);
}

void PropertySerializer::from_string(const std::string &value, float &result)
{
	result = StringHelp::text_to_float(value);
}

void PropertySerializer::from_string(const std::string &value, double &result)
{
	result = StringHelp::text_to_double(value);
}

void PropertySerializer::from_string(const std::string &value, bool &result)
{
	result = StringHelp::text_to_bool(value);
}

void PropertySerializer::from_string(const std::string &value, char &result)
{
	result = value.c_str()[0];
}

void PropertySerializer::from_string(const std::string &value, std::string &result)
{
	result = value;
}

void PropertySerializer::from_string(const std::string &value, Vec2i &result)
{
	std::vector<std::string> values = StringHelp::split_text(value, " ");
	if(values.size() != 2)
		throw Exception("Vec2i from_string failed");

	int x = StringHelp::text_to_int(values[0]);
	int y = StringHelp::text_to_int(values[1]);

	result = Vec2i(x, y);
}

/*void PropertySerializer::from_string(const std::string &value, (ServerGameObject *)&result)
{
	throw Exception("from_string ServerGameObject *: Not supported");
}
*/