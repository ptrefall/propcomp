
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
	std::vector<pp_type*> types;
	init_preprocessor(types);
}