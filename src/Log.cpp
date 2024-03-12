#include "Log.h"


mfpg_log::VERBOSE_LEVEL mfpg_log::VERBOSE = VERBOSE_LEVEL::VERBOSE_ALL;

void mfpg_log::Log::verbose_out(std::ostream& out, std::string s, VERBOSE_LEVEL v) {
	if (v <= VERBOSE) {
		out << s;
	}
}	
