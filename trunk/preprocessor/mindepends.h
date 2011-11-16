
std::string find_and_replace(const std::string &input)
{
	return std::string();
}

void init_preprocessor(std::vector<pp_type*> &types)
{
	types.push_back(new pp_type("T_String", "std::string"));
}
