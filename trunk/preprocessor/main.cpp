
#include <string>
#include <vector>

struct pp_type
{
	std::string find;
	std::string replace;
	pp_type(const std::string &find, const std::string &replace) : find(find), replace(replace) {}
};

#ifdef MINDEPENDS_PREPROCESSOR
#include "mindepends.h"
#elif BOOST_PREPROCESSOR
#include "boost.h"
#elif CLANLIB_PREPROCESSOR
#include "clanlib.h"
#endif

int main(int argc, char **argv)
{
	std::vector<pp_type*> basic_types;
	init_basic_findreplace_strings(basic_types);
	
	std::vector<pp_type*> component_special_types;
	init_component_replacements(component_special_types);
}
