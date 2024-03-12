#ifndef LOG_MFPG_H
#define LOG_MFPG_H

#include <ostream>

namespace mfpg_log {

	enum class VERBOSE_LEVEL {
		VERBOSE_NONE = 0,
		VERBOSE_ERRORS = 1,
		VERBOSE_ALL = 2
	};

	extern VERBOSE_LEVEL VERBOSE;

	class Log {
		public:
			Log() = delete;
			static void verbose_out(std::ostream& out, std::string s, VERBOSE_LEVEL v);
	};
}
#endif
