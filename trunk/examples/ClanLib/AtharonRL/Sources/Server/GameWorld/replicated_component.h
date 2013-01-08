
#pragma once

class ReplicatedComponent
{
public:
	enum ReplicationMode
	{
		REPLICATE_ON_CREATION = 1,
		REPLICATE_ON_CHANGE = 2
	};

public:
	void replicate_property(Totem::Property<unsigned int> &property, ReplicationMode mode = REPLICATE_ON_CREATION);
	void replicate_property(Totem::Property<int> &property, ReplicationMode mode = REPLICATE_ON_CREATION);
	void replicate_property(Totem::Property<float> &property, ReplicationMode mode = REPLICATE_ON_CREATION);
	void replicate_property(Totem::Property<double> &property, ReplicationMode mode = REPLICATE_ON_CREATION);
	void replicate_property(Totem::Property<bool> &property, ReplicationMode mode = REPLICATE_ON_CREATION);
	void replicate_property(Totem::Property<std::string> &property, ReplicationMode mode = REPLICATE_ON_CREATION);
	void replicate_property(Totem::Property<clan::Vec3f> &property, ReplicationMode mode = REPLICATE_ON_CREATION);
	void replicate_property(Totem::Property<clan::Quaternionf> &property, ReplicationMode mode = REPLICATE_ON_CREATION);

	std::vector<Totem::IProperty *> get_tracked_properties();
	std::vector<Totem::IProperty *> get_dirty_properties();
	void clear_dirty_properties();

private:
	void on_uint_value_changed(const unsigned int &old_value, const unsigned int &new_value, Totem::IProperty *property);
	void on_int_value_changed(const int &old_value, const int &new_value, Totem::IProperty *property);
	void on_float_value_changed(const float &old_value, const float &new_value, Totem::IProperty *property);
	void on_double_value_changed(const double &old_value, const double &new_value, Totem::IProperty *property);
	void on_bool_value_changed(const bool &old_value, const bool &new_value, Totem::IProperty *property);
	void on_cl_string_value_changed(const std::string &old_value, const std::string &new_value, Totem::IProperty *property);
	void on_cl_vec3f_value_changed(const clan::Vec3f &old_value, const clan::Vec3f &new_value, Totem::IProperty *property);
	void on_cl_quaternionf_value_changed(const clan::Quaternionf &old_value, const clan::Quaternionf &new_value, Totem::IProperty *property);

	std::map<Totem::IProperty *, bool /*dirty*/> properties;

	clan::SlotContainer slots;
};
