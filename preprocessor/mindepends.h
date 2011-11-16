
std::string find_and_replace(const std::string &input)
{
	return std::string();
}

void init_basic_findreplace_strings(std::vector<pp_type*> &types)
{
	//--------------------------------------------
	//Base types
	types.push_back(new pp_type("T_String", "std::string"));
	types.push_back(new pp_type("D32", "double"));
	types.push_back(new pp_type("F32", "float"));
	types.push_back(new pp_type("S32", "int"));
	types.push_back(new pp_type("U32", "unsigned int"));
	types.push_back(new pp_type("T_PropertyTypeId", "unsigned int"));
	types.push_back(new pp_type("T_EntityId", "unsigned long"));
	types.push_back(new pp_type("T_Any", "cdiggins::any"));
	types.push_back(new pp_type("T_BadAnyCast", "cdiggins::anyimpl::bad_any_cast"));
	
	//--------------------------------------------
	//Container types
	
	//--------------------------------------------
	//Exception handling
	types.push_back(new pp_type("T_Exception", "std::exception"));
	
	//--------------------------------------------
	//Signal handling
	types.push_back(new pp_type("HAS_SIGNALSLOTS_INHERITANCE_TYPE", ": public sigslot::has_slots<sigslot::single_threaded>"));
	
	//--------------------------------------------
	//Delegate handling
	
	//--------------------------------------------
	//Resource handling
	types.push_back(new pp_type("NULL_PTR", "null_ptr"));
	
	//--------------------------------------------
	//Hash handling
}

void init_component_replacements(std::vector<pp_type*> &types)
{
	//--------------------------------------------
	//T_Any //Actually don't need any editing for mindepends on this, but left in here to demonstrate
	/*types.push_back(new pp_type("custom1.cast<Custom_type1*>();", "custom1.cast<Custom_type1*>();"));
	types.push_back(new pp_type("custom2.cast<Custom_type2*>();", "custom1.cast<Custom_type2*>();"));
	types.push_back(new pp_type("custom3.cast<Custom_type3*>();", "custom1.cast<Custom_type3*>();"));
	types.push_back(new pp_type("custom4.cast<Custom_type4*>();", "custom1.cast<Custom_type4*>();"));
	types.push_back(new pp_type("custom5.cast<Custom_type5*>();", "custom1.cast<Custom_type5*>();"));
	types.push_back(new pp_type("custom6.cast<Custom_type6*>();", "custom1.cast<Custom_type6*>();"));
	types.push_back(new pp_type("custom7.cast<Custom_type7*>();", "custom1.cast<Custom_type7*>();"));
	types.push_back(new pp_type("custom8.cast<Custom_type8*>();", "custom1.cast<Custom_type8*>();"));*/
	
	//--------------------------------------------
	//Container types
	
	//--------------------------------------------
	//Exception handling
	
	//--------------------------------------------
	//Signal handling
	
	
	//--------------------------------------------
	//Delegate handling
	
	//--------------------------------------------
	//Resource handling
	
	//--------------------------------------------
	//Hash handling
}
